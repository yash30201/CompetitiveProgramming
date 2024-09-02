#include <bits/stdc++.h>

using namespace std;

struct Dsu {
    int n;
    vector<int> par, sz;
    Dsu(int n): n(n) {
        par.resize(n);
        sz.assign(n,1);
        iota(par.begin(), par.end(), 0);
    }
    inline int find(int x) { return x == par[x] ? x : par[x] = find(par[x]); }
    void join(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return;
        if (sz[x] < sz[y]) swap(x, y);
        par[y] = x;
        sz[x] += sz[y];
        return;
    }
};

void FastIO() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

int main() {
    FastIO();
    Dsu dsu(10);
    dsu.join(1, 2);
    dsu.join(5, 8);
    assert(dsu.find(1) == dsu.find(2));
    assert(dsu.find(5) == dsu.find(8));
    assert(dsu.find(1) != dsu.find(5));
    dsu.join(2, 8);
    assert(dsu.find(1) == dsu.find(5));
    cout << "TEST PASSED!\n";
    return 0;
}
