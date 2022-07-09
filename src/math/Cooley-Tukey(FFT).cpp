#include <bits/stdc++.h>

using namespace std;
using cpx = complex<double>;
//Cooley-Tukey FFT
void FFT(vector<cpx>& A, cpx w) {
    int n = (int)A.size();
    if(n == 1) return;

    vector<cpx> even(n / 2), odd(n / 2);
    for(int i = 0; i < n; ++i) {
        if(i & 1) odd[i / 2] = A[i];
        else even[i / 2] = A[i];
    }

    FFT(even, w * w);
    FFT(odd, w * w);

    cpx w_e(1, 0);

    for(int i = 0; i < n / 2; ++i) {
        A[i] = even[i] + w_e * odd[i];
        A[i + n / 2] = even[i] - w_e * odd[i];
        w_e *= w;
    }
}

void product(vector<cpx>& A, vector<cpx>& B) {
    int n = (A.size() <= B.size()) ? ceil(log2((double)B.size())) : ceil(log2((double)A.size()));
    n = pow(2, n + 1);

    A.resize(n);
    B.resize(n);
    vector<cpx> C(n);

    cpx w(cos(2 * acos(-1) / n), sin(2 * acos(-1) / n));
    FFT(A, w);
    FFT(B, w);

    for(int i = 0; i < n; ++i) C[i] = A[i] * B[i];

    FFT(C, cpx(1, 0) / w);
    for(int i = 0; i < n; ++i) {
        C[i] /= cpx(n, 0);
        C[i] = cpx(round(C[i].real()), round(C[i].imag()));
    }
}

/*
void FFT(vector<cpx>& A, bool invert) {
    int n = (int)A.size();

    for(int i = 1, j = 0; i < n; ++i) {
        int bit = n >> 1;

        while(j >= bit) {
            j -= bit;
            bit >>= 1;
        }
        j += bit;

        if(i < j) swap(A[i], A[j]);
    }    

    for(int length = 2; length <= n; length <<= 1) {
        double ang = 2 * PI / length * (invert ? -1 : 1);
        cpx w(cos(ang), sin(ang));

        for(int i = 0; i < n; i += length) {
            cpx w_i(1, 0);
            for(int j = 0; j < length / 2; ++j) {
                cpx u = A[i + j], v = A[i + j + length / 2] * w_i;
                A[i + j] = u + v, A[i + j + length / 2] = u - v;
                w_i *= w;
            }
        }
    }
    
    if(invert) {
        for(int i = 0; i < n; ++i) {
            A[i] /= cpx(n, 0);
            A[i] = cpx(round(A[i].real()), round(A[i].imag()));
        }
    }
} // referenced from https://blog.myungwoo.kr/54
*/ //faster version of FFT