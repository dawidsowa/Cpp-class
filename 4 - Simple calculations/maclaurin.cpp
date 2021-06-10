#include <math.h>

#include <iostream>
using namespace std;

double sine(double x, int n) {
    double sum = 0;
    double den = 1;

    for (int i = 0; i <= n; i++) {
        den *= (2.0 * i + 1.0);
        sum += pow(-1.0, i) * pow(x, 2.0 * i + 1.0) / den;

        if (i % 1 == 0) {
            printf(" n=%d suma=%20.12f \n", i, sum);
        };
    }

    return sum;
}

int main() {
    double x = 0.2;
    double target = sin(x);

    double s = sine(x, 10);

    cout << "s= " << s << endl;
    cout << "target= " << target << endl;

    return 0;
}