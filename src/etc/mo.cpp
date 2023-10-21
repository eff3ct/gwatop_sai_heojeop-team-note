#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,avx,avx2")

#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ppii = pair<int, pii>;

const int sqrt_N = 317;

class sqrt_decomposition {
    private:
        int arr[101010];
        int bucket[101010];
        int bucket_cnt[320][101010];
        int number_cnt[320][101010];

    public:
        sqrt_decomposition() {
            fill(arr, arr + 101010, 0);
            fill(bucket, bucket + 101010, 0);
            for(int i = 0; i < 320; ++i) {
                fill(number_cnt[i], number_cnt[i] + 101010, 0);
                fill(bucket_cnt[i], bucket_cnt[i] + 101010, 0);
            }
        }

        void update(int idx, int val) {
            int n = idx / sqrt_N;
            if(val > 0) {
                bucket_cnt[n][ number_cnt[n][idx] ]--;
                number_cnt[n][idx]++;
                bucket_cnt[n][ number_cnt[n][idx] ]++;
                bucket[n] = max(bucket[n], number_cnt[n][idx]);
                arr[idx] += val;
            }
            else {
                bucket_cnt[n][ number_cnt[n][idx] ]--;
                number_cnt[n][idx]--;
                bucket_cnt[n][ number_cnt[n][idx] ]++;
                if(bucket_cnt[n][ bucket[n] ] == 0) bucket[n]--;
                arr[idx] += val;
            }
        }        

        int query() {
            int M = 0, idx = -1;
            for(register int i = sqrt_N - 1; i >= 0; --i) {
                if(M < bucket[i]) {
                    M = bucket[i];
                    idx = i;
                }
            }

            int ret = sqrt_N * idx + sqrt_N - 1;
            M = arr[sqrt_N * idx + sqrt_N - 1];
            for(register int i = sqrt_N - 1; i >= 0; --i) {
                if(M < arr[sqrt_N * idx + i]) {
                    M = arr[sqrt_N * idx + i];
                    ret = sqrt_N * idx + i;
                }
            }

            return ret;
        }
};

struct query {
    int start, end, idx;
};

void add(int idx, vector<int>& A, sqrt_decomposition& sq) {
    sq.update(A[idx], 1);
}

void del(int idx, vector<int>& A, sqrt_decomposition& sq) {
    sq.update(A[idx], -1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);

    int n, q; cin >> n >> q;
    vector<int> A(n);
    for(int& e : A) cin >> e;

    vector<int> st(A);
    sort(st.begin(), st.end());

    for(register int i = 0; i < n; ++i) 
        A[i] = lower_bound(st.begin(), st.end(), A[i]) - st.begin();
    
    vector<query> Q(q);
    for(register int i = 0; i < q; ++i) {
        cin >> Q[i].start >> Q[i].end;
        Q[i].idx = i;
    }

    vector<int> ans(q);

    sort(Q.begin(), Q.end(), [&](const query& a, const query& b) {
        return (a.start / sqrt_N == b.start / sqrt_N ? a.end < b.end : a.start / sqrt_N < b.start / sqrt_N);
    });

    sqrt_decomposition bucket;
    register int s = Q[0].start - 1, e = Q[0].end - 1;
    for(register int i = s; i <= e; ++i) 
        add(i, A, bucket);
    ans[Q[0].idx] = bucket.query();

    for(int i = 1; i < q; ++i) {
        register int cur_s = Q[i].start - 1, cur_e = Q[i].end - 1;
        while(s > cur_s) add(--s, A, bucket);
        while(e < cur_e) add(++e, A, bucket);
        while(s < cur_s) del(s++, A, bucket);
        while(e > cur_e) del(e--, A, bucket);

        ans[Q[i].idx] = bucket.query();
    }

    for(register int i = 0; i < q; ++i) cout << st[ans[i]] << '\n';

    return 0;
}