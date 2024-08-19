//  https://codeforces.com/contest/1520/problem/F2
#include <bits/stdc++.h>

using namespace std;


void FastIO() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

struct SmartSegmentTree {
    int n;
    vector<int> t;
    SmartSegmentTree(int nn) {
        n = nn;
        t.assign(n << 2, -1);
    }
    void check(int idx, int l, int r) {
        if (t[idx] != -1) return;
        cout << "? " << l + 1 << " " << r << endl;
        int x;
        cin >> x;
        if (x == -1) exit(0);
        t[idx] = r - l - x;
    }
    int query(int i, int l, int r, int k) {
        if (r - l == 1) return l;
        int m = (r + l) >> 1;
        check(i << 1, l, m);
        if (t[i << 1] >= k) return query(i << 1, l, m, k);
        else return query(i << 1 | 1, m, r, k - t[i << 1]);
    }
    int query(int k) {
        return query(1, 0, n, k);
    }
    void update(int i, int l, int r, int idx) {
        if (r - l == 1) {
            t[i]--;
            return;
        }
        int m = (l + r) >>1;
        if (idx < m) update(i << 1, l, m, idx);
        else update(i << 1 | 1, m, r, idx);
        t[i]--;
    }
    void update(int idx) {
        update(1, 0, n, idx);
    }
};

void solve() {
    int n, t, k;
    cin >> n >> t;
    SmartSegmentTree st(n);
    while (t--) {
        cin >> k;
        k = st.query(k);
        cout << "! " << k + 1 << endl;
        st.update(k);
    }
}
int main() {
    FastIO();
    solve();
    return 0;
}