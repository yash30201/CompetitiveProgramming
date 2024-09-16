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

struct custom_hash
{
    static uint64_t splitmix64(uint64_t x)
    {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const
    {
        static const uint64_t FIXED_RANDOM =
            chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }

    size_t operator()(pair<uint64_t, uint64_t> x) const
    {
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
#define FORE(x, a) for (auto &x : a)
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
ostream &operator<<(ostream &out, const pair<P, Q> &a)
{
    return out << "(" << a.fi << ", " << a.se << ")\n";
}

template <typename T>
ostream &operator<<(ostream &out, const vector<T> &a)
{
    for (int i = 0; i < a.size(); i++)
    {
        if (i)
            out << ' ';
        out << a[i];
    }
    return out;
}

template <typename P, typename Q>
ostream &operator<<(ostream &out, const map<P, Q> &a)
{
    out << "\n[\n";
    for (auto &[key, val] : a)
        out << "  " << key << " => " << val << endl;
    return out << "]\n";
}

template <typename T>
ostream &operator<<(ostream &out, const set<T> &a)
{
    out << "[";
    for (const T &i : a)
        out << i << ", ";
    return out << "]\n";
}

template <typename P, typename Q>
istream &operator>>(istream &in, pair<P, Q> &a)
{
    return in >> a.fi >> a.se;
}

template <typename T>
istream &operator>>(istream &in, vector<T> &a)
{
    for (T &i : a)
        in >> i;
    return in;
}

inline void op() { cout << endl; }
template <typename P, typename... Q>
inline void op(const P &a, Q... b)
{
    cout << a;
    if constexpr (sizeof...(Q) == 0)
    {
        cout << endl;
    }
    else
    {
        cout << ' ';
        op(b...);
    }
}

inline void ip() {}
template <typename T, typename... Args>
inline void ip(T &a, Args &...b)
{
    cin >> a;
    ip(b...);
}

void err(istream_iterator<string> it) {}
template <typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args)
{
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

int maxi(const vector<int> &a) { return *max_element(all(a)); }
int maxi(const int &a) { return a; }
template <typename... T>
int maxi(const int &a, T &&...b)
{
    auto x = maxi(b...);
    return max(a, x);
}

int mini(const vector<int> &a) { return *min_element(all(a)); }
int mini(const int &a) { return a; }
template <typename... T>
int mini(const int &a, T &&...b)
{
    auto x = mini(b...);
    return min(a, x);
}

int px[] = {-1, 0, 1, 0};
int py[] = {0, -1, 0, 1};
string path_trace_dir = "DRUL";

bool cycle;
vi longest_path;
vector<int> cycle_path, path, prefix_path;
ump<int, int> vis, par;
ump<int, vector<pii>> g;

void dfs(int node, int pw = 11){
    vis[node] = 1;
    for (auto [next, wt] : g[node]) {
        if (next == par[node]) continue;
        if (abs(wt) == abs(pw)) continue;
        if (vis[node] == 2) continue;
        if (pw == 11 || next * node < 0) {
            if (vis[next] == 1) {
                see(node, next, wt);
                cycle = true;
                cycle_path.pub(abs(wt));
                for (int x = node ; x != next ; x = par[x]) {
                    see(x, par[x]);
                    cycle_path.push_back(abs(x - par[x]));
                }
                reverse(all(cycle_path));
                for (int x = next ; par[x] != 11 ; x = par[x]) {
                    prefix_path.pub(abs(x - par[x]));
                }
                reverse(all(prefix_path));
            } else {
                path.pub(abs(wt));
                par[next] = node;
                dfs(next, wt);
                path.pop_back();
            }
            if (cycle) return;
        }
    }
    if (longest_path.size() < path.size()) longest_path = path;
    vis[node] = 2;
}

void solve()
{
    // Let's begin
    string s;
    ip(s);
    vi a;
    FOR(i, 0, 10)
    {
        if (s[i] == '1')
            a.pub(i + 1);
    }
    int m;
    ip(m);
    if (a.empty())
    {
        op("NO");
        return;
    }
    if (sz(a) >= m)
    {
        op("YES");
        FOR(i, 0, m)
        cout << a[i] << " ";
        cout << endl;
        return;
    }

    FOR(i, -10, 11)
    {
        FORE(w, a)
        {
            if (i + w < 11)
                g[i].pub({i + w, w});
            if (i - w > -11)
                g[i].pub({i - w, -w});
        }
    }
    
    cycle = false;
    par[0] = 11;
    dfs(0);
    see(cycle);
    see(path);
    see(longest_path);
    if (cycle) {
        op("YES");
        if (m <= prefix_path.size()) {
            FOR(i, 0, m) cout << prefix_path[i] << " ";
        } else {
            FORE(i, prefix_path) cout << i << " ";
            m -= sz(prefix_path);
            FOR(i, 0, m) cout << cycle_path[i % sz(cycle_path)] << " ";
        }
        cout << endl;
    } else if (longest_path.size() >= m) {
        op("YES");
        FOR(i, 0, m) cout << longest_path[i] << " ";
        cout << endl;
    } else {
        op("NO");
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int t = 1;
    // cin >> t;
    while (t--)
        solve();
    return 0;
}
