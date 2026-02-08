#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<long long> a(n);
    for (auto &x : a) cin >> x;

    int len = n / k;
    long long ans = 0;

    for (int i = 0; i < n; ) {
        long long s = 0;
        for (int j = 0; j < len && i < n; j++, i++) {
            s += a[i];
        }
        ans += s * s;
    }

    cout << ans << "\n";
}
