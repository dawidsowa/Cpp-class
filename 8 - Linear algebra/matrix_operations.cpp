#include <math.h>

#include <iostream>
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

void add(int (&A)[][s], int (&B)[][s], int (&C)[][s]) {
    for (short i = 0; i <= s - 1; i++) {
        for (short j = 0; j <= s - 1; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

void mult_by_number(int (&A)[][s], int b, int (&C)[][s]) {
    for (short i = 0; i <= s - 1; i++) {
        for (short j = 0; j <= s - 1; j++) {
            C[i][j] = A[i][j] * b;
        }
    }
}

void mult_arrays(int (&A)[][s], int (&B)[][s], int (&C)[][s]) {
    C[s][s] = {0};  // Very important!

    for (short i = 0; i <= s - 1; i++) {
        for (short j = 0; j <= s - 1; j++) {
            for (short k = 0; k <= s - 1; k++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

int det(int (&A)[][s]) {
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
    int A[3][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}};
    int B[3][3] = {{0, 1, 2}, {3, 4, 5}, {6, 7, 8}};
    int C[3][3];

    add(A, B, C);

    print_array(C);

    mult_by_number(A, 3, C);

    print_array(C);

    mult_arrays(A, B, C);

    print_array(C);


    int d = det(A);
    cout << d;

    return 0;
}