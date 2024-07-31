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

int main() {
    showcaseWindowAnd();
    return 0;
}