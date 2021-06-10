#include <math.h>

#include <iostream>
using namespace std;

int n = 40;

const bool recursive = false;

unsigned long long int fac_i(int n) {
    if (n == 0) {
        return 1;
    } else {
        return fac_i(n - 1) * n;
    }
}

long double fac_r(int n) {
    if (n == 0) {
        return 1;
    } else {
        return fac_r(n - 1) * n;
    }
}

int main() {
    int n;

    cout << "n = ";
    cin >> n;

    if (recursive) {
        if (n > 20) {
            cout << n << "! = " << fac_r(n);
        } else {
            cout << n << "! = " << fac_i(n);
        }
    } else {
        if
            long double fac = 1;

        for (int i = 1; i <= n; i++) {
            fac *= i;
        }

        cout << n << "! = " << fac;
    }

    return 0;
}