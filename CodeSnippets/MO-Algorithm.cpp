#include <bits/stdc++.h>

using namespace std;

void fastIO() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

struct Q{
    int l, r, i;
};
struct MO{
    // Having a const bucket size work in a better way
    static const int S = 5; // Change this approximately to the bucket size, ie sqrt
    static vector<int> getAnswer(vector<int> &a, vector<pair<int, int>> &qq) {
        int n = qq.size();
        vector<Q> q(n);
        for (int i = 0 ; i < n ; i++) {
            q[i] = {qq[i].first, qq[i].second, i};
        }
        sort(q.begin(), q.end(), [](const Q &x, const Q &y) {
            int i = x.l / S, j = y.l / S;
            return i == j ? x.r < y.r : i < j;
        });
        
        vector<int> res(n);
        int l = 0, r = 0, sum = 0;
        for (int i = 0 ; i < res.size() ; i++) {
            while (l > q[i].l) sum += a[--l];
            while (l < q[i].l) sum -= a[l++];
            while (r > q[i].r) sum -= a[r--];
            while (r < q[i].r) sum += a[++r];
            res[q[i].i] = sum;
        }
        return res;
    }
};

int main() {
    fastIO();
    vector<int> a;
    for (int i = 0 ; i < 21 ; i++) a.push_back(i);
    
    vector<pair<int, int>> queries{
        {1, 3},
        {2, 10},
        {7, 17},
        {5, 14},
        {14, 19},
        {9, 15}
    };

    vector<int> res = move(MO::getAnswer(a, queries));

    for (int i = 0 ; i < queries.size() ; i++) {
        int expected = 0;
        for (int j = queries[i].first ; j <= queries[i].second ; j++) expected += a[j];
        assert(expected == res[i]);
    }
    cout << "Test Passed!\n";
    return 0;
}