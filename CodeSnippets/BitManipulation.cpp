#include <bits/stdc++.h>

using namespace std;

void showcaseWindowAnd() {
    vector<int> a{3, 5, 2, 6, 90, 23, 54, 2, 44};

    // Create a count array 
    vector<int> cnt(31, 0);

    // Update the count array as per the window size.
    // Let the current window be [l, r]
    int l, r;

    // The TRICK to calculate the and of a subarray is
    int curr_and = 0;
    for (int bit = 0 ; bit < 31 ; bit++) {
        if (cnt[bit] == r - l + 1) curr_and += (1 << bit);
    }
}

void showcaseSpecialTrickyLoop() {
    vector<int> a{3, 5, 2, 6, 90, 23, 54, 2, 44};
    int n = a.size();
    for (int i = 0 ; i < n ; i++) {
        int x = a[i], y = 0;
        for (int j = i + 1 ; j < n ; j++) {
            x |= a[j], y |= a[j];
            if (x == y) break;
        }
    }

    // This method has a TC of O(30n)!!!!!!

    // Why ??

    // Because, for each i, for j to go from i + 1 to n would mean that all numbers between
    // i + 1 and n don't have all the the set bits in i cummulatively.
    // Hence, let's say this happens for first x i's. Since there are just 30 bits in the
    // range, hence there could be at max 30 full loop i's.
}

int main() {
    showcaseWindowAnd();
    return 0;
}