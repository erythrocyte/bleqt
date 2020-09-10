#include "workTimeStep.hpp"

#include "workRp.hpp"

namespace ble_src
{

	double get_face_uw(int fc_ind, const std::shared_ptr<Grid> grd, const std::vector<double> &init, std::shared_ptr<PhysData> data)
	{
		std::shared_ptr<Face> fc = grd->faces[fc_ind];

		if (fc->u < 0.)
		{
			return 0.; // out flow;
		}

		double s_in = (fc->cl2 == -1)
						  ? fc->bound_satur
						  : init[fc->cl2];
		double s0 = init[fc->cl1];
		double s_av = (s_in + s0) / 2.0;

		double dfbl = std::max(
			std::max(
				get_dfbl(s_in, data), get_dfbl(s0, data)),
			get_dfbl(s_av, data));

		return fc->u * dfbl;
	}

	double get_time_step(const std::shared_ptr<Grid> grd, const std::vector<double> &s, const std::shared_ptr<InputData> data)
	{
		double result = 1e19;
		for (auto &cl : grd->cells)
		{
			double uw_in = 0.;
			double uw_left = get_face_uw(cl->fl, grd, s, data->phys);
			if (uw_left > 0.)
				uw_in += uw_left;
			double uw_right = get_face_uw(cl->fr, grd, s, data->phys);
			if (uw_right > 0.)
				uw_in += uw_right;

			double cell_size = std::abs(cl->xr - cl->xl);

			if (uw_in > 1e-10)
			{
				double t = (data->satSetts->cur_val * cell_size) / uw_in;
				if (t > 1e-8 && t < result)
					result = t;
			}
		}

		return result;
	}

} // namespace ble_src
