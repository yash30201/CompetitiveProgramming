#include <bits/stdc++.h>

using namespace std;

namespace BellmanFord {

const int MAX_DIST = 1e9;
class ShortestPath {
    int n, m, last_node;
    vector<int> par;
public:
    vector<int> dist;
    bool cycle_present;
    ShortestPath (int nn, vector<vector<int>> &edges, int source, bool undirected = false): n(nn) {
        m = static_cast<int>(edges.size());
        dist.assign(n, MAX_DIST);
        dist[source] = 0;
        par.resize(n);
        par[source] = source;

        bool nothing_happened;
        for (int i = 0 ; i < n ; i++) {
            nothing_happened = true;
            for (auto &e: edges) {
                if (dist[e[0]] == MAX_DIST) continue;
                if (dist[e[0]] + e[2] < dist[e[1]]) {
                    dist[e[1]] = dist[e[0]] + e[2];
                    par[e[1]] = e[0];
                    nothing_happened = false;
                    last_node = e[1];
                }
                if (undirected) {
                    if (dist[e[1]] + e[2] < dist[e[0]]) {
                        dist[e[0]] = dist[e[1]] + e[2];
                        par[e[0]] = e[1];
                        nothing_happened = false;
                        last_node = e[0];
                    }
                }
            }
            if (nothing_happened) break;
        }

        cycle_present = !nothing_happened;
    }

    vector<int> getPath(int target) {
        vector<int> path;
        if (cycle_present) {
            cout << "CYCLE PRESENT, invalid operation\n";
            return path;
        }
        for (int node = target ; ; node = par[node]) {
            path.push_back(node);
            if (par[node] == node) break;
        }
        reverse(path.begin(), path.end());
        return path;
    }

    vector<int> getCycle() {
        vector<int> path;
        if (!cycle_present) {
            cout << "CYCLE NOT PRESENT, invalid operation\n";
            return path;
        }
        int cycle_start = last_node;
        for (int i = 0 ; i < n ; i++) cycle_start = par[cycle_start];
        path.push_back(cycle_start);
        for (int node = par[cycle_start] ; ; node = par[node]) {
            path.push_back(node);
            if (node == cycle_start) break;
        }
        return path;
    }
};

}

int main() {
    int n = 5;
    vector<vector<int>> edges_without_cycle{
        {0, 1, 2},
        {1, 4, 5},
        {1, 2, 4},
        {0, 3, 1},
        {3, 2, 3},
        {2, 4, 1}
    };
    vector<vector<int>> edges_with_cycle{
        {0, 1, 2},
        {1, 4, -6},
        {1, 2, 4},
        {0, 3, 1},
        {3, 2, 3},
        {2, 4, 1}
    };

    BellmanFord::ShortestPath sp(n, edges_without_cycle, 0);
    assert(sp.cycle_present == false);
    assert(sp.dist[2] == 4);
    vector<int> expected_path{0, 3, 2};
    assert(sp.getPath(2) == expected_path);

    BellmanFord::ShortestPath spwc(n, edges_with_cycle, 0, true);
    assert(spwc.cycle_present == true);
    vector<int> expected_cycle{1, 4, 2, 1};
    assert(spwc.getCycle() == expected_cycle);
    cout << "Test Passed\n";
    return 0;
}
