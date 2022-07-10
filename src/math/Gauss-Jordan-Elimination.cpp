#include <bits/stdc++.h>

using namespace std;

typedef struct _Matrix{
    int N;
    vector<vector<double>> matrix;

    _Matrix(int X) {
        N = X;
        matrix.resize(N, vector<double>(N + 1));
    } // N by N + 1 matrix
} Matrix;

void row_swap(Matrix& A, int i) {
    vector<double> temp = A.matrix[i];
    A.matrix.erase(A.matrix.begin() + i);
    A.matrix.push_back(temp);
}

//Gauss-Jordan Elmination
void gauss_jordan(Matrix& A) {
    for(int i = 0; i < A.N; ++i) {
        while(A.matrix[i][i] == 0) row_swap(A, i); //check diagonal components are non-zero, when if, rotate row(swap)

        for(int j = 0; j < A.N; ++j) { //make RREF
            if(i != j) {
                double ratio = A.matrix[j][i] / A.matrix[i][i];
                for(int k = 0; k <= A.N; ++k) {
                    A.matrix[j][k] = A.matrix[j][k] - ratio * A.matrix[i][k];
                }
            }
        }
    }
}