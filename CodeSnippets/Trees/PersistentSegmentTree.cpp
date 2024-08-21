#include<bits/stdc++.h>

using namespace std;


void FastIO() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

struct Node {
    Node *left, *right;
    int sum, lazy;
    Node(int val): sum(val), left(nullptr), right(nullptr), lazy(0) {}
    Node(Node* l, Node *r): left(l), right(r), sum(0), lazy(0) {
        if (left) sum += left->sum;
        if (left) sum += right->sum;
    }
    Node(Node* l, Node *r, int sum, int lazy): left(l), right(r), sum(sum), lazy(lazy) {}
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
        if (node->left) {
            node->left->sum += node->lazy * (m - l);
            node->left->lazy += node->lazy;
        }
        if (node->right) {
            node->right->sum += node->lazy * (r - m);
            node->right->lazy += node->lazy;
        }
        node->lazy = 0;
    }

    Node* update(Node* node, int l, int r, int L, int R, int val) {
        if (l >= R || r <= L) return node;
        if (l >= L && r <= R) {
            return new Node(
                node->left,
                node->right,
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
        return get(node->left, l, m, L, R) 
            + get(node->right, m, r, L, R);
    }

    int get(int l, int r, int version_id = -1) {
        if (version_id == -1) version_id = (int)versions.size() - 1;
        return get(versions[version_id], 0, n, l, r);
    }
};

int main() {
    FastIO();
    vector<int> a{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    PersistentSegmentTree st(a);
    assert(st.get(1, 6) == 20);
    st.update(2, 5, 10);
    assert(st.get(1, 7) == 57);
    assert(st.get(1, 4, 0) == 9);
    cout << "Test Passed\n";
    return 0;
}
