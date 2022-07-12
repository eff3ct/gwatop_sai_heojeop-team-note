#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

//less <- set, less_equal <- multiset
#define ordered_set tree<int, null_type, less_equal<int>, rb_tree_tag, tree_order_statistics_node_update>

int main() {
    ordered_set pbds_set;
    
    int X; cin >> X;
    pbds_set.insert(X); //insert
    cout << pbds_set.order_of_key(X) << '\n'; //Number of elements smaller than X : O(log N)
    cout << *pbds_set.find_by_order(X) << '\n'; //X-th element in a set (0-based) : O(log N)
    //based on red-black tree.

    return 0;
}