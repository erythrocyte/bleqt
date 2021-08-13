#ifndef BLE_SRC_CALC_MODELS_DIAGMATRIX_H_
#define BLE_SRC_CALC_MODELS_DIAGMATRIX_H_

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <math.h>
#include <sstream>
#include <vector>

namespace ble_src::calc::models {

struct DiagMat {
    std::vector<double> A, B, C;
    std::vector<double> alpha, beta;
    void resize(int n)
    {
        A.resize(n, 0.0);
        B.resize(n, 0.0);
        C.resize(n, 0.0);
    }

    std::vector<double> solve(const std::vector<double>& F)
    {
        double sz = C.size();
        alpha.resize(sz, 0.0);
        beta.resize(sz, 0.0);
        std::vector<double> result(sz, 0.0);

        alpha[0] = -B[0] / C[0];
        beta[0] = F[0] / C[0];
        for (int i = 1; i < sz; ++i) {
            double d = A[i] * alpha[i - 1] + C[i];
            alpha[i] = -B[i] / d;
            beta[i] = (F[i] - A[i] * beta[i - 1]) / d;
        }

        result[sz - 1] = beta[sz - 1];
        for (int i = sz - 2; i >= 0; --i) {
            result[i] = alpha[i] * result[i + 1] + beta[i];
        }

        return result;
    }
};

}

#endif
