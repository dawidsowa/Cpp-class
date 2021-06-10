#include <math.h>

#include <iostream>

using namespace std;

double riemann(double a, double b, int n, double (*func)(double)) {
    double h = (b - a) / n;
    double sum = 0;

    for (double x = a; x <= b; x = x + h) {
        sum += h * (*func)(x);
    }

    return sum;
}

double riemann_improper(double a, double m, double h, double (*func)(double)) {
    double sum = 0;
    double f;
    double x = a;

    do {
        f = (*func)(x);
sum += h * (*func)(x);
x += h;
    } while (f > m);



    return sum;
}


double ex2(double x) {
    return exp(-pow(x, 2));
}

int main() {
    double a = 0;
    double b = M_PI * 2;
    int n = 100;

    double r = riemann(a, b, 1000, sin);
    cout << "r= " << r << endl;

    double einf = riemann_improper(a, 0.0001, 0.0001, ex2); // sqrt(pi)/2

    cout << "einf= " << einf << endl;

    return 0;
}