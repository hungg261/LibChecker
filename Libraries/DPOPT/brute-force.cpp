#include <bits/stdc++.h>
using namespace std;

int n, k;
vector<long long> a;
long long ans = LLONG_MAX;

void backtrack(int pos, int cuts, vector<int>& split) {
    if (cuts == k - 1) {
        // Tính cost
        long long cur = 0;
        int last = 0;
        for (int c : split) {
            long long s = 0;
            for (int i = last; i <= c; ++i) s += a[i];
            cur += s * s;
            last = c + 1;
        }
        long long s = 0;
        for (int i = last; i < n; ++i) s += a[i];
        cur += s * s;

        ans = min(ans, cur);
        return;
    }

    for (int i = pos; i < n - 1; ++i) {
        split.push_back(i);
        backtrack(i + 1, cuts + 1, split);
        split.pop_back();
    }
}

int main() {
    cin >> n >> k;
    a.resize(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    vector<int> split;
    backtrack(0, 0, split);

    cout << ans << "\n";
}
