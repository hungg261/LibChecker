#include <bits/stdc++.h>
using namespace std;

const long long INF = LLONG_MAX / 4;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<long long> a(n + 1), S(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        S[i] = S[i - 1] + a[i];
    }

    vector<long long> dp_prev(n + 1, INF), dp_cur(n + 1, INF);
    dp_prev[0] = 0;

    for (int t = 1; t <= k; t++) {
        fill(dp_cur.begin(), dp_cur.end(), INF);

        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; j++) {
                long long sum = S[i] - S[j];
                dp_cur[i] = min(dp_cur[i],
                                 dp_prev[j] + sum * sum);
            }
        }

        swap(dp_prev, dp_cur);
    }

    cout << dp_prev[n] << "\n";
}
