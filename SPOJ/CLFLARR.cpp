// https://www.spoj.com/problems/CLFLARR/
#include <bits/stdc++.h>

using namespace std;

#define endl "\n";

struct SegmentTree {
    int n;
    vector<int> lazy;
    SegmentTree(int nn) {
        n = nn;
        lazy.assign(n << 2, 0);
    }

    void propagate(int i) {
        if (lazy[i] == 0) return;
        lazy[i << 1] = lazy[i << 1 | 1] = lazy[i];
        lazy[i] = 0;
    }
    void update(int i, int lx, int rx, int l, int r, int color) { // [l, r)
        if (lx >= r || rx <= l) return;
        if (lx >= l && rx <= r) {
            lazy[i] = color;
            return;
        }
        propagate(i);
        int m = (lx + rx) >> 1;
        update(i << 1, lx, m, l, r, color);
        update(i << 1 | 1, m, rx, l, r, color);
    }

    void update(int l, int r, int color) { // [l, r)
        update(1, 1, n, l, r, color);
    }

    int get(int i, int l, int r, int idx) {
        if (r - l == 1) return lazy[i];
        propagate(i);
        int m = (l + r) >> 1;
        if (idx < m) return get(i << 1, l, m, idx);
        else return get(i << 1 | 1, m, r, idx);
    }
    int get(int i) {
        return get(1, 1, n, i);
    }
};

void solveSegmentTree() {
    int n, q, l, r, c;
    cin >> n >> q;
    n++;
    SegmentTree st(n);
    while (q--) {
        cin >> l >> r >> c;
        st.update(l, r + 1, c);
    }
    for (int i = 1 ; i < n ; i++) cout << st.get(i) << endl;
    return;
}

struct Dsu {
    vector<int> par;
    Dsu(int n) {
        par.resize(n + 2);
        iota(par.begin(), par.end(), 0);
    }
    int getNextVirginRange(int x) {
        return x == par[x] ? x : par[x] = getNextVirginRange(par[x]);
    }
};

void solveDsu() {
    int n, q;
    cin >> n >> q;
    vector<vector<int>> queries(q, vector<int>(3));
    for (auto &query: queries) cin >> query[0] >> query[1] >> query[2];
    vector<int> color(n + 1, 0);
    Dsu dsu(n);
    for (int i = q - 1; i >= 0 ; --i) {
        const auto& query = queries[i];
        int x = dsu.getNextVirginRange(query[0]);
        while (x <= query[1]) {
            color[x] = query[2];
            x = dsu.par[x] = dsu.getNextVirginRange(x + 1);
        }
    }
    for (int i = 1 ; i <= n ; i++) cout << color[i] << endl;
}

void FastIO() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}
int main() {
    FastIO();
    // solveSegmentTree();
    solveDsu();
    return 0;
}
