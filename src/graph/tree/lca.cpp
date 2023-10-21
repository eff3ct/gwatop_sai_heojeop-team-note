#include <bits/stdc++.h>
using namespace std;
 
#define endl '\n'
 
#define PRECISION 0
 
#define fr first
#define sc second
 
using ll = long long;
using ld = long double;
 
typedef pair<ll,ll> pll;
typedef pair<int,int> pii;
 
const ll MOD = 1e9+7;

const int MAX_DEPTH = 17; //ceil(log base2(n))
int n,q;
int table[MAX_DEPTH+1][100005];
 
vector<int>edges[100005];
 
int parent[100005];
int depth[100005];
bool vis[100005];
 
void dfs(int cur, int d){
    depth[cur] = d;
    vis[cur] = 1;
    for(int &nxt:edges[cur]){
        if(vis[nxt]) continue;
        parent[nxt] = cur;
        dfs(nxt, d+1);
    }
}

void fill_table(){
    dfs(1,1);
    for(int i=1; i<=n; i++){
        table[0][i] = parent[i];
    }
    for(int k=1; k<=MAX_DEPTH; k++){
        for(int i=1; i<=n; i++){
            table[k][i] = table[k-1][table[k-1][i]];
        }
    }
}