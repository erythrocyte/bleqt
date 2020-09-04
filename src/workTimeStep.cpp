#include "workTimeStep.hpp"

#include "workRp.hpp"

namespace ble_src {

double get_face_uw(int fc_ind, const std::shared_ptr<Grid> grd, const std::vector<double>&init, std::shared_ptr<PhysData> data)
{
	std::shared_ptr<Face> fc = grd->faces[fc_ind];
	double s = (fc->u > 0.)
		? (fc->cl2 == -1)
			? fc->bound_satur
			: init[fc->cl2]
		: init[fc->cl1];
	
	return fc->u * get_fbl(s, data);
}

double get_time_step(const std::shared_ptr<Grid> grd, const std::vector<double>&s, const std::shared_ptr<InputData> data)
{
	double result = 1e19;
	for (auto& cl: grd->cells) {
		double u_in = 0.;
		double uw_left = get_face_uw(cl->fl, grd, s, data->phys);
		if (uw_left > 0.)
			u_in += uw_left;
		double uw_right = get_face_uw(cl->fr, grd, s, data->phys);
		if (uw_right > 0.)
			u_in += uw_right;

		double cell_size = std::abs(cl->xr - cl->xl);

		double t = u_in * data->satSetts->cur_val / cell_size;
		if (t > 1e-8 && t < result)
			result = t;
	}

	return result;
}


}
