#include <bits/stdc++.h>
using namespace std;

#define int long long
const int INF = 1e18;

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int n, q;
    cin >> n >> q;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    while (q--) {
        int type;
        cin >> type;

        if (type == 1) {
            int l, r, k;
            cin >> l >> r >> k;
            for (int i = l; i <= r; i++) {
                a[i] += k;
            }
        } else {
            int l, r;
            cin >> l >> r;

            if (type == 2) {
                int sum = 0;
                for (int i = l; i <= r; i++) sum += a[i];
                cout << sum << '\n';
            }
            else if (type == 3) {
                int mn = INF;
                for (int i = l; i <= r; i++) mn = min(mn, a[i]);
                cout << mn << '\n';
            }
            else if (type == 4) {
                int mx = -INF;
                for (int i = l; i <= r; i++) mx = max(mx, a[i]);
                cout << mx << '\n';
            }
        }
    }

    return 0;
}
