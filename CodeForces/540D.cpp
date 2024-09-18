#include <bits/stdc++.h>

using namespace std;

#define FOR(i, a, b) for (int i = a; i < b; i++)
#define FORD(i, a, b) for (int i = b - 1; i >= a; i--)

constexpr int N = 105;
// dp[i][j][k]  = Probability that i rocks, j papers and k scissors are present;
long double dp[N][N][N];

// We cannot just do i, j, k = Sum[(i-1,j,k), (i,j-1,k), (i,j,k-1)] / 3 because
// All pieces of same species aren't considered the same. We are seeking
// holistic equiprobability.
void solve() {
    // Let's begin
    int R, P, S;
    cin >> R >> S >> P;
    dp[R][S][P] = 1;
    int T = R + P + S;
    FORD(t, 1, T + 1) {
        FORD(r, 0, R + 1) {
            FORD(s, 0, S + 1) {
                // We are looking like this because we want to make sure
                // that we try all possible combinations for a particular
                // total state. This will allows us to be sure that we've
                // calculated all the states with just one death next. 
                int p = t - r - s;
                if (p < 0 || p > P) continue;
                // For each r, p, s, we try to kill somebody
                // This also means we already know the probability
                // for the r,p,s state.
                // Killing stops when  we just have elements of just one species
                if (r == 0 && p == 0) continue;
                if (p == 0 && s == 0) continue;
                if (r == 0 && s == 0) continue;
                
                // Calculate ways any elemental species would get killed
                // given that a element is killed for sure.
                // This is called conditional probability.
                int ways_r = r * p;
                int ways_p = p * s;
                int ways_s = r * s;
                int total = ways_p + ways_r + ways_s;
                long double curr = dp[r][s][p];
                if (r > 0) {
                    dp[r-1][s][p] += (curr * ways_r) / total;
                }
                if (s > 0) {
                    dp[r][s-1][p] += (curr * ways_s) / total;
                }
                if (p > 0) {
                    dp[r][s][p-1] += (curr * ways_p) / total;
                }
            }
        }
    }
    long double res_r = 0, res_s = 0, res_p = 0;
    FOR(r, 1, R + 1) res_r += dp[r][0][0];
    FOR(s, 1, S + 1) res_s += dp[0][s][0];
    FOR(p, 1, P + 1) res_p += dp[0][0][p];
    cout << fixed << setprecision(12) << res_r << " " << res_s << " " << res_p;
    cout << endl; 
    return;
}

int main() {
    int t = 1;
    // cin >> t;
    while (t--) solve();
    return 0;
}








