#include <math.h>
#include <stdio.h>

#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>

const int n = 20;

using namespace std;

FILE* fp;

typedef long double Real;

struct TVec {
    int dim;
    Real coor[n];
};

void neumann(TVec& Tp, TVec& T, Real T0, Real dTL, Real dx, Real dt) {
    Real Ta = Tp.coor[n - 2] + 2 * dx * dTL;  // Tp(L+1)

    T.coor[0] = T0;
    for (int i = 1; i <= n; i++) {
        T.coor[i] = Tp.coor[i + 1] * dt / pow(dx, 2) +
                    (1 - 2 * dt / pow(dx, 2)) * Tp.coor[i] +
                    dt / pow(dx, 2) * Tp.coor[i - 1];
    }
    T.coor[n - 1] = Ta * dt / pow(dx, 2) +
                    (1 - 2 * dt / pow(dx, 2)) * Tp.coor[n - 1] +
                    dt / pow(dx, 2) * Tp.coor[n - 2];
    ;

    for (int i = 0; i < n; i++) {
        Tp.coor[i] = T.coor[i];
    }
}

int main() {
    TVec X, T, Tp;

    Real L = 1;

    Real T0 = 393.15;
    Real dTL = 0;
    Real Tinit = 273.15;

    Real dx = L / (n - 1);
    Real dt = 0.8 * pow(dx, 2) / 2;

    X.coor[0] = 0;
    Tp.coor[0] = Tinit;

    for (int i = 1; i < n; i++) {
        X.coor[i] = X.coor[i - 1] + dx;
        Tp.coor[i] = Tinit;
    }

    int col = 1;

#ifdef WIN32  // Create pipe
    fp = _popen("gnuplot -persist", "w");
#else
    fp = popen("gnuplot -persist", "w");
#endif

    for (int k = 0; k < 1001; k++) {
        neumann(Tp, T, T0, dTL, dx, dt);  // Calculations

        fprintf(fp, "plot '-' using 1:2 with lines\n");
        for (int i = 0; i < n; i++) {
            fprintf(fp, "%Lf %Lf\n", X.coor[i],
                    T.coor[i]);  // Pass the coordinates
        }
        fprintf(fp, "e\n");                   // End of data
        fprintf(fp, "set yrange restore\n");  // Restore Yrange
        fflush(fp);                           // Send to pipe

        this_thread::sleep_for(chrono::milliseconds(200));  // Wait 0.2s
    }

#ifdef WIN32  // Close pipe
    _pclose(fp);
#else
    pclose(fp);
#endif
}