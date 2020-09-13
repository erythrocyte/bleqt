#include "pressureSolver.hpp"

#include "diagMatrix.hpp"
#include "workSigma.hpp"

namespace ble_src {

double get_h(const std::shared_ptr<Face> fc, const std::shared_ptr<Grid> grd)
{
	return (fc->cl2 == -1)
		? std::abs(grd->cells[fc->cl1]->cntr - fc->x)
		: std::abs(grd->cells[fc->cl1]->cntr - grd->cells[fc->cl2]->cntr);
}

std::vector<double> solve_press(const std::shared_ptr<Grid> grd, const std::vector<double>& s, const std::shared_ptr<PhysData> data)
{
	DiagMat ret;
	ret.resize(grd->cells.size());

	std::vector<double> rhs(grd->cells.size(), 0.0);

	for (auto &fc: grd->faces) {
		double sigma = get_face_sigma(fc, s, data, grd);
		double h = get_h(fc, grd);

		double cf = fc->area * sigma / h;

		if (fc->type != FaceType::kInner) {
			rhs[fc->cl1] += cf * fc->bound_press;
			ret.C[fc->cl1] += cf;
		}
		else {
			ret.C[fc->cl1] += cf;
			ret.A[fc->cl1] -= cf;
			ret.B[fc->cl2] -= cf;
			ret.C[fc->cl2] += cf;
		}
	}

	return ret.solve(rhs);
}

void calc_u(const std::vector<double>& p, const std::vector<double>& s, const std::shared_ptr<PhysData> data, 
		std::shared_ptr<Grid> grd)
{
	for (auto &fc: grd->faces) {
		double sigma = get_face_sigma(fc, s, data, grd);
		double h = get_h(fc, grd);

		double p1 = p[fc->cl1];
		double p2 = (fc->cl2 == -1)
			? fc->bound_press
			: p[fc->cl2];

		fc->u = - fc->area * sigma * (p1 - p2) / h;
	}
}

}
