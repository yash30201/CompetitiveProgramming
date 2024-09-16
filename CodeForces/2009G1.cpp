#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#pragma GCC optimize("O3")

using namespace std;
using namespace __gnu_pbds;


template <typename T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

using vi = vector<int>;
using vll = vector<long long>;
using vb = vector<bool>;
using pii = pair<int, int>;
using pll = pair<long long, long long>;

template <typename T>
using _v = vector<T>;

template <typename T>
using _pq = priority_queue<T>;

template <typename T>
using _pqr = priority_queue<T, vector<T>, greater<T>>;

template <typename P, typename Q>
using _p = pair<P, Q>;

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }

    size_t operator()(pair<uint64_t, uint64_t> x) const {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x.first + FIXED_RANDOM) ^
               (splitmix64(x.second + FIXED_RANDOM) >> 1);
    }
};

// template<typename P, typename T>
// using ump = gp_hash_table<P, T, custom_hash>;
template <typename P, typename T>
using ump = unordered_map<P, T, custom_hash>;

template <typename T>
using us = unordered_set<T, custom_hash>;

using ll = long long;
const int INF = int(1e9);
const ll INFL = ll(1e18);
const int mod = 1000000007;

int n_ones(int x) { return __builtin_popcount(x); }
int n_ones(ll x) { return __builtin_popcountll(x); }
#define FOR(i, a, b) for (int i = a; i < b; i++)
#define FORD(i, a, b) for (int i = b - 1; i >= a; i--)
#define FORE(x, a) for (auto& x : a)
#define all(a) a.begin(), a.end()
#define sz(a) a.size()
#define pub push_back
#define fi first
#define se second
#define lb lower_bound
#define up upper_bound
#define endl '\n'
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

template <typename P, typename Q>
ostream& operator<<(ostream& out, const pair<P, Q>& a) {
    return out << "(" << a.fi << ", " << a.se << ")\n";
}

template <typename T>
ostream& operator<<(ostream& out, const vector<T>& a) {
    for (int i = 0; i < a.size(); i++) {
        if (i) out << ' ';
        out << a[i];
    }
    return out;
}

template <typename P, typename Q>
ostream& operator<<(ostream& out, const map<P, Q>& a) {
    out << "\n[\n";
    for (auto& [key, val] : a) out << "  " << key << " => " << val << endl;
    return out << "]\n";
}

template <typename T>
ostream& operator<<(ostream& out, const set<T>& a) {
    out << "[";
    for (const T& i : a) out << i << ", ";
    return out << "]\n";
}

template <typename P, typename Q>
istream& operator>>(istream& in, pair<P, Q>& a) {
    return in >> a.fi >> a.se;
}

template <typename T>
istream& operator>>(istream& in, vector<T>& a) {
    for (T& i : a) in >> i;
    return in;
}

inline void op() { cout << endl; }
template <typename P, typename... Q>
inline void op(const P& a, Q... b) {
    cout << a;
    if constexpr (sizeof...(Q) == 0) {
        cout << endl;
    } else {
        cout << ' ';
        op(b...);
    }
}

inline void ip() {}
template <typename T, typename... Args>
inline void ip(T& a, Args&... b) {
    cin >> a;
    ip(b...);
}

void err(istream_iterator<string> it) {}
template <typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cerr << ' ' << *it << " = " << a;
    err(++it, args...);
}


#ifdef DEBUG
#define see(args...)                             \
    {                                            \
        cerr << "LINE " << __LINE__;             \
        string _s = #args;                       \
        replace(_s.begin(), _s.end(), ',', ' '); \
        stringstream _ss(_s);                    \
        istream_iterator<string> _it(_ss);       \
        err(_it, args);                          \
        cerr << endl;                            \
    }
#else
#define see(args...)
#endif

int maxi(const vector<int>& a) { return *max_element(all(a)); }
int maxi(const int& a) { return a; }
template <typename... T>
int maxi(const int& a, T&&... b) {
    auto x = maxi(b...);
    return max(a, x);
}

int mini(const vector<int>& a) { return *min_element(all(a)); }
int mini(const int& a) { return a; }
template <typename... T>
int mini(const int& a, T&&... b) {
    auto x = mini(b...);
    return min(a, x);
}

int px[] = {-1, 0, 1, 0};
int py[] = {0, -1, 0, 1};
string path_trace_dir = "DRUL";
struct Q{
    int l, r, i;
};
class SegmentTree{
    int n;
    vector<int> t;

    inline int calc(int x, int y) {return max(x, y);}
    
    void build(vector<int> &a) {
        for (int i = 0 ; i < n ; i++) t[i + n] = a[i];
        for (int i = n - 1 ; i > 0 ; i--) t[i] = calc(t[i << 1], t[i << 1 | 1]);
    }

    void pointUpdateImpl(int pos, int val) {
        for (t[pos += n] += val ; pos > 1 ; pos >>= 1) {
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

    void clear() {
        fill(all(t), 0);
    }
};
struct MO{
    // Having a const bucket size work in a better way
    static const int S = 500; // Change this approximately to the bucket size, ie sqrt
    static vector<int> getAnswer(vector<int> &a, vector<pair<int, int>> &qq, int k) {
        int n = qq.size();
        vector<Q> q(n);
        for (int i = 0 ; i < n ; i++) {
            q[i] = {qq[i].first - 1, qq[i].second - 1, i};
        }
        sort(q.begin(), q.end(), [](const Q &x, const Q &y) {
            int i = x.l / S, j = y.l / S;
            return i == j ? x.r < y.r : i < j;
        });
        
        vector<int> res(n);
        int N = maxi(a);
        SegmentTree st(N + 1);
        int l = 0, r = -1, sum = 0;
        int pr = INF;
        for (int i = 0 ; i < res.size() ; i++) {
            if (pr > q[i].r) {
                st.clear();
                l = 0, r = -1;
            }
            while (r < q[i].r) {
                pr = q[i].r;
                st.update(a[++r], 1);
                if (r - l + 1 > k) st.update(a[l++], -1);
            }
            while (l > q[i].l) {
                if ((r - l + 2) <= k) st.update(a[--l], 1);
            }
            while (l < q[i].l) {
                if ((r - l + 1) <= k)
                st.update(a[l++], -1);
            }
            
            res[q[i].i] = (q[i].r - q[i].l + 1) - st.query(0, N + 1);
        }
        return res;
    }
};
void solve() {
    // Let's begin
    int n, k, q;
    ip(n, k, q);
    vi a(n);
    ip(a);
    int mm = 0;
    FOR(i, 0, n) {
        a[i] -= i;
        mm = min(mm, a[i]);
    }
    mm *= -1;
    FOR(i, 0, n) a[i] += mm;
    vector<pii> Q(q);
    ip(Q);
    vector<int> res = move(MO::getAnswer(a, Q, k));
    FORE(i, res) op(i);
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int t = 1;
    cin >> t;
    while (t--) solve();
    return 0;
}








