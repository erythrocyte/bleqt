#ifndef BLE_SRC_DIAGMATRIX_H_
#define BLE_SRC_DIAGMATRIX_H_

#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <math.h>
#include <cmath>
#include <fstream>
#include <algorithm>

namespace ble_src{

struct DiagMat{
	std::vector<double> A, B, C;
	std::vector<double> alpha, beta;
	void resize(int n){ A.resize(n,0.0); B.resize(n,0.0); C.resize(n,0.0); }

	void solve(const std::vector<double>& F, std::vector<double>& ans){
		double sz = C.size();
		alpha.resize(sz, 0.0);
		beta.resize(sz, 0.0);

		alpha[0] = -B[0]/C[0];
		beta[0] = F[0]/C[0];
		for (int i=1; i<sz; ++i){
			double d = A[i]*alpha[i-1]+C[i];
			alpha[i] = -B[i]/d;
			beta[i] = (F[i]-A[i]*beta[i-1])/d;
		}

		ans[sz-1] = beta[sz-1];
		for (int i=sz-2; i>=0; --i){
			ans[i] = alpha[i]*ans[i+1]+beta[i];
		}
	}
}

}


#endif

