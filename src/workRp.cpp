#include "workRp.hpp"

#include <cmath>

namespace ble_src{

double get_kw(double s, const std::shared_ptr<PhysData> data)
{
	return std::pow(s, data->n_wat);
}

double get_koil(double s, const std::shared_ptr<PhysData> data)
{
	return std::pow((1. - s), data->n_oil);
}

double get_sigma(double s, const std::shared_ptr<PhysData> data)
{
	return get_kw(s, data) + data->kmu * get_koil(s, data);
}

double get_fbl(double s, const std::shared_ptr<PhysData> data) 
{
	double kw = get_kw(s, data);
	double sig = get_sigma(s, data);

	return kw / sig;
}

}
