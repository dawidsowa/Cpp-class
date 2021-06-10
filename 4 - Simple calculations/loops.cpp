#include <math.h>

#include <iostream>
using namespace std;

double geometric_series(float a, float q) {
    double s = 0;
    double aq = a;

    while (abs(aq) > 0.000001) {
        s += aq;

        aq *= q;
    }

    return s;
}

int main() {
    double g = geometric_series(1, -0.99999);

    cout << "g= " << g << endl;

    return 0;
}