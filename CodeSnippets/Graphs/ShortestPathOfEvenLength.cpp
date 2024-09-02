#include <bits/stdc++.h>

using namespace std;

using pii = pair<int, int>;
using vii = vector<pair<int, int>>;


int n;
vii edges;
void Init() {
    // Vertices 0, 1, ... n - 1
    n = 3;
    edges.clear();
    edges.push_back({0, 1});
    edges.push_back({1, 2});
    edges.push_back({0, 2});
}

int ShortestPathOfEvenLength(int source, int target) {
    queue<pii> q;
    vii g[2][n];
    for (auto [from, to]: edges) {
        g[0][from].push_back({to, 1});
        g[1][from].push_back({to, 0});
        g[0][to].push_back({from, 1});
        g[1][to].push_back({from, 0});
    }
    int dist[2][n];
    memset(dist, 0, sizeof(dist));
    q.push({source, 0});
    bool vis[2][n];
    memset(vis, false, sizeof(vis));
    vis[0][source] = true;
    while (!q.empty()) {
        auto node = q.front();
        q.pop();
        for (auto [to, p]: g[node.second][node.first]) {
            if (vis[p][to]) continue;
            dist[p][to] = dist[node.second][node.first] + 1;
            vis[p][to] = true;
            q.push({to, p});
        }
    }
    return dist[0][target];
}

int main() {
    Init();
    assert(ShortestPathOfEvenLength(0, 2) == 2);
    cout << "Test Passed!\n";
    return 0;
}
