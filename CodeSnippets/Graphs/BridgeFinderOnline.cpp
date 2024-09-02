#include <bits/stdc++.h>

using namespace std;

struct Dsu {
    int n;
    vector<int> size, par;
    Dsu () {}
    Dsu (int nn): n(nn) {
        par.resize(n);
        size.assign(n, 1);
        iota(par.begin(), par.end(), 0);
    }
    inline int getPar(int x) {return x == par[x] ? x : par[x] = getPar(par[x]);}
    void join(int x, int y) {
        x = getPar(x), y = getPar(y);
        if (x == y) return;
        if (size[x] < size[y]) swap(x, y);
        par[y] = x;
        size[x] += size[y];
    }
};

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

template <typename T>
using us = unordered_set<T, custom_hash>;

class BridgeFinder {
    int n;
    Dsu e2cc, cc;
    vector<int> par;

    void rerootAt(int x) {
        // Since individual nodes don't exist, hence find 2-ecc leader
        x = e2cc.getPar(x);
        int cx = cc.getPar(x);
        int p = x;
        for (int node = x ; ; node = e2cc.getPar(par[node])) {
            par[node] = p;
            p = node;
            if (node == cx) break;
        }
    }

    inline void addBridge(int x, int y) {
        if (x > y) swap(x, y);
        bridges.insert({x, y});
    }

    inline void removeBridge(int x, int y) {
        if (x > y) swap(x, y);
        bridges.erase({x, y});
    }

    void processCycle(int x, int y) {
        x = e2cc.getPar(x), y = e2cc.getPar(y);
        int xi = x, yi = y, ancestor;
        while(xi != yi) {
            if (par[xi] != xi) xi = e2cc.getPar(par[xi]);
            if (par[yi] != yi) yi = e2cc.getPar(par[yi]);
        }
        ancestor = e2cc.getPar(xi);
        int p;
        while (x != ancestor) {
            removeBridge(x, par[x]);
            p = e2cc.getPar(par[x]);
            e2cc.join(p, x);
            x = p;
        }
        ancestor = e2cc.getPar(x);
        while(y != ancestor) {
            removeBridge(y, par[y]);
            p = e2cc.getPar(par[y]);
            e2cc.join(y, p);
            y = p;
        }
    }

public:
    us<pair<int, int>> bridges;

    BridgeFinder(int _n): n(_n) {
        e2cc = Dsu(n);
        cc = Dsu(n);
        par.resize(n);
        iota(par.begin(), par.end(), 0);
        bridges.clear();
    }

    void addEdge(int x, int y) {
        int ax = x, ay = y;
        x = e2cc.getPar(x), y = e2cc.getPar(y);
        if (x == y) return;

        int cx = cc.getPar(x), cy = cc.getPar(y);
        if (cx != cy) {
            if (cc.size[cx] < cc.size[cy]) swap(x, y);
            // Prepare smaller tree for merger
            rerootAt(y);
            // Maintain the actual structure
            par[y] = ax;
            // Merge the two different cc into a single cc
            cc.join(x, y);
            addBridge(ax, ay);
        } else {
            // We'll create cycle and compress this newly created 2-ecc to
            // the lowest common ancestor of this cycle.
            processCycle(x, y);
        }
    }
};

int main() {
    int n = 6;
    BridgeFinder bf(n);
    bf.addEdge(0, 1);
    bf.addEdge(0, 2);
    assert(bf.bridges.size() == 2);
    bf.addEdge(1, 2);
    assert(bf.bridges.size() == 0);
    bf.addEdge(1, 3);
    bf.addEdge(2, 4);
    assert(bf.bridges.size() == 2);
    bf.addEdge(3, 4);
    assert(bf.bridges.size() == 0);
    cout << "Test Passed!\n";
    return 0;
}