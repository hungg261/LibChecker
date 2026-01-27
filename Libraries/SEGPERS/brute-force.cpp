#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int n, q;
    cin >> n >> q;

    vector<long long> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    vector<vector<long long>> ver;
    ver.push_back({});
    ver.push_back(a);

    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int v, i;
            long long k;
            cin >> v >> i >> k;
            vector<long long> nv = ver[v];
            nv[i] += k;
            ver.push_back(nv);
        } else if (t == 2) {
            int v, l, r;
            cin >> v >> l >> r;
            long long s = 0;
            for (int i = l; i <= r; i++) s += ver[v][i];
            cout << s << '\n';
        } else if (t == 3) {
            int v, l, r;
            cin >> v >> l >> r;
            long long mn = ver[v][l];
            for (int i = l + 1; i <= r; i++) mn = min(mn, ver[v][i]);
            cout << mn << '\n';
        } else if (t == 4) {
            int v, l, r;
            cin >> v >> l >> r;
            long long mx = ver[v][l];
            for (int i = l + 1; i <= r; i++) mx = max(mx, ver[v][i]);
            cout << mx << '\n';
        }
    }

    return 0;
}
