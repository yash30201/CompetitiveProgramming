#include <bits/stdc++.h>

using namespace std;

class SegmentTree{
    int n;
    vector<int> t;
    
    inline int calc(int x, int y) {
        return x + y;
    }

    void build(vector<int> &a, int i, int l, int r) {
        if (r - l == 1) {
            t[i] = a[l];
            return;
        }
        int m = (r + l) >> 1;
        build(a, i << 1, l, m);
        build(a, i << 1 | 1, m, r);
        t[i] = calc(t[i << 1], t[i << 1 | 1]);
    }

    void pointUpdateImpl(int i, int l, int r, int pos, int val) {
        if (r - l == 1) {
            t[i] = val;
            return;
        }
        int m = (r + l) >> 1;
        if (pos < m) pointUpdateImpl(i << 1, l, m, pos, val);
        else pointUpdateImpl(i<<1 | 1, m, r, pos, val);
        t[i] = calc(t[i << 1], t[i << 1 | 1]);
    }

    int rangeQueryImpl(int i, int l, int r, int tl, int tr) {
        if (l >= tr || r <= tl) return 0;
        if (l >= tl && r <= tr) return t[i];
        int m = (l + r) >> 1;
        return calc(
            rangeQueryImpl(i << 1, l, m, tl, tr),
            rangeQueryImpl(i << 1 | 1, m, r, tl ,tr)
        );
    }
public:
    SegmentTree(vector<int> &a) {
        n = a.size();
        t.resize(n * 4 + 5);
        build(a, 1, 0, n);
    }

    SegmentTree(int nn) {
        this->n = nn;
        t.assign(n * 4 + 5, 0);
    }

    void update(int pos, int val) {
        pointUpdateImpl(1, 0, n, pos, val);
    }

    int query(int l, int r) { // [l, r)
        return rangeQueryImpl(1, 0, n, l, r);
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