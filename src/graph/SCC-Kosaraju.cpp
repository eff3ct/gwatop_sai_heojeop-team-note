#include <bits/stdc++.h>

void forward_DFS(int node, vector<vector<int>>& adj, stack<int>& stk, vector<bool>& visit) {
    for(auto& next : adj[node]) {
        if(visit[next]) continue;
        visit[next] = true;
        forward_DFS(next, adj, stk, visit);
    }
    stk.push(node);
}

void backward_DFS(int node, vector<vector<int>>& adj, vector<bool>& visit, vector<int>& group, int& group_number) {
    group[node] = group_number;
    for(auto& next : adj[node]) {
        if(visit[next]) continue;
        visit[next] = true;
        backward_DFS(next, adj, visit, group, group_number);
    }
}

void get_SCC(int N, vector<vector<int>>& f_adj, vector<vector<int>>& b_adj, 
    vector<int>& group, vector<vector<int>>& scc_adj) {

    stack<int> stk;
    vector<bool> visit(N + 1, false);
    for(int i = 1; i <= N; ++i) {
        if(visit[i]) continue;
        visit[i] = true;
        forward_DFS(i, f_adj, stk, visit);
    }

    fill(visit.begin(), visit.end(), false);
    
    int group_number = 1;
    while(!stk.empty()) {
        int node = stk.top();
        stk.pop();

        if(visit[node]) continue;
        
        visit[node] = true;
        backward_DFS(node, b_adj, visit, group, group_number);
        group_number++;
    }
    
    scc_adj.resize(group_number);
    vector<int> in_degree(group_number);

    for(int i = 1; i <= N; ++i) {
        for(auto& j : f_adj[i]) {
            if(group[i] != group[j]) {
                in_degree[group[j]]++;
                scc_adj[group[i]].push_back(group[j]);
            }
        }
    }
}