#include <math.h>

#include <iostream>
using namespace std;

// y' = 0.5 * (t - y)
// y0 =
// t e 0 3

int main() {
    double a = 0;
    double b = 1;
    double h = 0.01;

    double y0 = 0;
    double y0p = 1;

    int n = 1 + (b - a) / h;

    double x[n];
    double y[n];

    x[0] = a;
    y[0] = y0;

    x[1] = a + h;
    y[1] = y0 + h * y0p;

    for (int i = 2; i < n; i++) {
        x[i] = x[i - 1] + h;
        y[i] = ((2 - 2 * h) * y[i - 1] - y[i - 2]) / (1 + 2 * h);

        cout << "x= " << x[i] << endl;
        cout << "y= " << y[i] << endl;
        // cout << "ye= " << 3 * exp(-0.5 * x[i]) - 2 + x[i] << endl;
    }

    return 0;
}