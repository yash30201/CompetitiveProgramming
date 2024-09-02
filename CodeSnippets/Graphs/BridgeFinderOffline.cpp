#include <bits/stdc++.h>

using namespace std;

using vii = vector<pair<int, int>>;
using pii = pair<int, int>;
struct BridgeFinder {
    vii *g;
    vector<int> tin, low, bridges;
    int counter, bridge_count;
    inline void process(int x) {
        ++bridge_count;
        static_assert(false, "Method: process not implemented");
    }
    void dfs(int node, int p = -1) {
        tin[node] = low[node] = ++counter;
        for (auto [next, idx]: g[node]) {
            if (next == p) continue;
            if (tin[next]) low[node] = min(low[node], tin[next]);
            else {
                dfs(next, node);
                low[node] = min(low[node], low[next]);
            }
            if (tin[node] < low[next]) {
                // This is a bridge
                process(idx);
            }
        }
    }
    BridgeFinder(int n, vii a[]) {
        g = a;
        tin.assign(n, 0);
        low.resize(n);
        bridges.clear();
        counter = bridge_count = 0;
        for (int i = 0 ; i < n ; i++) {
            if (tin[i]) continue;
            dfs(i);
        }
    }
};

int main() {
    int n = 5;
    vii g[n];
    vii edges{
        {0, 1},
        {0, 2},
        {1, 2},
        {1, 3},
        {2, 4}
    };
    for (int i = 0 ; i < (int)edges.size() ; i++) {
        g[edges[i].first].push_back({edges[i].second, i});
        g[edges[i].second].push_back({edges[i].first, i});
    }
    BridgeFinder bf(n, g);
    assert(bf.bridge_count == 2);
    cout << "Test Passed!\n";
    return 0;
}
