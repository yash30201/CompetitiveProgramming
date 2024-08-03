#include <bits/stdc++.h>

using namespace std;

class FenwickTree{
    vector<int> t;
    int n;
    
    inline int calc(int x, int y) {return x + y;}

    inline int impose(int bigger, int smaller) {
        return bigger - smaller;
    }

    void updateBy(int pos, int delta) {
        for ( ; pos < n ; pos |= (pos + 1))  t[pos] = calc(t[pos], delta);
    }

    int prefixCalc(int pos) {
        int result = 0;
        while (pos >= 0) {
            result = calc(result, t[pos]);
            pos = (pos & (pos + 1)) - 1;
        }
        return result;
    }
public:
    FenwickTree(vector<int> &a) {
        n = a.size();
        t.assign(n, 0);
        for (int i = 0 ; i < n ; i++) updateBy(i, a[i]);
    }

    int query(int l, int r) { // [l, r]
        return impose(prefixCalc(r), prefixCalc(l - 1));
    }

    void update(int pos, int val) {
        updateBy(pos, val);
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
    FenwickTree st(a);
    assert(st.query(1, 3) == 15);
    st.update(1, 7);
    assert(st.query(1, 3) == 22);
    cout << "Test Passed!\n";
    return 0;
}