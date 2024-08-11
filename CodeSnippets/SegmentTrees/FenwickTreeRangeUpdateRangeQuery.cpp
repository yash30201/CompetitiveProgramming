#include <bits/stdc++.h>

using namespace std;

struct FenwickTree {
    int n;
    vector<int> b1, b2, pre;
    FenwickTree(vector<int> &arr, int nn): n(nn) {
        b1.assign(n, 0);
        b2.assign(n, 0);
        pre.assign(n + 1, 0);
        for (int i = 0 ; i < n ; i++) pre[i+1] = pre[i] + arr[i];
    }
    void add(vector<int> &t, int i, int x) {
        for ( ; i < n ; i = (i | (i + 1))) t[i] += x;
    }
    void rangeAdd(int l, int r, int x) {
        add(b1, l, x);
        add(b2, l, x * (l - 1));
        add(b1, r + 1, -x);
        add(b2, r + 1, -x * r);
    }
    int get(vector<int> &t, int i) {
        int res = 0;
        for ( ; i >= 0 ; i = (i & (i + 1)) - 1) res += t[i];
        return res;
    }
    int prefixSum(int i) {
        return get(b1, i) * i - get(b2, i);
    }
    int get(int l, int r) {
        return prefixSum(r) - prefixSum(l - 1) + pre[r + 1] - pre[l];
    }
};


void fastIO() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}
int main() {
    fastIO();
    vector<int> a{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    FenwickTree st(a, (int)a.size());
    st.rangeAdd(1, 5, 10);
    assert(st.get(0, 2) == 26);
    cout << "Test Passed!\n";
    return 0;
}
