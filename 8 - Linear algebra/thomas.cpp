#include <stdio.h>
#include <stdlib.h> /* srand, rand */
#include <time.h>   /* time */

#include <cmath>    // std::abs
#include <iomanip>  // std::setprecision
#include <iostream>

using namespace std;

const int n = 10000;

typedef long double Real;

// struct TMat{ int degg; Real valua[n][n];};

struct TVec {
    int dimm;
    Real coor[n];
};

void ThomasTridiagonal(TVec b, TVec c, TVec a, TVec d, TVec &X) {
    int dim = b.dimm;

    Real w;

    // eliminating the lower subdiagonal

    for (int i = 1; i < dim; i++) {
        w = a.coor[i] / b.coor[i - 1];

        a.coor[i] = 0.0;

        b.coor[i] -= w * c.coor[i];

        d.coor[i] -= w * d.coor[i - 1];
    }

    // calculating X

    X.coor[dim - 1] = d.coor[dim - 1] / b.coor[dim - 1];

    for (int i = dim - 2; i >= 0; i--)

        X.coor[i] = (d.coor[i] - c.coor[i] * X.coor[i + 1]) / b.coor[i];
}

int main() {
    int dim = 2001;

    TVec Dia, Up, Lo, Be, X;  // using Up[i],Lo[i] for 0<i<dim

    Dia.dimm = dim;

    for (int i = 0; i < dim; i++) {
        Dia.coor[i] = -2.0;
        Up.coor[i] = +1.0;
        Lo.coor[i] = +1.0;

        Be.coor[i] = 0.0;
        X.coor[i] = 0.0;
    }

    Be.coor[0] = -1.0;

    Be.coor[dim - 1] = -5.0;

    clock_t start = clock();

    cout << "time =" << clock() << endl;

    for (int k = 0; k < 1000; k++) {  // So the time can be calculated
        ThomasTridiagonal(Dia, Up, Lo, Be, X);
    }

    printf("Execution time: %lu ms\n", (clock() - start) / 1000);

    cout << "X[1000]=" << X.coor[1000] << endl;

    printf("X[1000]= %0.20Lf \n", X.coor[1000]);

    cout << "time =" << clock() << endl;

    return 0;
}