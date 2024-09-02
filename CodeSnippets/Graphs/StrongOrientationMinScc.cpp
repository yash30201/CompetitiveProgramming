#include <bits/stdc++.h>

using namespace std;

using vii = vector<pair<int, int>>;
using pii = pair<int, int>;
class StrongOrientation {
    vii *g;
    vector<int> tin, low;
    int counter;
    void dfs(int node, int p = -1) {
        tin[node] = low[node] = ++counter;
        for (auto [next, idx]: g[node]) {
            if (next == p) continue;
            if (tin[next]) {
                orientation[idx] = '<';
                low[node] = min(low[node], tin[next]);
            } else {
                dfs(next, node);
                orientation[idx] = '>';
                low[node] = min(low[node], low[next]);
            }
            if (tin[node] < low[next]) {
                // This is a bridge
                bcount++;
            }
        }
    }
public:
    string orientation;
    int bcount;
    StrongOrientation(int n, vii a[]) {
        g = a;
        bcount = 0;
        tin.assign(n, 0);
        low.resize(n);
        counter = 0;
        orientation.assign(n, '&');
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
    StrongOrientation so(n, g);
    assert(so.bcount == 2);
    assert(so.orientation == "><>>>");
    cout << "Test Passed!\n";
    return 0;
}
