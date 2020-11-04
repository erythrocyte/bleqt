#include "saturSolverNum.hpp"

#include "workRp.hpp"

namespace ble_src {

std::vector<double> solve_explicit(const double tau, const std::vector<double>& init, const std::shared_ptr<InputData> data,
		const std::shared_ptr<Grid> grd)
{
	std::vector<double> result(init.size(), 0.);

	std::vector<double> dvs(grd->cells.size(), 0.);

	for (auto &fc: grd->faces) {
		double s = (fc->u > 0.)
			? (fc->cl2 == -1)
				? fc->bound_satur
				: init[fc->cl2]
			: init[fc->cl1];
		
		double fbl = get_fbl(s, data->phys);
		double cf = fc->u * fbl * fc->area;
		dvs[fc->cl1] += cf;
		if (fc->cl2 != -1)
			dvs[fc->cl2] -= cf;
	}

	for (auto &cl: grd->cells) {
		result[cl->ind] = init[cl->ind] + tau / (data->phys->poro * cl->volume) * dvs[cl->ind];

		if (cl->ind > 0)
		{
			if (result[cl->ind-1] > result[cl->ind])
			{
				std::cout << "for cell ind = " << cl->ind - 1 << " bad calc" << std::endl;
				std::cout << "\t vol = " << grd->cells[cl->ind-1]->volume << std::endl;
				std::cout << "\t dvs = " << dvs[cl->ind] << std::endl;
			}
		}
	}

	return result;
}

std::vector<double> solve_satur(const double tau, const std::vector<double>& init, const std::shared_ptr<InputData> data,
		const std::shared_ptr<Grid> grd)
{
	switch(data->satSetts->type) {
		case SaturSolverType::TypeEnum::kExplicit:
			return solve_explicit(tau, init, data, grd);
		case SaturSolverType::TypeEnum::kImplicit:
		default:
			return solve_explicit(tau, init, data, grd);
	}
}

}
