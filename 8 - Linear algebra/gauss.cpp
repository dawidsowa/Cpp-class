#include <math.h>
#include <unistd.h>

#include <iostream>
using namespace std;

const int n = 10;

typedef long double Real;

struct TMat {
    int deg;
    Real value[n][n];
};

Real DetGauss(TMat A) {
    Real det = 1, coef;
    for (int s = A.deg; s > 0; s--) {
        Real mm = abs(A.value[s - 1][0]);
        int j = 0;
        for (int k = 1; k < s; k++) {
            if (abs(A.value[s - 1][k]) > mm) {
                mm = abs(A.value[s - 1][k]);
                j = k;
            }
            if ((s + j) % 2 == 0) {
                det = -det;
            }
            if (mm == 0) {
                return 0;
            }
            det *= A.value[s - 1][j];
            for (int i = 0; i < s - 1; i++) {
                coef = A.value[i][j] / A.value[s - 1][j];
                for (int k = 0; k < s - 1; k++) {
                    if (k < j) {
                        A.value[i][k] -= coef * A.value[s - 1][k];
                    } else {
                        A.value[i][k] =
                            A.value[i][k + 1] - coef * A.value[s - 1][k + 1];
                    }
                }
            }
        }
    }
    return det;
}

int main() {
    TMat A;

    for (int i = 0; i < n; i++) {  // All to 0
        for (int j = 0; j < n; j++) {
            A.value[i][j] = 0.0;
            // printf("B[%d][%d]=%Lf\n", i, j, A.value[i][j]);
        }
    }
    for (int i = 0; i < n; i++) {  // Diagonal to 5
        A.value[i][i] = 5.0;
    }
    for (int i = 1; i < n; i++) {
        A.value[i][i - 1] = 2.0;
        A.value[i - 1][i] = 3.0;
    }

    for (int i = 1; i <= n; i++) {
        A.deg = i;
        cout << "i= " << i << " det=" << DetGauss(A) << endl;
    }

    return 0;
}