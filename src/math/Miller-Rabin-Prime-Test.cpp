#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;

vector<ull> prime_list = {2, 7, 61};
//~ int range
//{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}
//~ long long range
//use __int128_t instead of ull
//O(klog^3(x))

ull mod_pow(ull a, ull b, ull M) {
    if(b == 0) return 1;

    ull temp = mod_pow(a, b / 2, M);

    if(b & 1) return (((temp % M) * (temp % M)) % M * (a % M)) % M;
    else return ((temp % M) * (temp % M)) % M;
}

bool miller_rabin(ull x) {
    if(x < 2) return false;

    bool ret = true;
    for(auto& p : prime_list) {
        if(x == p) return true;
        ull k = x - 1;
        while(true) {
            ull val = mod_pow(p, k, x) % x;

            if(val == x - 1) {
                ret = true;
                break;
            }
            if(k & 1) {
                ret = (val == 1 || val == x - 1);
                break;
            }
        
            k /= 2;
        }

        if(!ret) break;
    }

    return ret;
}