/*
Question: You have a CPU with n processors line up sequentially from 1 to n.
Each processor i has three efficiency values defined:
- no_adjacent[i] = Efficiency when it was started and both adjacent processors were down.
- one_adjacent[i] = Efficiency when it was started and only one of the adjacent processors were up.
- both_adjacent[i] = Efficiency when it was started and both the adjacent processors were up.

Find the maximum efficiency we can achive out of all startup sequences.

For, 
n = 4
no_adjacent = [1 2 3 4]
one_adjacent = [4 4 2 1]
two_adjacent = [0 1 1 0]

Best startup sequence would be 4 -> 3 -> 2 -> 1 giving us efficiency = 4 + 2 + 4 + 4 = 14
*/


#include <bits/stdc++.h>

using namespace std;
using vi = vector<int>;
const int NINF = -1e9;

int BestScheduling(int n, vi &no_adjacent, vi &one_adjacent, vi &both_adjacent);

struct Best{
    int left_first, left_last, right_first, right_last;
    Best(): left_first(NINF), left_last(NINF), right_first(NINF), right_last(NINF) {}
    Best(int val): left_first(val), left_last(NINF), right_first(val), right_last(NINF) {}
    int getMax() {
        return max({left_first, left_last, right_first, right_last});
    }
};
Best BestScheduling(int l, int r, vi &no_adjacent, vi &one_adjacent, vi &both_adjacent);

int main() {
    int n;
    cin >> n;

    vi no_adjacent(n), one_adjacent(n), both_adjacent(n);
    for (int i = 0 ; i < n ; i++) cin >> no_adjacent[i];
    for (int i = 0 ; i < n ; i++) cin >> one_adjacent[i];
    for (int i = 0 ; i < n ; i++) cin >> both_adjacent[i];

    cout << BestScheduling(n, no_adjacent, one_adjacent, both_adjacent) << endl;
    return 0;
}


int BestScheduling(int n, vi &no_adjacent, vi &one_adjacent, vi &both_adjacent) {
    Best result = BestScheduling(0, n, no_adjacent, one_adjacent, both_adjacent);
    return result.getMax();
}

Best BestScheduling(int l, int r, vi &no_adjacent, vi &one_adjacent, vi &both_adjacent) {
    if (r - l == 1) return Best(no_adjacent[l]);
    int m = (r + l) >> 1;
    Best res_l = BestScheduling(l, m, no_adjacent, one_adjacent, both_adjacent);
    Best res_r = BestScheduling(m, r, no_adjacent, one_adjacent, both_adjacent);
    Best res_total;

    // When all left processors are turned on first
    int r_contribution = max(
        res_r.left_first - no_adjacent[m] + one_adjacent[m],
        res_r.left_last - one_adjacent[m] + both_adjacent[m]
    );
    res_total.left_first = res_l.left_first + r_contribution; 
    res_total.left_last = res_l.left_last + r_contribution;

    // When all right processors are turned on first
    int l_contribution = max(
        res_l.right_first - no_adjacent[m - 1] + one_adjacent[m - 1],
        res_l.right_last - one_adjacent[m - 1] + both_adjacent[m - 1]
    );
    res_total.right_first = res_r.right_first + l_contribution;
    res_total.right_last = res_r.right_last + l_contribution;

    return res_total;
}