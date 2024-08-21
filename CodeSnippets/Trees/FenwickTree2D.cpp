#include <bits/stdc++.h>

using namespace std;

class FenwickTree2D{
    vector<vector<int>> t;
    int n, m;

    inline int calc(int x, int y) {return x + y;}

    inline int impose(int bigger, int smaller) {
        return bigger - smaller;
    }

    void updateBy(int ii, int jj, int delta) {
        for (int i = ii ; i < n ; i = (i | (i + 1))) {
            for (int j = jj ; j < m ; j = (j | (j + 1))) {
                t[i][j] = calc(t[i][j], delta);
            }
        }
    }

    int prefixCalc(int i, int j) {
        int result = 0;
        for (int k = i ; k >= 0 ; k = (k & (k + 1)) - 1) {
            for (int l = j ; l >= 0 ; l = (l & (l + 1)) - 1) {
                result = calc(result, t[k][l]);
            }
        }
        return result;
    }
public:
    FenwickTree2D(vector<vector<int>> &a) {
        n = a.size(), m = a[0].size();
        t = vector<vector<int>>(n, vector<int>(m, 0));
        for (int i = 0 ; i < n ; i++) {
            for (int j = 0 ; j < m ; j++) {
                updateBy(i, j, a[i][j]);
            }
        }
    }

    int query(int i1, int j1, int i2, int j2) { // i1 <= i2, j1 <= j2
        int result = impose(prefixCalc(i2, j2), prefixCalc(i2, j1 - 1));
        result = impose(result, prefixCalc(i1 - 1, j2));
        result = calc(result, prefixCalc(i1 - 1, j1 - 1));
        return result;
    }

    void update(int i, int j, int val) {
        updateBy(i, j, val);
    }
};

void FastIO(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

int main() {
    FastIO();
    vector<vector<int>> a{
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };
    FenwickTree2D st(a);
    assert(st.query(0, 1, 2, 2) == 33);
    st.update(1, 1, 5);
    assert(st.query(0, 1, 2, 2) == 38);
    cout << "Test Passed!\n";
    return 0;
}
