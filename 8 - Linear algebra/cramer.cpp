#include <math.h>

#include <iostream>
#include <stdexcept>

// #include "matrix_operations.h"
using namespace std;

const short s = 3;

void print_array(double A[][s]) {
    for (short i = 0; i <= s - 1; i++) {
        for (short j = 0; j <= s - 1; j++) {
            cout << A[i][j] << ' ';
        }
        cout << endl;
    }

    cout << endl;
}

int det(double (&A)[][s]) {
    int sum = 0;

    int C[s][s * 2];

    for (short i = 0; i <= s - 1; i++) {
        for (short j = 0; j <= s - 1; j++) {
            C[i][j] = A[i][j];
            C[i][j + s] = A[i][j];
        }
    }

    for (short j = 0; j <= s - 1; j++) {
        int p = 1;
        for (short k = 0; k <= s - 1; k++) {
            p *= C[k][j + k];
        }
        sum += p;
    }

    for (short j = s * 2 - 1; j > s - 1; j--) {
        int p = 1;
        for (short k = 0; k <= s - 1; k++) {
            p *= C[k][j - k];
        }
        sum -= p;
    }

    return sum;
}

int main() {
    double X[s][s] = {{2, 5, 3}, {4, 2, 5}, {3, 8, 4}};
    double Y[s] = {5, 4, 9};
    double B[s];

    double detX = det(X);
    if (detX == 0.0) {
        throw invalid_argument("determinant can't be equal to 0");
    }
    cout << "detX= " << detX << endl;

    // arr is equal to &arr[0] by default

    for (short k = 0; k < s; k++) {
        double C[3][3];
        for (int i = 0; i < s; i++) {
            for (int j = 0; j < s; j++) {
                if (j == k) {
                    C[i][j] = Y[i];
                } else {
                    C[i][j] = X[i][j];
                }
            }
        }

        B[k] = det(C) / detX;
    }

    for (int i = 0; i < s; i++) {
        printf("a%d=%f\n", i, B[i]);
    }
}