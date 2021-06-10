#include <math.h>

#include <array>
#include <iostream>
using namespace std;

double f(double x) {
    return pow(x, 3) + 3 * pow(x, 2) - 2 * x * sin(1 + pow(x, 2));
}

void values(double a, double b, double (*func)(double), double x[], double v[],
            int n) {
    double h = (b - a) / (n - 1);

    double xi = a;

    for (short i = 0; i < n; i++) {
        x[i] = xi;
        v[i] = (*func)(xi);

        xi += h;
    }
}

int main() {
    int n = 10;
    double v[n];
    double x[n];

    values(0, M_PI_2, sin, x, v, n);

    for (int i = 0; i < n; i++) {
        printf("f(%f)=%f\n", x[i], v[i]);
    }

    double a = 2;
    double b = 7;
    n = (b - a) / 0.01 + 1;
    double o[n];
    double p[n];

    values(a, b, f, o, p, n);

    for (int i = 0; i < n; i++) {
        printf("f(%f)=%f\n", o[i], p[i]);
    }

    return 0;
}