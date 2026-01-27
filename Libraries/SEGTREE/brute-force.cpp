#include<bits/stdc++.h>
using namespace std;

#define int long long

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);

    int n, q;
    cin >> n >> q;

    vector<long long> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    while (q--) {
        int type;
        cin >> type;

        if (type == 1) {
            int k;
            long long x;
            cin >> k >> x;
            a[k] = x;
        }
        else if (type == 2) {
            int l, r;
            cin >> l >> r;
            long long sum = 0;
            for (int i = l; i <= r; i++) {
                sum += a[i];
            }
            cout << sum << "\n";
        }
        else if (type == 3) {
            int l, r;
            cin >> l >> r;
            long long mn = a[l];
            for (int i = l; i <= r; i++) {
                mn = min(mn, a[i]);
            }
            cout << mn << "\n";
        }
        else if (type == 4) {
            int l, r;
            cin >> l >> r;
            long long mx = a[l];
            for (int i = l; i <= r; i++) {
                mx = max(mx, a[i]);
            }
            cout << mx << "\n";
        }
    }

    return 0;
}
