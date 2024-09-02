#include <bits/stdc++.h>

using namespace std;

void FastIO() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

class Solution {
private:
    vector<int> tin, low, sz;
    int counter, n, m;
    long long result;
    void dfs(int v, vector<int> g[], int p = -1) {
        tin[v] = low[v] = ++counter;
        for (int t: g[v]) {
            if (t == p) continue;
            if (tin[t]) {
                low[v] = min(low[v], tin[t]);
            } else {
                dfs(t, g, v);
                low[v] = min(low[v], low[t]);
                sz[v] += sz[t];
            }
            if (tin[v] < low[t]) {
                result = max(result, 1LL * sz[t] * (n - sz[t]));
            }
        }
    }
public:
    void solve() {
        cin >> n >> m;
        vector<int> g[n];
        for (int i = 0 ; i < m ; i++) {
            int x, y;
            cin >> x >> y;
            --x, --y;
            g[x].push_back(y);
            g[y].push_back(x);
        }

        tin.assign(n, 0);
        low.resize(n);
        sz.assign(n, 1);
        result = counter = 0;
        dfs(0, g);
        cout << 1LL * n * (n - 1) / 2 - result << "\n";
    }
};

int main() {
    FastIO();
    int t;
    cin >> t;
    Solution solver;
    while (t--) solver.solve();
    return 0;
}
