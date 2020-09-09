#include "makeGrid.hpp"

#include "shockFront.hpp"

namespace ble_src {

std::shared_ptr<Grid> make_regular_grid(const std::shared_ptr<InputData> data) 
{
	std::shared_ptr<Grid> result (new Grid());
	double step = data->grd->l / data->grd->n;

	for (int k = 0; k < data->grd->n; k++) { // cells
		std::shared_ptr<Face> fc (new Face());
		fc->ind = k;
		fc->x = step * k;
		fc->cl1 = k;
		fc->cl2 = k - 1;
		fc->type = (k == 0)
			? FaceType::kWell
			: FaceType::kInner;
		result->faces.push_back(fc);

		std::shared_ptr<Cell> cl (new Cell());
		cl->ind = k;
		cl->xl = k * step;
		cl->xr = (k + 1) * step;
		cl->cntr = (cl->xr + cl->xl) / 2.0;
		cl->fl = k;
		cl->fr = k + 1;
		cl->volume = step;
		cl->poro = data->phys->poro;
		cl->perm = data->phys->perm;
		result->cells.push_back(cl);
	}
	
	// last face;
	std::shared_ptr<Face> fc(new Face());
	fc->ind = data->grd->n;
	fc->x = data->grd->l;
	fc->cl1 = data->grd->n -1;
	fc->type = FaceType::kContour;
	fc->bound_press = 1.;
	fc->bound_satur = 1.;
	result->faces.push_back(fc);

	return result;
}

std::shared_ptr<Grid> make_grid(const std::shared_ptr<InputData> data)
{
	switch (data->grd->type) { 
		case GridTypeEnum::kRegular:
			return make_regular_grid(data);
		case GridTypeEnum::kRadial:
		case GridTypeEnum::kSpheric:
		default:
			return std::make_shared<Grid>();
	}
}

}
