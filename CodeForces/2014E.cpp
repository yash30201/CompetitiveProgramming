#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#pragma GCC optimize("O3")

using namespace std;
using namespace __gnu_pbds;

// find_by_order -> value at index (0 based)
// order_of_key -> index of value (0 based)
template <typename T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

using vi = vector<int>;
using vll = vector<long long>;
using vb = vector<bool>;
using pii = pair<int, int>;
using pll = pair<long long, long long>;
using vpii = vector<pair<int, int>>;
using vpll = vector<pair<long long, long long>>;

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
#define mms(a, x) memset(a, x, sizeof(a));
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

void solve() {
    // Let's begin
    int n, m, h;
    ip(n, m, h);
    vb horse_present(n, false);
    FOR(i, 0, h) {
        int x;
        ip(x);
        x--;
        horse_present[x] = true;
    }
    vector<pair<pll, ll>> g[n][2];
    FOR(i, 0, m) {
        int x, y, w;
        ip(x, y, w);
        x--;
        y--;
        bool xi = horse_present[x], yi = horse_present[y];
        g[x][0].pub({{y, 0}, w});
        g[y][0].pub({{x, 0}, w});
        g[x][1].pub({{y, 1}, w / 2});
        g[y][1].pub({{x, 1}, w / 2});
        if (xi) {
            g[x][0].pub({{y, 1}, w / 2});
        }
        if (yi) {
            g[y][0].pub({{x, 1}, w / 2});
        }
    }

    auto dj = [&](vector<pair<pll, ll>> gg[][2], vector<vll> &dist, ll ii) {
        _pqr<array<ll, 3>> min_heap;
        if (horse_present[ii]) {
            dist[1][ii] = 0;
            min_heap.push({0LL, 1LL, ii});
        } else {
            dist[0][ii] = 0;
            min_heap.push({0LL, 0LL, ii});
        }

        while (!min_heap.empty()) {
            auto [d, hor, from] = min_heap.top();
            min_heap.pop();
            if (dist[hor][from] < d) continue;
            for (auto t: gg[from][hor]) {
                auto to_hor = t.first.se, to = t.first.fi, tow = t.second;
                if (dist[to_hor][to] > d + tow) {
                    dist[to_hor][to] = d + tow;
                    min_heap.push({dist[to_hor][to], to_hor, to});
                }
            }
        }
    };

    vector<vll> dist_0(2, vll(n, INFL));
    dj(g, dist_0, 0);
    if (dist_0[0][n - 1] == INFL && dist_0[1][n - 1] == INFL) {
        op(-1);
        return;
    }
    vector<vll> dist_n(2, vll(n, INFL));
    dj(g, dist_n, n - 1);
    ll res = INFL;
    FOR(i, 0, n) {
        ll m1 = min(dist_0[0][i], dist_0[1][i]);
        ll m2 = min(dist_n[0][i], dist_n[1][i]);
        res = min(res, max(m1, m2));
    }
    op(res);
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








