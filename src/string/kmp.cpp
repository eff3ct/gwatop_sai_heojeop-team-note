#include <bits/stdc++.h>

using namespace std;

void get_fail(string& P, vector<int>& fail) {
    for(int i = 1, j = 0; i < (int)P.length(); ++i) {
        while(j && P[i] != P[j]) j = fail[j - 1];
        if(P[i] == P[j]) fail[i] = ++j;
    }
}

void KMP(string& T, string& P) { //O(N + M)
    int T_len = (int)T.length();
    int P_len = (int)P.length();

    vector<int> fail(P_len);
    get_fail(P, fail);

    vector<int> ret;

    for(int i = 0, j = 0; i < T_len; ++i) {
        while(j && T[i] != P[j]) j = fail[j - 1];

        if(T[i] == P[j]) {
            if(j == P_len - 1) { //matching success
                ret.push_back(i - P_len + 2);
                j = fail[j];
            }
            else j++;
        }
    }

    cout << (int)ret.size() << '\n';
    for(auto& element : ret) cout << element << '\n';
}