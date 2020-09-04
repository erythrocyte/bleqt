#include "pressureSolver.hpp"

#include "diagMatrix.hpp"
#include "workSigma.hpp"

namespace ble_src {

std::vector<double> solve_press(const std::shared_ptr<Grid> grd, const std::vector<double>& s)
{
	DiagMat ret;
	ret.resize(grd->cells.size());

	std::vector<double> rhs(grd->cells.size(), 0.0);

	for (auto &fc: grd->faces) {
		double sigma = (fc->cl2 == -1)
			? get_cell_sigma()
			: get_face_sigma();
		double h = (fc->cl2 == -1)
			? std::abs(grd->cells[fc->cl1]->cntr - fc->x)
			: std::abs(grd->cells[fc->cl1]->cntr - grd->cells[fc->cl2]->cntr);

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

}
