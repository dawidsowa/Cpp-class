#include <math.h>

#include <fstream>
#include <iostream>
#include <string>

using std::string;

string filename("data.csv");
const int n = 200;

using namespace std;

typedef long double Real;

struct TVec {
    int dim;
    Real coor[n];
};

void ThomasTridiagonal(TVec b, TVec c, TVec a, TVec d, TVec &X) {
    int dim = b.dim;

    Real w;

    // eliminating the lower subdiagonal

    for (int i = 1; i < dim; i++) {
        w = a.coor[i] / b.coor[i - 1];

        a.coor[i] = 0.0;

        b.coor[i] -= w * c.coor[i - 1];

        d.coor[i] -= w * d.coor[i - 1];
    }

    // calculating X

    X.coor[dim - 1] = d.coor[dim - 1] / b.coor[dim - 1];

    for (int i = dim - 2; i >= 0; i--) {
        X.coor[i] = (d.coor[i] - c.coor[i] * X.coor[i + 1]) / b.coor[i];
    }
}

int main() {
    int dim = 10;

    TVec X;
    TVec T;

    Real L = 1;

    Real TL = 373.15;
    Real dT0 = -5;

    Real h = L / (dim - 1);

    X.coor[0] = 0;

    for (int i = 1; i < dim; i++) {
        X.coor[i] = X.coor[i - 1] + h;
    }

    TVec Dia, Up, Lo, Y;

    Dia.dim = dim;

    Dia.coor[0] = 1;
    Up.coor[0] = -1;
    Y.coor[0] = -dT0 * L / (dim);

    for (int i = 1; i < dim - 1; i++) {
        Up.coor[i] = 1;
        Dia.coor[i] = -2;
        Lo.coor[i] = 1;
        Y.coor[i] = 0;
    }

    Lo.coor[dim - 1] = 0;
    Dia.coor[dim - 1] = 1;
    Y.coor[dim - 1] = TL;

    ThomasTridiagonal(Dia, Up, Lo, Y, T);

    ofstream myfile;
    myfile.open(filename);

    for (int i = 0; i < dim; i++) {
        myfile << X.coor[i] << ',' << T.coor[i] << endl;
    }

    myfile.close();

    system(
        "gnuplot -p -e \""
        "set datafile separator ',';plot 'data.csv' using 1:2 with lines"
        "\"");
}