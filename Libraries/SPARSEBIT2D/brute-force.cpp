#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;

    map<pair<long long, long long>, long long> grid;

    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            long long x, y, k;
            cin >> x >> y >> k;
            grid[{x, y}] += k;
        } else {
            long long x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            long long ans = 0;
            for (auto &it : grid) {
                auto [x, y] = it.first;
                if (x1 <= x && x <= x2 && y1 <= y && y <= y2) {
                    ans += it.second;
                }
            }
            cout << ans << '\n';
        }
    }
    return 0;
}
