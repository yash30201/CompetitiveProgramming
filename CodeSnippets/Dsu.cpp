#include <bits/stdc++.h>

using namespace std;

struct Dsu {
    int n;
    vector<int> leader, depth;
    Dsu(int n): n(n) {
        leader.resize(n);
        depth.assign(n,0);
        iota(leader.begin(), leader.end(), 0);
    }
    inline int find(int x) { return x == leader[x] ? x : leader[x] = find(leader[x]); }
    void join(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return;
        if (depth[x] < depth[y]) swap(x, y);
        leader[y] = x;
        if (depth[x] == depth[y]) depth[x]++;
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