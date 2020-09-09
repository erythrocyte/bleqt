#include "shockFront.hpp"

#include "workRp.hpp"

namespace ble_src {

double get_rhs(double sc, const std::shared_ptr<PhysData> data) 
{
	if (std::abs(sc - 0.) < 1e-6) { 
		return 1e18;
	}

	double fsc = get_fbl(sc, data);

	double sdown = 0.;
	double fsdown = get_fbl(sdown, data);

	return (fsc - fsdown) / (sc - sdown);
}

double get_shock_front(const std::shared_ptr<PhysData> data)
{
	double eps = 1e-3;
	double n = 1000;
	double ds = (1 - 2. * eps) / n;

	double minDiff = 1e16;
	double result = -1.;

	for (int k = 0; k < n; k++) {
		double sc = eps + k * ds;
		double f1 = get_dfbl(sc, data);
		double f2 = get_rhs(sc, data);

		double diff = std::abs(f1 - f2);
		if (diff < minDiff) {
			minDiff = diff;
			result = sc;
		}
	}

	return result;
}

}
