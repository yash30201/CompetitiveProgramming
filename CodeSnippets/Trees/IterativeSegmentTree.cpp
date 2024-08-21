#include <bits/stdc++.h>

using namespace std;

class SegmentTree{
    int n;
    vector<int> t;

    inline int calc(int x, int y) {return x + y;}
    
    void build(vector<int> &a) {
        for (int i = 0 ; i < n ; i++) t[i + n] = a[i];
        for (int i = n - 1 ; i > 0 ; i--) t[i] = calc(t[i << 1], t[i << 1 | 1]);
    }

    void pointUpdateImpl(int pos, int val) {
        for (t[pos += n] = val ; pos > 1 ; pos >>= 1) {
            t[pos >> 1] = calc(t[pos], t[pos ^ 1]);
        }
    }

    int rangeQueryImpl(int l, int r) {
        int result = 0;
        for (l += n, r += n ; l < r ; l >>= 1, r >>= 1) {
            if (l&1) result = calc(result, t[l++]);
            if (r&1) result = calc(result, t[--r]);
        }
        return result;
        // See https://imgur.com/GGBmcEP 's query explaination for range [3, 11)
    }
public:
    SegmentTree(vector<int> &a) {
        n = a.size();
        t.resize(n << 1);
        build(a);
    }

    SegmentTree(int nn) {
        this->n = nn;
        t.assign(n << 1, 0);
    }

    void update(int pos, int val) {
        pointUpdateImpl(pos, val);
    }

    int query(int l, int r) { // [l, r)
        return rangeQueryImpl(l, r);
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