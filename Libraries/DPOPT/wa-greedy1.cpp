#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<long long> a(n);
    for (auto &x : a) cin >> x;

    long long total = accumulate(a.begin(), a.end(), 0LL);
    long long target = total / k;

    long long cur = 0, ans = 0;
    int used = 1;

    for (int i = 0; i < n; i++) {
        if (used < k && cur + a[i] > target) {
            ans += cur * cur;
            cur = 0;
            used++;
        }
        cur += a[i];
    }
    ans += cur * cur;

    cout << ans << "\n";
}
