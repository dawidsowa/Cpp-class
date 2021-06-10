#include <math.h>

#include <iostream>
#include <stdexcept>
using namespace std;

unsigned long long int coeff(int n, int k) {
    if (k > n) {
        throw invalid_argument("k can't greater than n");
    } else if (k == 0 || k == n) {
        return 1;
    } else {
        return coeff(n - 1, k - 1) + coeff(n - 1, k);
    }
}

int main() {
    int n;
    cout << "n = ";
    cin >> n;

    int k;
    cout << "k = ";
    cin >> k;

    int c = coeff(n, k);

    cout << "c= " << c;

    return 0;
}