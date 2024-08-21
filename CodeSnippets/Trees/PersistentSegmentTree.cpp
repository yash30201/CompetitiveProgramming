#include<bits/stdc++.h>

using namespace std;


void FastIO() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

struct Node {
    Node *l, *r;
    int sum, lazy;
    Node(int val): sum(val), l(nullptr), r(nullptr), lazy(0) {}
    Node(Node* l, Node *r): l(l), r(r), sum(0), lazy(0) {
        if (l) sum += l->sum;
        if (r) sum += r->sum;
    }
    Node(Node* l, Node *r, int sum, int lazy): l(l), r(r), sum(sum), lazy(lazy) {}
};
struct PersistentSegmentTree {
    vector<Node*> versions;
    int n;
    Node* build(int l, int r, const vector<int> &a) {
        if (r - l == 1) return new Node(a[l]);
        int m = (l + r) >> 1;
        return new Node(build(l, m, a), build(m, r, a));
    }
    PersistentSegmentTree(const vector<int> &a) {
        n = a.size();
        versions.push_back(build(0, n, a));
    }

    void push(Node* node, int l, int m, int r) {
        if (node->lazy == 0) return;
        if (node->l) {
            node->l->sum += node->lazy * (m - l);
            node->l->lazy += node->lazy;
        }
        if (node->r) {
            node->r->sum += node->lazy * (r - m);
            node->r->lazy += node->lazy;
        }
        node->lazy = 0;
    }

    Node* update(Node* node, int l, int r, int L, int R, int val) {
        if (l >= R || r <= L) return nullptr;
        if (l >= L && r <= R) {
            return new Node(
                node->l,
                node->r,
                node->sum + (r - l) * val,
                node->lazy + val);
        }
        int m = (l + r) >> 1;
        push(node, l, m, r);
        return new Node(
            update(node->left, l, m, L, R, val),
            update(node->right, m, r, L, R, val)
        );
    }

    void update(int l, int r, int val, int version_id = -1) {
        if (version_id == -1) version_id = (int)versions.size() - 1;
        versions.push_back(update(versions[version_id], 0, n, l, r, val));
    }

    int get(Node* node, int l, int r, int L, int R) {
        if (l >= R || r <= L) return 0;
        if (l >= L && r <= R) return node->sum;
        int m = (l + r) >> 1;
        push(node, l, m, r);
        return get(node->l, l, m, L, R);
            + get(node->r, m, r, L, R);
    }

    int get(int l, int r, int version_id = -1) {
        if (version_id == -1) version_id = (int)versions.size() - 1;
        return get(versions[version_id], 0, n, l, r);
    }
};

int main() {
    FastIO();
    return 0;
}
