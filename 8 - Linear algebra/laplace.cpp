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

Real DetLaplace(TMat A) {
    if (A.deg == 0) {
        return 1.0;
    } else if (A.deg == 1) {
        return A.value[0][0];
    } else {
        TMat B;  // Minor
        Real det = 0.0, sig = 1.0;

        for (int k = 0; k < A.deg; k++) {
            B.deg = A.deg - 1;
            for (int i = 0; i < B.deg; i++) {
                for (int j = 0; j < B.deg; j++) {
                    if (i < k) {
                        B.value[i][j] = A.value[i][j + 1];
                    } else {
                        B.value[i][j] = A.value[i + 1][j + 1];
                    }
                }
            }
            // for (int i = 0; i < B.deg; i++) {
            //     for (int j = 0; j < B.deg; j++) {
            //         cout << B.value[i][j] << " ";
            //     }
            //     cout << endl;
            // }
            // cout << endl;

            det += sig * A.value[k][0] * DetLaplace(B);
            sig = -sig;
        }
        return det;
    }
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
        cout << "i= " << i << " det=" << DetLaplace(A) << endl;
    }

    return 0;
}