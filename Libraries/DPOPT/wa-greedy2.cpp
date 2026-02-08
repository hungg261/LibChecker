#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<long long> a(n);
    for (auto &x : a) cin >> x;

    long long ans = 0, cur = 0;
    int segments = 1;

    for (int i = 0; i < n; i++) {
        long long add = (cur + a[i]) * (cur + a[i]) - cur * cur;
        if (segments < k && add > cur * cur) {
            ans += cur * cur;
            cur = 0;
            segments++;
        }
        cur += a[i];
    }

    ans += cur * cur;
    cout << ans << "\n";
}
