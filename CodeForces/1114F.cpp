#include <bits/stdc++.h>

using namespace std;

void FastIO();

struct SegmentTree {
    int n;
    vector<pair<int, long long>> t, lz;
    SegmentTree(const vector<int> &a);
    pair<int, long long> comb(const pair<int, long long> &x, const pair<int, long long> &y);
    void build(int i, int l, int r, const vector<int> &a);
    void update(int l, int r, int val);
    void update(int i, int l, int r, int L, int R, int val);
    pair<int, long long> query(int i, int l, int r, int L, int R);
    int query(int l, int r);
    void push(int i, int l, int m, int r);
};



int main() {
    FastIO();
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (auto &i: a) cin >> i;
    SegmentTree st(a);
    string s;
    int l, r, x;
    while (q--) {
        cin >> s;
        if (s[0] == 'M') {
            cin >> l >> r >> x;
            st.update(l - 1, r, x);
        } else {
            cin >> l >> r;
            cout << st.query(l - 1, r) << "\n";
        }
    }
    return 0;
}

void FastIO(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

const int N = 300, mod = 1e9 + 7;
int prime_to_index[N + 1];
long long num_to_mask[N + 1];
int prime_to_inv_spl[N + 1];

pair<int, long long> SegmentTree::comb(const pair<int, long long> &x, const pair<int, long long> &y) {
    pair<int, long long> res;
    res.first = 1LL * x.first * y.first % mod;
    res.second = (x.second | y.second);
    return res;
}

void SegmentTree::build(int i, int l, int r, const vector<int> &a) {
    if (r - l == 1) {
        t[i] = {a[l], num_to_mask[a[l]]};
        return;
    }
    int m = (r + l) / 2;
    build(i << 1, l, m, a);
    build(i << 1 | 1, m, r, a);
    t[i] = comb(t[i << 1], t[i << 1 | 1]);
}

int binexp(int x, int y) {
    int res = 1;
    while (y) {
        if (y & 1) res = 1LL * res * x % mod;
        y >>= 1;
        x = 1LL * x * x % mod;
    }
    return res;
}

inline int ggg(int i) {
    return 1LL * (i - 1) * binexp(i, mod - 2) % mod;
}

void initializePrimeToIndex() {
    vector<int> primes;
    vector<bool> isp(N + 1, true);
    int x = 1;

    prime_to_inv_spl[1] = 1;
    for (int i = 2 ; i <= N ; i++) {
        if (!isp[i]) continue;
        prime_to_inv_spl[x] = ggg(i);
        prime_to_index[i] = x++;
        for (int j = i * i ; j <= N ; j += i) isp[j] = false;
    }
}

void initializeNumMask() {
    num_to_mask[1] = 0LL;
    for (int i = 2 ; i <= N ; i++) {
        for (int j = 2 ; j <= N ; j++) {
            if (prime_to_index[j] == 0) continue;
            if (i % j == 0) num_to_mask[i] |= (1LL << prime_to_index[j]);
        }
    }
}

SegmentTree::SegmentTree(const vector<int> &a) {
    n = a.size();
    t.resize(n << 2);
    lz.assign(n << 2, {1, 0LL});
    initializePrimeToIndex();
    initializeNumMask();
    build(1, 0, n, a);
}

void SegmentTree::push(int i, int l, int m, int r) {
    if (lz[i].second == 0LL) return;
    t[i << 1].first = 1LL * t[i << 1].first * lz[i].first % mod * (m - l) % mod;
    t[i << 1].second |= lz[i].second;
    lz[i << 1].first = 1LL * lz[i << 1].first * lz[i].first % mod;
    lz[i << 1].second |= lz[i].second;
    t[i << 1 | 1].first = 1LL * t[i << 1 | 1].first * lz[i].first % mod * (r - m) % mod;
    t[i << 1 | 1].second |= lz[i].second;
    lz[i << 1 | 1].first = 1LL * lz[i << 1 | 1].first * lz[i].first % mod;
    lz[i << 1 | 1].second |= lz[i].second;
    lz[i] = {1, 0LL};
}

void SegmentTree::update(int i, int l, int r, int L, int R, int val) {
    if (l >= R || r <= L) return;
    if (l >= L && r <= R) {
        t[i] = comb(t[i], {1LL * val * (r - l) % mod, num_to_mask[val]});
        lz[i] = comb(lz[i], {val, num_to_mask[val]});
        return;
    }
    int m = (l + r) >> 1;
    push(i, l, m, r);
    update(i << 1, l, m, L, R, val);
    update(i << 1 | 1, m, r, L, R, val);
    t[i] = comb(t[i << 1], t[i << 1 | 1]);
}

void SegmentTree::update(int l, int r, int val) {
    update(1, 0, n, l, r, val);
}

pair<int, long long> SegmentTree::query(int i, int l, int r, int L, int R) {
    if (l >= R || r <= L) return {1, 0LL};
    if (l >= L && r <= R) return t[i];
    int m = (l + r) >> 1;
    return comb(query(i << 1, l, m, L, R), query(i << 1 | 1, m, r, L, R));
}

int SegmentTree::query(int l, int r) {
    auto a = query(1, 0, n, l, r);
    int res = a.first;
    for(int bit = 1 ; bit < 63 ; bit++) {
        if ((1LL << bit) & a.second) res = 1LL * res * prime_to_inv_spl[bit] % mod;
    }
    return res;
}
