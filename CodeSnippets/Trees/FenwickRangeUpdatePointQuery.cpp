#include <bits/stdc++.h>

using namespace std;

struct FenwickTree {
    int n;
    vector<int> t;
    FenwickTree(int nn): n(nn) {t.assign(n, 0);}
    void update(int i, int val) {
        for ( ; i < n ; i = (i | (i + 1))) t[i] += val;
    }
    void update(int l, int r, int val) { // [l, r]
        update(l, val);
        update(r + 1, -val);
    }
    int query(int i) {
        int result = 0;
        for ( ; i >= 0 ; i = (i & (i + 1)) - 1) result += t[i];
        return result;
    }
};

void fastIO() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

int main() {
    fastIO();
    vector<int> a{1, 2, 3, 4, 5, 6};
    // 1 indexed based tree
    FenwickTree tree((int)a.size());
    tree.update(0, 3, -1);
    assert(tree.query(1) + a[1] == 1);
    assert(tree.query(4) + a[4] == 5);
    tree.update(1, 4, 10);
    assert(tree.query(4) + a[4] == 15);
    assert(tree.query(1) + a[1] == 11);
    cout << "Test Passed!\n";
    return 0;
}
