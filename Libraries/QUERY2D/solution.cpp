#include<bits/stdc++.h>
using namespace std;

#define int long long

struct FenwickTree2D{
    int n, m;
    vector<vector<int>> BIT;

    FenwickTree2D(int sz_n, int sz_m): n(sz_n), m(sz_m){
        BIT.resize(n + 1, vector<int>(m + 1, 0));
    }

    void add(int x, int y, int val){
        for(int i = x; i <= n; i += i & -i)
            for(int j = y; j <= m; j += j & -j)
                BIT[i][j] += val;
    }

    int get(int x, int y){
        int res = 0;
        for(int i = x; i > 0; i -= i & -i)
            for(int j = y; j > 0; j -= j & -j)
                res += BIT[i][j];

        return res;
    }

    int get(int x1, int y1, int x2, int y2){
        return get(x2, y2) - get(x1 - 1, y2) - get(x2, y1 - 1) + get(x1 - 1, y1 - 1);
    }
};

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);

    int n, m, q;
    cin >> n >> m >> q;

    FenwickTree2D fwt(n, m);
    for(int i = 1; i <= n; ++i){
        for(int j = 1; j <= m; ++j){
            int cur; cin >> cur;
            fwt.add(i, j, cur);
        }
    }

    while(q--){
        int type;
        cin >> type;

        if(type == 1){
            int x, y, k;
            cin >> x >> y >> k;

            fwt.add(x, y, k);
        }
        else{
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;

            cout << fwt.get(x1, y1, x2, y2) << '\n';
        }
    }

    return 0;
}
