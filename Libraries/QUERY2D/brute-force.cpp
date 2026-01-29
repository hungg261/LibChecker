#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0);

    int n, m, q;
    cin >> n >> m >> q;

    vector<vector<long long>> a(n + 1, vector<long long>(m + 1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> a[i][j];
        }
    }

    while (q--) {
        int type;
        cin >> type;

        if (type == 1) {
            int x, y;
            long long k;
            cin >> x >> y >> k;
            a[x][y] += k;
        } else {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;

            long long sum = 0;
            for (int i = x1; i <= x2; i++) {
                for (int j = y1; j <= y2; j++) {
                    sum += a[i][j];
                }
            }
            cout << sum << '\n';
        }
    }
    return 0;
}
