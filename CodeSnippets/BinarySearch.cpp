#include <bits/stdc++.h>

using namespace std;

class BinarySearch {
public:
    static int upperBound(vector<int> &a, int l, int r, int val) {
        // Assuming l >= 0 && r <= a.size()
        // [l, r)
        while (l < r) {
            int m = (r - l) / 2 + l;
            if (a[m] <= val) l = m + 1;
            else r = m;
        }
        return l;
    }

    static int lowerBound(vector<int> &a, int l, int r, int val) {
        // Same assumption as above
        while(l < r) {
            int m = (r - l) / 2 + l;
            if (a[m] < val) l = m + 1;
            else r = m;
        }
        return l;
    }
};


void fastIO() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

int main() {
    fastIO();

    vector<int> a{1, 3, 6, 6, 6, 9, 10};
    assert(BinarySearch::lowerBound(a, 0, 7, 6) == 2);
    assert(BinarySearch::lowerBound(a, 0, 7, 7) == 5);
    assert(BinarySearch::upperBound(a, 0, 7, 6) == 5);
    cout << "Test Passed!\n";
    return 0;
}