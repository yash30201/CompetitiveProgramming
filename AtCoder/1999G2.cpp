#include <bits/stdc++.h>

using namespace std;

int ask(int x, int y) {
    cout << "? " << x << " " << y << endl;
    int z;
    cin >> z;
    return z;
}
void say(int x) {
    cout << "! " << x << endl;
}
void solve() {
    // Let's begin
    int l = 1, r = 1001;
    while (r - l > 3) {
        int d = (r - l) / 3;
        int m1 = l + d, m2 = r - d;
        int x = ask(m1, m2);
        if (x == (m1 + 1) * (m2 + 1)) {
            r = m1 + 1;
        } else if (x == m1 * (m2 + 1)) {
            l = m1 + 1, r = m2 + 1;
        } else {
            l = m2 + 1;
        }
    }
    if (r - l == 1) say(l);
    else if (r - l == 2) {
        if (ask(l, l + 1) == (l + 1) * (l + 2)) say(l);
        else say(l + 1);
    } else {
        int x = ask(l, l + 1);
        if (x == (l + 1) * (l + 2)) say(l);
        else if (x == l * (l + 2)) say(l + 1);
        else say(l + 2);
    }
    return;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    int t = 1;
    cin >> t;
    while (t--) solve();
    return 0;
}








