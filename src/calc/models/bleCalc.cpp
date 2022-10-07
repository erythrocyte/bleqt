#include "bleCalc.hpp"

#include <chrono>
#include <fstream>
#include <math.h>
#include <numeric>
#include <sstream>
#include <stdio.h>

#include "calc/services/pressureSolver.hpp"
#include "calc/services/saturAverService.hpp"
#include "calc/services/saturSolverAnalytic.hpp"
#include "calc/services/saturSolverNum.hpp"
#include "calc/services/workParam.hpp"
#include "calc/services/workTimeStep.hpp"
#include "common/services/dataDistributionService.hpp"
#include "common/services/shockFront.hpp"
#include "common/services/wellWorkCalc.hpp"
#include "common/services/workRp.hpp"
#include "common/services/workString.hpp"
#include "file/services/workFile.hpp"
#include "logging/logger.hpp"

namespace cs = ble::src::common::services;
namespace fss = ble::src::file::services;

namespace ble::src::calc::models {

BleCalc::BleCalc()
{
    _results = std::make_shared<BleResultData>();
}

BleCalc::~BleCalc()
{
    _results.reset();
    _wellWorkParams.clear();
    m_tau_data.clear();
}

void BleCalc::calc(const std::shared_ptr<mesh::models::Grid> grd,
    const std::shared_ptr<common::models::SolverData> data,
    std::function<void(double)> set_progress, bool clear_aver)
{
    auto suit_step = [&](double fw, double sum_t) {
        bool result = true;
        if (data->use_fwlim) {
            result = fw <= data->fw_lim;
            if (!result) {
                std::cout << "max watercut value reached" << std::endl;
            }
        } else {
            result = sum_t <= data->period;
            if (!result) {
                std::cout << "max time value reached" << std::endl;
            }
        }

        return result;
    };

    auto get_perc = [&](double fw, double sum_t) {
        double p = data->use_fwlim
            ? fw / data->fw_lim
            : sum_t / data->period;

        return std::min(100.0, p * 100);
    };

    auto get_fract_pv = [&]() {
        double ans = 0.0;
        double poro = 1.0; // data->real_poro;
        for (const auto& cl : grd->cells) {
            ans += cl->volume;
        }

        return ans * poro * 2.0 * data->delta;
    };

    auto save_aver_reached = [&](int index, const char* fn, bool conv) {
        if (conv) {
            auto s = cs::string_format("fw shore and well converged in %i iter", index);
            logging::write_log(s, logging::kInfo);
        }
        auto d = std::make_shared<calc::models::AverFwSaveData>();
        d->m = data->m;
        d->s_const = data->top_bot_bound_s[0]->v0;
        d->converged = conv;
        d->data = m_fw_data[m_fw_data.size() - 1];
        d->iter_count = index;
        // d->cv = data->sat_setts->cv;
        // d->cg = data->sat_setts->cg;
        save_aver_fw(fn, d);
    };

    auto get_tau = [&](int index, const std::vector<double> s) {
        switch (data->sat_setts->time_step_type) {
        case cm::TimeStepType::kOld:
            return services::get_time_step(grd, s, data);
        case cm::TimeStepType::kNew:
            return services::get_time_step_new(index, grd, s, data);
        default:
            return 0.0;
        }
    };

    auto snapshot_fields = [&](double sumU, double sumT, const std::vector<double>& p,
                               const std::vector<double>& s) {
        double sc = cs::shock_front::get_shock_front(data->rp_n, data->kmu);
        std::vector<std::tuple<double, double>> xs_an;
        if (data->get_contour_press_bound_type() == common::models::BoundCondType::kConst)
            xs_an = services::get_satur_exact(sc, sumU, data);
        auto d = std::make_shared<ble::src::common::models::DynamicData>();
        d->t = sumT;
        d->p = p;
        d->s = s;
        d->s_an = xs_an;
        d->p_ex = _results->data[0]->p_ex;

        _results->data.push_back(d);
    };

    create_one_calc_files_headers();

    m_data = data;
    m_grd = grd;

    _results->data.clear();
    m_tau_data.clear();
    m_fw_data.clear();
    _wellWorkParams.clear();

    m_sum_t = 0.0;
    set_initial_cond();

    int index = 0, fw_const_iter = 0;
    double sumT = 0.0, sumU = 0.0, cur_fw = 0.0, sumQ = 0.0;
    double fract_pv = get_fract_pv();
    std::vector<double> pvi_inds = {}; // 0.1, 0.5, 1.0, 2.0, 4.0, 6.0 };
    int pvi_ind = static_cast<int>(pvi_inds.size()) == 0
        ? -1
        : 0;

    std::vector<double> s_cur, s_prev = _results->data[0]->s;
    std::vector<double> p = _results->data[0]->p;

    services::calc_u(p, s_prev, data, grd);
    std::chrono::system_clock::time_point start, end;
    std::chrono::duration<double> diff;
    bool aver_reached = false;
    double sf_aver_prev = std::accumulate(s_prev.begin(), s_prev.end(), 0.0) / s_prev.size();

    const char* aver = "aver.dat";
    if (clear_aver)
        std::remove(aver);

    if (!data->sat_setts->need_satur_solve) {
        auto well_params = services::calc_well_work_param(grd, s_prev, data, sumT);

        // check_conservative();

        // std::cout << "m = " << data->m << ", q = " << well_params->ql << std::endl;
        // double qan = services::calc_q_analytic(grd, data);
        // double qnum = well_params->ql;
        // double perc = std::abs(qan - qnum) / qan * 100.0;

        std::string mess = common::services::string_format("m = %.4f, q = %.5f", data->m, well_params->ql_well);
        logging::write_log(mess, logging::kInfo);

        // save_faces_val(grd, data);
    } else {
        auto sst_name = SaturSolverType::get_description(data->sat_setts->type);
        std::string mess = common::services::string_format("saturation solver type: %s", sst_name.c_str());
        logging::write_log(mess, logging::kInfo);
        while (suit_step(cur_fw, sumT)) {
            if (index % data->sat_setts->pressure_update_n == 0) {
                p = services::solve_press(grd, s_prev, data);
                services::calc_u(p, s_prev, data, grd);
                // save_press(index, grd, p);
            }

            double t = data->sat_setts->type == SaturSolverType::kImplicit
                ? data->sat_setts->tau
                : get_tau(index, s_prev);

            // double t = 1e-5;

            double u = data->get_contour_press_bound_type() == common::models::BoundCondType::kConst
                ? services::getULiqInject(grd, data->mesh_setts->type)
                : 0.0;
            sumU += u * t;

            s_cur = services::solve_satur(t, index == 0, s_prev, data, grd);

            // std::string fn_s = data->sat_setts->type == SaturSolverType::kImplicit
            //     ? "impl::"
            //     : "expl::";
            // auto x = m_grd->get_cells_centers();

            // std::vector<std::tuple<double, double>> y(s_cur.size());
            // std::transform(x.begin(), x.end(), s_cur.begin(), y.begin(),
            //     [](auto&& a, auto&& b) {
            //         return std::make_tuple(std::move(a), std::move(b));
            //     });

            // save_any_vector(y, fn_s);
            // std::cout << fn_s << "tau = " << t << ", m = " << data->m << ", s[0] = " << s_cur[0] << "\n";
            // break;
            s_prev = s_cur;
            sumT += t;
            m_tau_data.push_back(std::make_shared<common::models::TauData>(sumT, t));

            if (index % data->sat_setts->satur_field_save_n == 0) {
                snapshot_fields(sumU, sumT, p, s_cur);
            }
            index++;

            auto wwp = services::calc_well_work_param(grd, s_cur, data, sumT);
            _wellWorkParams.push_back(wwp);

            if (data->sat_setts->use_fw_delta) {
                double r_fw = std::abs(wwp->fw_well - cur_fw);
                if (r_fw != 0.0) {
                    if (r_fw < data->sat_setts->fw_delta) {
                        fw_const_iter++;
                    } else {
                        fw_const_iter = 0;
                    }
                }

                if (fw_const_iter > data->sat_setts->fw_delta_iter) {
                    logging::write_log("fw change significant reason for break calc", logging::kInfo);
                    break;
                }
            }

            cur_fw = wwp->fw_well;
            if (index % 100 == 0) {
                auto s = cs::string_format("fw = {%.6f}, t = {%.6f}, s_w = {%.4f}, index = {%i}", cur_fw, t, s_cur[0], index);
                logging::write_log(s, logging::kInfo);
            }

            sumQ += wwp->ql_well * t;
            double pv = sumQ / fract_pv; // how many pv are flushed
            add_aver_fw(pv, wwp, s_cur, sf_aver_prev, t);

            if (pvi_ind != -1 && pv > pvi_inds[pvi_ind]) {
                save_pvi_s(pv, pvi_inds[pvi_ind], s_cur, m_data->m);

                pvi_ind++;
                if (pvi_ind >= static_cast<int>(pvi_inds.size()))
                    pvi_ind = -1;
            }

            // if (!fss::file_exists("dd.dat")) {
            //     std::ofstream a("dd.dat");
            //     a << "s\tt\tu\tPVI\tsumT\tsumQ\tql\tvp\tql_shore\tfw\n";
            //     a.close();
            // }

            // if (index % 1 == 0) {
            //     std::ofstream a("dd.dat", std::ios_base::app);
            //     a << s_cur[0] << "\t" << t << "\t" << u << "\t"
            //       << pv << "\t" << sumT << "\t"
            //       << sumQ << "\t" << wwp->ql << "\t" << fract_pv << "\t"
            //       << wwp->ql_shore << "\t" << wwp->fw << "\n";
            //     a.close();
            // }

            double perc = get_perc(cur_fw, sumT);
            set_progress(perc);

            if (index > data->sat_setts->max_iter) {
                auto s = cs::string_format("max iter {%i} reached", data->sat_setts->max_iter);
                logging::write_log(s, logging::kInfo);
                break;
            }

            if (data->sat_setts->use_fw_shorewell_converge) {
                double r = std::abs(wwp->fw_well - wwp->fw_shore); // residual
                double dr = wwp->fw_shore * data->sat_setts->fw_shw_conv / 100.0;
                // double dr = data->sat_setts->fw_shw_conv;
                if (index % 10 == 0) {
                    auto s = cs::string_format("fw_well = {%.6f}, fw_shore = {%.6f}, r = {%.6f}, dr = {%.6f}, s_w = {%.6f}",
                        wwp->fw_well, wwp->fw_shore, r, dr, s_cur[0]);
                    logging::write_log(s, logging::kInfo);
                }
                if (r < dr) {
                    save_aver_reached(index, aver, true);
                    aver_reached = true;
                    break;
                }
            }
        }

        logging::write_log("saturation solve completed", logging::kInfo);
    }

    m_sum_t = sumT;

    if (!aver_reached && data->get_contour_press_bound_type() == common::models::BoundCondType::kImpermeable) {
        save_aver_reached(index, aver, false);
    }

    // std::string m = common::services::string_format("U/PV = %.8f", sumU / fract_pv / 2.0);
    // logging::write_log(m, logging::kInfo);
    // m = cs::string_format("PV = %.6f", fract_pv / 2.0);
    // logging::write_log(m, logging::kInfo);

    // if (!fss::file_exists("1.dat")) {
    //     std::ofstream ofs("1.dat");
    //     ofs << "n\ttau\tfwlim\tU/m\ts\tPVI\tfpv\n";
    //     ofs.close();
    // }

    // std::ofstream ofs("1.dat", std::ios_base::app);
    // ofs << grd->cells.size() << "\t"
    //     << data->sat_setts->tau << "\t"
    //     << data->fw_lim << "\t"
    //     << sumU << "\t"
    //     << s_cur[0] << "\t"
    //     << sumQ / fract_pv << "\t" // how many pv are flushed // / fract_pv / 2.0 << "\n";
    //     << fract_pv << "\n";
    // ofs.close();

    set_progress(100); // completed;
}

void BleCalc::create_one_calc_files_headers()
{
    // sffw
    std::ofstream ofs(m_sffw_fn);
    ofs << "s\tf_sf\tf_num\n";
    ofs.close();
}

void BleCalc::set_initial_cond()
{
    std::vector<double> s;
    for (auto const& cl : m_grd->cells) {
        double cl_s = src::common::services::DataDistributionService::get_value(cl->cntr, m_data->initial_s, 0.0);
        s.push_back(cl_s);
    }

    // = m_data->initial_s;
    std::vector<double> p = services::solve_press(m_grd, s, m_data);
    std::vector<double> p_ex = services::calc_press_exact(m_grd, m_data);

    auto d = std::make_shared<ble::src::common::models::DynamicData>();
    d->t = 0;
    d->p = p;
    d->s = s;
    d->p_ex = p_ex;

    _results->data.push_back(d);
}

void BleCalc::save_press(int index, const std::vector<double> p)
{
    std::ostringstream oss;
    oss << "press_" << index << ".dat";
    std::ofstream ofs(oss.str().c_str());

    ofs << "cind\tpress\tum\tup";

    for (auto& cl : m_grd->cells) {
        ofs << cl->ind << "\t" << p[cl->ind] << "\t"
            << m_grd->faces[cl->faces[0]]->u << "\t"
            << m_grd->faces[cl->faces[1]]->u << std::endl;
    }

    ofs.close();
}

void BleCalc::save_faces_val()
{
    auto uan = [&](double x) {
        return (1.0 - 0.0) / std::log(1.0 / m_data->rw) / x;
    };

    std::ofstream f("faces_val.dat");
    for (auto& fc : m_grd->faces) {
        f << fc->cntr << "\t" << fc->u << "\t" << fc->area << "\t" << uan(fc->cntr) << std::endl;
    }
    f.close();
}

void BleCalc::save_any_vector(const std::vector<std::tuple<double, double>>& v, const std::string& fn)
{
    std::ofstream f(fn.c_str());
    double x, y;
    for (auto& item : v) {
        std::tie(x, y) = item;
        f << x << "\t" << y << std::endl;
    }
    f.close();
}

double BleCalc::get_period()
{
    return m_sum_t;
}

void BleCalc::add_aver_fw(double pv, const std::shared_ptr<cmm::WellWorkParams> wwp,
    const std::vector<double>& s, double& sf_prev, double tau)
{
    auto item = std::make_shared<common::models::FwData>();
    item->pv = pv;
    item->fw_num_well = wwp->fw_well;
    item->fw_num_shore = wwp->fw_shore;
    item->sav_an_shore = services::SaturAverService::get_satur_aver_analytic(m_data->rp_n, wwp->fw_shore / 100.0, m_data->kmu);
    item->sav_num = services::SaturAverService::get_satur_aver_num(m_grd, s);
    double qw_shore = cs::wellworkcalc::calc_qw(wwp->ql_shore, wwp->fw_shore);
    double ql_well = wwp->ql_well;

    // time
    // double a_shore = M_PI * (1.0 - m_data->rw) * (1.0 - m_data->rw);
    // double u_shore = wwp->ql_shore / (2.0 * a_shore);
    // double a_well = 2.0 * M_PI * m_data->rw;
    // double u_well = wwp->ql_well / a_well / (2.0 * m_data->m);
    // double t = calc_sf_aver_time_step(u_shore, m_data->top_bot_bound_s[0]->v0, u_well, s[0]);

    item->sav_balance = services::SaturAverService::calc_sf_aver(qw_shore, ql_well, sf_prev, tau, m_grd, m_data);
    sf_prev = item->sav_balance;
    m_fw_data.push_back(item);

    save_sf_fw(sf_prev, wwp->fw_well / 100.0);
}

void BleCalc::save_sf_fw(double s, double fw)
{
    std::ofstream ofs(m_sffw_fn, std::ios_base::app);
    double f_sf = cs::rp::get_fbl(s, m_data->rp_n, m_data->kmu);
    ofs << s << "\t" << f_sf << "\t" << fw << "\n";

    ofs.close();
}

void BleCalc::check_conservative()
{
    double max_sum_q = -1e6;
    int cind = -1;

    for (auto& cl : m_grd->cells) {
        double sum_q = 0.0;
        for (auto& fi : cl->faces) {
            auto f = m_grd->faces[fi];
            double u = f->cl1 == cl->ind
                ? f->u
                : -f->u;
            double c = mm::FaceType::is_top_bot(f->type)
                ? 2.0 * m_data->m
                : 1.0;
            sum_q += u * f->area / c;
        }

        if (std::abs(sum_q) > max_sum_q) {
            max_sum_q = std::abs(sum_q);
            cind = cl->ind;
        }
    }

    std::string mess = common::services::string_format("residual(%i) = %.12f", cind, max_sum_q);
    logging::write_log(mess, logging::kInfo);
}

void BleCalc::save_aver_fw(const char* fn, const std::shared_ptr<AverFwSaveData> data)
{
    auto get_file_exists = [&]() {
        std::ifstream infile(fn);
        return infile.good();
    };

    bool file_exists = get_file_exists();

    std::ofstream f(fn, std::ios_base::app);

    if (!file_exists) // write headers
        f << "m\t"
          << "s\t"
          << "pv\t"
          << "fw_well\t"
          << "fw_shore\t"
          << "s_num\t"
          << "s_an\t"
          << "status\t"
          << "iter_count\t"
          //   << "cv\t"
          //   << "cg"
          << std::endl;

    f << data->m << "\t"
      << data->s_const << "\t"
      << data->data->pv << "\t"
      << data->data->fw_num_well << "\t"
      << data->data->fw_num_shore << "\t"
      << data->data->sav_num << "\t"
      << data->data->sav_an_shore << "\t"
      << data->converged << "\t"
      << data->iter_count << "\t"
      //   << data->cv << "\t"
      //   << data->cg
      << std::endl;

    f.close();
}

void BleCalc::save_pvi_s(double pvi, double pvi_fake, const std::vector<double>& s, double m)
{
    std::ostringstream oss;
    oss << "s_pvi_" << pvi << "_fpvi_" << pvi_fake << "_m_" << m << ".dat";
    std::ofstream ofs(oss.str().c_str());

    ofs << "r\ts\n";

    for (auto& cl : m_grd->cells) {
        ofs << cl->cntr << "\t" << s[cl->ind] << "\n";
    }

    ofs.close();
}

}
