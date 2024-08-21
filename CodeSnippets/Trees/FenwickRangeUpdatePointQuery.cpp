#include <bits/stdc++.h>

using namespace std;

struct FenwickTree {
    int n;
    vector<int> t;
    FenwickTree(int nn): n(nn) {t.assign(n + 1, 0);}
    void add(int i, int val) {
        for ( ; i <= n ; i += (i & (-i))) t[i] += val;
    }
    void add(int l, int r, int val) { // [l, r]
        add(l, val);
        add(r + 1, -val);
    }
    int get(int i) {
        int result = 0;
        for ( ; i > 0 ; i -= (i & (-i))) result += t[i];
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
    tree.add(1, 4, -1);
    assert(tree.get(2) + a[1] == 1);
    assert(tree.get(5) + a[4] == 5);
    tree.add(2, 5, 10);
    assert(tree.get(5) + a[4] == 15);
    assert(tree.get(2) + a[1] == 11);
    cout << "Test Passed!\n";
    return 0;
}
