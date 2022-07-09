#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using pii = pair<int, int>;
using ppii = pair<int, pii>;

struct node {
    node *l, *r;
    ll s;
    
    node() {
        l = r = NULL;
        s = 0;
    }
};

class dynamic_segment_tree {
    private:
        node* root;

        void delete_nodes(node* v) {
            if(!v) return;
            delete_nodes(v->l);
            delete_nodes(v->r);
            delete v;
        }

    public:
        dynamic_segment_tree() {
            root = new node();
        }

        node* get_root() {
            return root;
        }

        void update(int start, int end, node* cur_node, int idx, ll val) {
            if(idx < start || idx > end) return;

            if(start == end) {
                cur_node->s = val;
                return;
            }

            int mid = (start + end) / 2;
            if(idx <= mid) {
                if(!cur_node->l) cur_node->l = new node();
                update(start, mid, cur_node->l, idx, val);
            }
            else {
                if(!cur_node->r) cur_node->r = new node();
                update(mid + 1, end, cur_node->r, idx, val);
            }

            ll l_val = (cur_node->l ? cur_node->l->s : 0);
            ll r_val = (cur_node->r ? cur_node->r->s : 0);
            cur_node->s = l_val + r_val;
        }

        ll query(int start, int end, node* cur_node, int left, int right) {
            if(!cur_node) return 0;

            if(right < start || left > end) return 0;

            if(left <= start && end <= right) return cur_node->s;

            int mid = (start + end) / 2;

            return query(start, mid, cur_node->l, left, right) + query(mid + 1, end, cur_node->r, left, right);
        }

        ~dynamic_segment_tree() {
            delete_nodes(root);
        }
};