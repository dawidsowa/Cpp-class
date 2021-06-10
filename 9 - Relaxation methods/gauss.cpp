#include <math.h>

#include <iostream>
using namespace std;

const int n = 4;
typedef long double Real;
struct TMat {
    int deg;
    Real value[n][n];
};
struct TVec {
    int dim;
    Real coor[n];
};

int steps = 1000;

void Jacobi(TMat A, TVec B, TVec &X) {
    Real erro, temp;

    int count = 0;
    do {
        count++;
        erro = 0;
        for (int i = 0; i < A.deg; i++) {
            temp = B.coor[i];
            for (int j = 0; j < A.deg; j++) {
                if (i != j) {
                    temp -= A.value[i][j] * X.coor[j];
                }
            }
            temp /= A.value[i][i];
            erro += pow(X.coor[i] - temp, 2);
            X.coor[i] = temp;
        }
        cout << "iteration " << count << " error=" << erro << endl;
    } while (erro > 1.0e-30);
}

int main() {
    TMat A;
    Real suma;
    A.deg = n;

    for (int i = 0; i < n; i++) {
        suma = 0;
        for (int j = 0; j < n; j++) {
            A.value[i][j] = 2 * (double(rand()) / RAND_MAX) - 1.0;
            if (i != j) {
                suma += abs(A.value[i][j]);
            }
        }
        for (int j = 0; j < n; j++) {
            A.value[i][j] / suma;
        }
        A.value[i][i] = 1.001;
    }

    TVec Y;
    Y.dim = n;

    for (int i = 0; i < n; i++) {
        Y.coor[i] = 2 * (double(rand()) / RAND_MAX) - 1.0;
    }

    TVec B;
    B.dim = n;

    for (int i = 0; i < n; i++) {
        B.coor[i] = 0;
        for (int j = 0; j < n; j++) {
            B.coor[i] += A.value[i][j] * Y.coor[j];
        }
    }

    TVec X;
    X.dim = n;

    Jacobi(A, B, X);

    cout << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%7.4Lf ", A.value[i][j]);
        }
        cout << endl;
    }
}