#include <bits/stdc++.h>

using namespace std;

struct FenwickTree {
    vector<int> t;
    int n;
    FenwickTree(int nn) {
        n = nn;
        t.assign(n, 0);
    }
    int pSum(int i) {
        int res = 0;
        for ( ; i >= 0 ; i = (i & (i + 1)) - 1) res += t[i];
        return res;
    }
    void update(int i, int val) {
        for ( ; i < n ; i = (i | (i + 1))) t[i] += val;
    }
    int query(int l, int r) { // [l, r]
        return pSum(r) - pSum(l - 1);
    }
};

void FastIO(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

int main() {
    FastIO();
    vector<int> a{1, 3, 5, 7, 9, 11};
    FenwickTree st(a.size());
    for (int i = 0 ; i < a.size() ; ++i) st.update(i, a[i]);
    assert(st.query(1, 3) == 15);
    st.update(1, 7);
    assert(st.query(1, 3) == 22);
    cout << "Test Passed!\n";
    return 0;
}
