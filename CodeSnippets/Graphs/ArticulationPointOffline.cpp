#include <bits/stdc++.h>

using namespace std;

using vii = vector<pair<int, int>>;
using pii = pair<int, int>;
struct ArticulationPoint {
    vii *g;
    vector<int> tin, low;
    unordered_set<int> points;
    int counter;
    inline void process(int x) {
        points.insert(x);
        static_assert(false, "Method: process not implemented");
    }
    void dfs(int node, int p = -1) {
        tin[node] = low[node] = ++counter;
        int traversal = 0;
        for (auto [next, idx]: g[node]) {
            if (next == p) continue;
            if (tin[next]) low[node] = min(low[node], tin[next]);
            else {
                ++traversal;
                dfs(next, node);
                low[node] = min(low[node], low[next]);
            }
            if (tin[node] < low[next]) {
                process(node);
            }
        }
        if (p == -1 && traversal > 1) process(node);
    }
    ArticulationPoint(int n, vii a[]) {
        g = a;
        tin.assign(n, 0);
        low.resize(n);
        counter = 0;
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
    ArticulationPoint ap(n, g);
    assert(static_cast<int>(ap.points.size()) == 2);
    cout << "Test Passed!\n";
    return 0;
}
