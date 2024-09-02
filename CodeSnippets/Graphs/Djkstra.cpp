#include <bits/stdc++.h>

using namespace std;

class ShortestPath {
    static const int _INF = 1e9;
    vector<long long> d;
    vector<int> par;
public:
    ShortestPath (int n, vector<pair<int, int>> g[], int source = 0) {
        par.resize(n);
        d.assign(n, _INF);
        d[source] = 0LL;
        par[source] = source;
        set<pair<long long, int>> st;
        st.insert({0LL, source});
        while(!st.empty()) {
            auto [_wt, from] = *st.begin();
            st.erase(st.begin());
            for (auto [to, wt]: g[from]) {
                if (d[to] > d[from] + wt) {
                    st.erase({d[to], to});
                    d[to] = d[from] + wt;
                    st.insert({d[to], to});
                    par[to] = from;
                }
            }
        }
    }

    vector<int> getPathTo(int x) {
        vector<int> path;
        for (int v = x ; par[v] != v ; v = par[v]) path.push_back(v);
        path.push_back(0);
        reverse(path.begin(), path.end());
        return path;
    }
};

int main() {
    int n = 5;
    vector<pair<int, int>> g[n];
    vector<vector<int>> edges{
        {0, 1, 2},
        {1, 4, 5},
        {1, 2, 4},
        {0, 3, 1},
        {3, 2, 3},
        {2, 4, 1}
    };
    
    for (auto &edge: edges) {
        g[edge[0]].push_back({edge[1], edge[2]});
        g[edge[1]].push_back({edge[0], edge[2]});
    }

    ShortestPath sp(n, g);
    vector<int> path = move(sp.getPathTo(n - 1));
    vector<int> expected{0, 3, 2, 4};
    assert(path == expected);
    cout << "Test Passed!\n";
    return 0;
}