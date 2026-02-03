#include <bits/stdc++.h>
using namespace std;

static const int MAXN = 5e3;

long long bit[MAXN + 1][MAXN + 1]; // impossible

void update(int x, int y, long long v) {
    for (int i = x; i <= MAXN; i += i & -i)
        for (int j = y; j <= MAXN; j += j & -j)
            bit[i][j] += v;
}

long long query(int x, int y) {
    long long res = 0;
    for (int i = x; i > 0; i -= i & -i)
        for (int j = y; j > 0; j -= j & -j)
            res += bit[i][j];
    return res;
}

long long rect(int x1, int y1, int x2, int y2) {
    return query(x2, y2)
         - query(x1 - 1, y2)
         - query(x2, y1 - 1)
         + query(x1 - 1, y1 - 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int x, y;
            long long k;
            cin >> x >> y >> k;
            update(x, y, k);
        } else {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            cout << rect(x1, y1, x2, y2) << '\n';
        }
    }
}
