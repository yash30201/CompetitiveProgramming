#include <bits/stdc++.h>

using namespace std;

void FastIO() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

// Example lazy propagaqtion segment tree for range addition and range sum queries
struct SegmentTree {
    vector<int> t, lazy;
    int n;

    inline void event(int i) {
        t[i] = t[i << 1] + t[i << 1 | 1];
    }

    void build(int i, int l, int r, const vector<int> &a) {
        if (r - l == 1) {
            t[i] = a[l];
            return;
        }
        int m = (l + r) / 2;
        build(i << 1, l, m, a);
        build(i << 1 | 1, m, r, a);
        event(i);
    }

    void push(int i, int l, int m, int r) {
        if (lazy[i] == 0) return;
        t[i << 1] += lazy[i] * (m - l);
        lazy[i << 1] += lazy[i];
        t[i << 1 | 1] += lazy[i] * (r - m);
        lazy[i << 1 | 1] += lazy[i];
        lazy[i] = 0;
    }

    SegmentTree(const vector<int> &a) {
        n = a.size();
        lazy.assign(n << 2, 0);
        t.resize(n << 2);
        build(1, 0, n, a);
    }

    void update(int i, int l, int r, int L, int R, int val) {
        if (l >= R || r <= L) return;
        if (l >= L && r <= R) {
            t[i] += (r - l) * val;
            lazy[i] += val;
            return;
        }
        int m = (l + r)>>1;
        push(i, l, m, r);
        update(i << 1, l, m, L, R, val);
        update(i << 1 | 1, m, r, L, R, val);
        event(i);
    }

    void update(int l, int r, int val) { // [l, r)
        update(1, 0, n, l, r, val);
    }

    int query(int i, int l, int r, int L, int R) {
        if (l >= R || r <= L) return 0;
        if (l >= L && r <= R) return t[i];
        int m = (l + r) >> 1;
        push(i, l, m, r);
        return query(i << 1, l, m, L, R)
            + query(i << 1 | 1, m, r, L, R); 
    }

    int query(int l, int r) {
        return query(1, 0, n, l, r);
    }
};

int main() {
    FastIO();
    vector<int> a{1, 2, 3, 4, 5, 6, 7};
    SegmentTree st(a);
    assert(st.query(0, 2) == 3);
    st.update(1, 3, 10);
    assert(st.query(0, 2) == 13);
    cout << "Test Passed!\n";
    return 0;
}