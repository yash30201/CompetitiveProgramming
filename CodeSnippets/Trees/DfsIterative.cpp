#include <bits/stdc++.h>

using namespace std;
using vi = vector<int>;

int Dfs(vi g[], vector<bool> vis, int source) {
    stack<int> st;
    st.push(source);
    vis[source] = true;
    int counter = 0;
    while (!st.empty()) {
        int from = st.top();
        st.pop();
        counter++;
        for (int to: g[from]) {
            if (vis[to]) continue;
            vis[to] = true;
            st.push(to);
        }
    }
    return counter;
}

int main() {
    int n = 5;
    vi g[n];
    pair<int, int> edges[] = {
        {0, 1},
        {1, 4},
        {2, 3},
        {3, 4}
    };
    for (auto [from, to]: edges) {
        g[from].push_back(to);
        g[to].push_back(from);
    }
    vector<bool> vis(n, false);
    assert(Dfs(g, vis, 3) == 5);
    cout << "Test Passed!\n";
    return 0;
}
