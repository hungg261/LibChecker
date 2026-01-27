#include<bits/stdc++.h>
using namespace std;

int main() {
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
            int l, r, k;
            cin >> l >> r >> k;

            vector<long long> v;
            for (int i = l; i <= r; i++) {
                v.push_back(a[i]);
            }

            sort(v.begin(), v.end(), greater<long long>());

            if (k > (int)v.size()) {
                cout << "NO\n";
            } else {
                cout << v[k - 1] << "\n";
            }
        }

        else if (type == 2) {
            int l, r;
            long long x;
            cin >> l >> r >> x;

            int cnt = 0;
            for (int i = l; i <= r; i++) {
                if (a[i] <= x) cnt++;
            }
            cout << cnt << "\n";
        }

        else if (type == 3) {
            int l, r;
            long long x;
            cin >> l >> r >> x;

            long long sum = 0;
            for (int i = l; i <= r; i++) {
                if (a[i] <= x) sum += a[i];
            }
            cout << sum << "\n";
        }

        else if (type == 4) {
            int l, r;
            long long x;
            cin >> l >> r >> x;

            int cnt = 0;
            for (int i = l; i <= r; i++) {
                if (a[i] == x) cnt++;
            }
            cout << cnt << "\n";
        }
    }

    return 0;
}
