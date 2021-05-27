#include <math.h>

#include <fstream>
#include <iostream>
#include <string>

using std::string;

string filename("data.csv");
const int n = 10;

using namespace std;

typedef long double Real;

struct TVec {
    int dim;
    Real coor[n];
};

int main() {
    TVec X;
    TVec T;

    Real L = 1;

    Real T0 = 293.15;
    Real TL = 373.15;

    Real h = L / (n - 1);

    X.coor[0] = 0;

    for (int i = 1; i < n; i++) {
        X.coor[i] = X.coor[i - 1] + h;
    }

    // T = ax + b
    // T(0) = a*0 + b -> b = T0
    // T(L) = a*L + T0 -> b = (TL - T0) / L
    Real a = (TL - T0) / L;

    for (int i = 0; i < n; i++) {
        T.coor[i] = a * X.coor[i] + T0;
    }

    ofstream myfile;
    myfile.open(filename);

    for (int i = 0; i < n; i++) {
        myfile << X.coor[i] << ',' << T.coor[i] << endl;
    }

    myfile.close();

    system(
        "gnuplot -p -e \""
        "set datafile separator ',';plot 'data.csv' using 1:2 with lines"
        "\"");
}