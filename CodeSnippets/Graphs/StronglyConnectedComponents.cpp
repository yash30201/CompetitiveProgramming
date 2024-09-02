#include <bits/stdc++.h>

using namespace std;

class SCC {
    int n;
    vector<bool> vis;

    void dfs(int node, vector<int> g[], vector<int> &order) {
        vis[node] = true;
        for (int next: g[node]) {
            if (vis[next]) continue;
            dfs(next, g, order); 
        }
        order.push_back(node);
    }
public:
    int id;
    vector<int> scc_id;
    vector<vector<int>> gc;
    SCC(int _n, vector<int> g[]): n(_n) {
        vis.assign(n, false);
        scc_id.resize(n);
        gc.resize(n);
        vector<int> topo;
        id = 0;
        for (int i = 0 ; i < n ; i++) {
            if (vis[i]) continue;
            dfs(i, g, topo);
        }
        
        // True topo order
        reverse(topo.begin(), topo.end());
        vector<int> gr[n];
        for (int from = 0 ; from < n ; from++) {
            vis[from] = false;
            for (int to: g[from]) gr[to].push_back(from);
        }

        vector<int> scc;
        for (int i = 0 ; i < n ; i++) {
            if (vis[topo[i]]) continue;
            dfs(topo[i], gr, scc);
            while (!scc.empty()) {
                scc_id[scc.back()] = id;
                scc.pop_back();
            }
            ++id;
        }

        for (int from = 0 ; from < n ; from++) {
            for (int to: g[from]) {
                if (scc_id[to] == scc_id[from]) continue;
                gc[scc_id[from]].push_back(scc_id[to]);
            }
        }
    }
};

int main() {
    int n = 10;
    vector<int> g[n];
    g[0] = {1, 7};
    g[1] = {1, 2};
    g[2] = {1, 5};
    g[3] = {2, 4};
    g[4] = {9};
    g[5] = {3, 6, 9};
    g[6] = {2};
    g[7] = {0, 6, 8};
    g[8] = {6, 9};
    g[9] = {4};

    SCC s(n, g);
    assert(s.id == 4);
    cout << "Test Passed!\n";
    return 0;
}