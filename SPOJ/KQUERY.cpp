//  https://www.spoj.com/problems/KQUERY/
#include<bits/stdc++.h>

using namespace std;


void FastIO() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

struct Node {
    Node *left, *right;
    int sum;
    Node(int val): sum(val), left(nullptr), right(nullptr) {}
    Node(Node* l, Node *r): left(l), right(r), sum(0) {
        if (left) sum += left->sum;
        if (left) sum += right->sum;
    }
    Node(Node* l, Node *r, int sum): left(l), right(r), sum(sum) {}
};
struct PersistentSegmentTree {
    vector<Node*> versions;
    int n;

    Node* build(int l, int r) {
        if (r - l == 1) return new Node(0);
        int m  = (l + r) / 2;
        return new Node(build(l, m), build(m, r)); 
    }

    PersistentSegmentTree(int n): n(n) {
        versions.clear();
        versions.push_back(build(0, n));
    }

    Node* update(Node* node, int l, int r, int idx) {
        if (r - l == 1) {
            return new Node(
                node->left,
                node->right,
                node->sum + 1);
        }
        int m = (l + r) >> 1;
        if (idx < m) return new Node(update(node->left, l, m, idx), node->right);
        else return new Node(node->left, update(node->right, m, r, idx));
    }

    void update(int i) {
        versions.push_back(update(versions.back(), 0, n, i));
    }

    int get(Node* left_node, Node* right_node, int l, int r, int k, int total) {
        if (r - l == 1) return total - (right_node->sum - left_node->sum); 
        int m = (l + r) >> 1;
        if (k < m) {
            return get(left_node->left, right_node->left, l, m, k, total);
        } else return get(left_node->right, right_node->right, m, r, k,
            total - (right_node->left->sum - left_node->left->sum));
    }

    int get(int l, int r, int k, int total) {
        return get(versions[l], versions[r], 0, n, k, total);
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
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

// template<typename P, typename T>
// using ump = gp_hash_table<P, T, custom_hash>;
template<typename P, typename T>
using ump = unordered_map<P, T, custom_hash>;

int main() {
    FastIO();
    int n;
    cin >> n;
    ump<int, int> index;
    vector<int> a(n);
    for (auto &i: a) cin >> i;
    vector<int> b = a;
    int counter = 1;
    sort(b.begin(), b.end());
    for (int i = 0 ; i < n ; i++) {
        if (index.count(b[i])) continue;
        index[b[i]] = counter++;
    }
    PersistentSegmentTree st(counter);
    for (int i = 0 ; i < n ; i++) {
        st.update(index[a[i]]);
    }
    int q, l, r, k;
    cin >> q;
    while (q--) {
        cin >> l >> r >> k;
        --l;
        int i = upper_bound(b.begin(), b.end(), k) - b.begin();
        int y = 0;
        if (i) y = index[b[i - 1]];
        cout << st.get(l, r, y, st.versions[r]->sum - st.versions[l]->sum) << "\n";
    }
    return 0;
}
