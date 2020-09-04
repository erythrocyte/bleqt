#include "workSigma.hpp"

#include "workRp.hpp"

namespace ble_src {

double get_face_sigma(const std::shared_ptr<Face> fc, const std::vector<double> sats, const std::shared_ptr<PhysData> data)
{
	double s = (fc->u > 0.)
		? sats[fc->cl1]
		: (fc->cl2 == -1)
			? fc->bound_satur
			: sats[fc->cl2];
	
	return get_sigma(s, data);
}

}
