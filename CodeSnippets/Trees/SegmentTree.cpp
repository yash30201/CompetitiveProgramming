#include <bits/stdc++.h>

using namespace std;

struct SegmentTree {
    int n;
    vector<int> t;

    void build(int i, int l, int r, const vector<int> &a) {
        if (r - l == 1) {
            t[i] = a[l];
            return;
        }
        int m = (l + r) >> 1;
        build(i << 1, l, m, a);
        build(i << 1 | 1, m, r, a);
        t[i] = t[i << 1] + t[i << 1 | 1];
    }
    SegmentTree(vector<int> &a) {
        n = a.size();
        t.resize(n << 2);
        build(1, 0, n, a);
    }
    void update(int i, int l, int r, int idx, int val) {
        if (r - l == 1) {
            t[i] = val;
            return;
        }
        int m = (l + r) >> 1;
        if (idx < m) update(i << 1, l, m, idx, val);
        else update(i << 1 | 1, m, r, idx, val);
        t[i] = t[i << 1] + t[i << 1 | 1];
    }
    void update(int idx, int val) {
        update(1, 0, n, idx, val);
    }
    int query(int i, int lx, int rx, int l, int r) {
        if (lx >= r || rx <= l) return 0;
        if (lx >= l && rx <= r) return t[i];
        int m = (lx + rx) >> 1;
        return query(i << 1, lx, m, l, r)
            + query(i << 1 | 1, m, rx, l, r);
    }
    int query(int l, int r) {
        return query(1, 0, n, l, r);
    }
};

void fastIO() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

int main() {
    fastIO();
    vector<int> a{1, 3, 5, 7, 9, 11};
    SegmentTree st(a);
    assert(st.query(1, 4) == 15);
    st.update(1, 10);
    assert(st.query(1, 4) == 22);
    cout << "Test Passed!\n";
    return 0;
}