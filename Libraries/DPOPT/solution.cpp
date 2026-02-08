#include<bits/stdc++.h>
using namespace std;

#define int long long

const int MAXN = 1e5, MAXK = 20;
int arr[MAXN + 5], n, k, pre[MAXN + 5];
int dp[MAXK + 5][MAXN + 5];

inline int pow2(int x){ return x * x; } 
int cost(int l, int r){
    return pow2(pre[r] - pre[l - 1]);
}

void compute(int c, int l, int r, int optL, int optR){
    if(l > r) return;
    
    int mid = (l + r) >> 1;
    pair<int, int> best = {LLONG_MAX, -1};
    for(int i = optL; i <= min(mid, optR); ++i){
        best = min(best, {dp[c - 1][i - 1] + cost(i, mid), i});
    }
    
    dp[c][mid] = best.first;
    int opt = best.second;
    
    compute(c, l, mid - 1, optL, opt);
    compute(c, mid + 1, r, opt, optR);
}

void solve(){
    memset(dp, 0x3f, sizeof dp);
    dp[0][0] = 0;
    for(int j = 1; j <= k; ++j){
        compute(j, 1, n, 1, n);
    }
    
    cout << dp[k][n] << '\n';
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n >> k;
    for(int i = 1; i <= n; ++i){
        cin >> arr[i];
        pre[i] = pre[i - 1] + arr[i];
    }
    
    solve();
    
    return 0;
}