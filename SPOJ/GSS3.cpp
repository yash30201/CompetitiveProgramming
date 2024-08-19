// https://www.spoj.com/problems/GSS3/
#include <bits/stdc++.h>

using namespace std;
const int INF = 1000000000;

struct Node {
    int sum, psum, ssum, msum;
};
struct SegmentTree{
    int n;
    vector<Node> t;
    Node combine(const Node &a, const Node &b) {
        Node x;
        x.sum = a.sum + b.sum;
        x.psum = max(a.psum, a.sum + b.psum);
        x.ssum = max(b.ssum, a.ssum + b.sum);
        x.msum = max({a.msum ,b.msum, a.ssum + b.psum});
        return x;
    }
    void build(int i, int l, int r,const vector<int> &a) {
        if (r - l == 1) {
            t[i] = {a[l], a[l], a[l], a[l]};
            return;
        }
        int m  = (r + l) >> 1;
        build(i << 1, l, m, a);
        build(i << 1 | 1, m, r, a);
        t[i] = combine(t[i << 1], t[i << 1 | 1]);
    }
    SegmentTree(const vector<int> &a) {
        n = a.size();
        t.resize(n << 2);
        build(1, 0, n, a);
    }
    void update(int i, int l, int r, int idx, int val) {
        if (r - l == 1) {
            t[i] = {val, val, val, val};
            return;
        }
        int m = (l + r) / 2;
        if (idx < m) update(i << 1, l, m, idx, val);
        else update(i << 1 | 1, m, r, idx, val);
        t[i] = combine(t[i << 1], t[i << 1 | 1]);
    }
    void update(int i, int val) {
        update(1, 0, n, i, val);
    }
    Node get(int i, int l, int r, int L, int R) {
        if (l >= R || r <= L) return {0, -INF, -INF, -INF};
        if (l >= L && r <= R) return t[i];
        int m = (l + r) >> 1;
        return combine(
            get(i << 1, l, m, L, R),
            get(i << 1 | 1, m, r, L, R)
        );
    }
    int get(int l, int r) { // [l, r)
        return get(1, 0, n, l, r).msum;
    }
};

void solveA() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto &i: a) cin >> i;
    int q, t, x, y;
    cin >> q;
    SegmentTree st(a);
    while (q--) {
        cin >> t >> x >> y;
        --x;
        if (t == 0) {
            // Update a[x] to y
            st.update(x, y);
        } else {
            // Query
            cout << st.get(x, y) << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    solveA();
    return 0;
}