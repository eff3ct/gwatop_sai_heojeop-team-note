#include <bits/stdc++.h>

using namespace std;
using ll = long long;

class fenwick_tree {
    private:    
        vector<ll> tree;
        int max_size;

    public: 
        fenwick_tree(int N) {
            tree.resize(N + 1);
            max_size = N;
        }

        void update(int idx, ll diff) {
            for(int i = idx; i <= max_size; i += (i & (-i)))
                tree[idx] += diff;
        }

        ll query(int idx) {
            ll ret = 0;
            for(int i = idx; i > 0; i -= (i & (-i)))
                ret += tree[i];
            return ret;
        }
};

class fenwick_tree_2d {
    private:    
        vector<vector<ll>> tree;
        int max_size;

    public: 
        fenwick_tree_2d(int N) {
            tree.resize(N + 1);
            for(int i = 1; i <= N; ++i)
                tree[i].resize(N + 1);
            max_size = N;
        }

        void update(int y, int x, ll diff) {
            for(int i = x; i <= max_size; i += (i & (-i))) {
                for(int j = y; j <= max_size; j += (j & (-j))) {
                    tree[i][j] += diff;
                }
            }
        }

        ll query(int y, int x) {
            ll ret = 0;
            for(int i = x; i > 0; i -= (i & (-i))) {
                for(int j = y; j > 0; j -= (j & (-j))) {
                    ret += tree[i][j];
                }
            }
            return ret;
        }
};