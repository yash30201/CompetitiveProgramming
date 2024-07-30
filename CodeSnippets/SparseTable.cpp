#include <bits/stdc++.h>

using namespace std;

class SparseTable {
    int n, m;
    vector<vector<int>> dp;

    inline int calculate(int x, int y) {
        // Customize the operation as per the requirement
        return x + y;
    }
public:
    SparseTable(vector<int> &a) {
        n = a.size();
        m = log2(n) + 1;
        dp.resize(m, vector<int>(n));
        dp[0] = a;
        
        for (int i = 1 ; i < m ; i++) {
            for (int j = 0 ; j + (1 << i) <= n ; j++) {
                dp[i][j] = calculate(dp[i-1][j], dp[i-1][j + (1 << (i - 1))]);
            }
        }
    }

    int query(int l, int r) {
        // Query for range [l, r)
        int result = 0;
        for (int i = m - 1 ; i >= 0 ; i--) {
            if ((1 << i) > (r - l)) continue;
            result = calculate(result, dp[i][l]);
            l += (1 << i);
        }
        return result;
    }
};

void fastIO() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

struct TestCase{
    vector<int> arr;
    vector<pair<int, int>> queries;
    vector<int> results;
    TestCase(vector<int> a, vector<pair<int, int>> q, vector<int> result): arr(a), queries(q), results(result) {}
};

vector<TestCase> getTestCases() {
    vector<TestCase> test_cases;
    test_cases.emplace_back(TestCase(vector<int>{1, 2, 3, 4}, vector<pair<int, int>>{{0, 2}, {1, 4}}, vector<int>{32, 9}));
    return test_cases;
}

int main () {
    for (auto &test_case: getTestCases()) {
        SparseTable st(test_case.arr);
        int counter = 0;
        for (auto &[l, r]: test_case.queries) {
            assert(st.query(l, r) == test_case.results[counter++]);
        }
    }
    return 0;
}