#include <math.h>

#include <iostream>
using namespace std;

double deriv(double x, double (*func)(double), double h) {
    return ((*func)(x + h) - (*func)(x)) / h;
}

int main() {
    double d = deriv(0.5, log, 0.0000001);

    cout << "d= " << d << endl;

    return 0;
}