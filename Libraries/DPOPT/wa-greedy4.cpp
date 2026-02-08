#include <bits/stdc++.h>
using namespace std;

const long long INF = 1e18;

int main() {
    int n, k;
    cin >> n >> k;
    vector<long long> a(n + 1), S(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        S[i] = S[i - 1] + a[i];
    }

    vector<long long> dp(n + 1, INF);
    dp[0] = 0;

    for (int t = 1; t <= k; t++) {
        vector<long long> ndp(n + 1, INF);
        int best_j = 0;

        for (int i = 1; i <= n; i++) {
            long long cost = dp[best_j] + (S[i] - S[best_j]) * (S[i] - S[best_j]);
            ndp[i] = cost;

            if (dp[i] < dp[best_j]) best_j = i;
        }
        dp.swap(ndp);
    }

    cout << dp[n] << "\n";
}
