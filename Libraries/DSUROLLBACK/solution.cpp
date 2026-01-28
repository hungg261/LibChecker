#include<bits/stdc++.h>
#define int long long
using namespace std;

struct DSU_Rollback{
    int n;
    vector<int> par, sz;
    vector<int> minVal;
    vector<tuple<int, int, int>> sta;
    int components;

    DSU_Rollback() = default;
    DSU_Rollback(int _sz): n(_sz){
        par.resize(n + 1, -1);
        sz.resize(n + 1);

        minVal.resize(n + 1);
        components = 0;
    }

    void init(){
        for(int v = 1; v <= n; ++v)
            create(v);
    }

    void create(int v){
        if(par[v] == -1) ++components;

        par[v] = v;
        sz[v] = 1;
        minVal[v] = INT_MAX;
    }

    int find(int v){ return par[v] == v ? v : find(par[v]); }
    int Min(int u){ return minVal[find(u)]; }
    int Size(int u){ return sz[find(u)]; }

    void pop(){
        if(sta.empty()) return;

        int b, old_size, old_min; tie(b, old_size, old_min) = sta.back();
        sta.pop_back();

        if(b == -1) return;

        int a = par[b];

        sz[a] = old_size;
        minVal[a] = old_min;
        par[b] = b;
        ++components;
    }

    void unite(int a, int b){
        a = find(a);
        b = find(b);

        if(a == b){
            sta.emplace_back(-1, -1, -1);
            return;
        }

        if(sz[a] < sz[b]) swap(a, b);

        sta.emplace_back(b, sz[a], minVal[a]);
        par[b] = a;
        sz[a] += sz[b];
        minVal[a] = min(minVal[a], minVal[b]);
        --components;
    }
};

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);

    int n, q;
    cin >> n >> q;

    DSU_Rollback dsu(n);
    dsu.init();

    for(int i = 1; i <= n; ++i){
        int cur; cin >> cur;
        dsu.minVal[i] = cur;
    }

    while(q--){
        int type; cin >> type;

        if(type == 0){
            int u, v;
            cin >> u >> v;

            dsu.unite(u, v);
        }
        else if(type == 1){
            dsu.pop();
        }
        else if(type == 2){
            cout << dsu.components << '\n';
        }
        else if(type == 3){
            int u;
            cin >> u;

            cout << dsu.Size(u) << '\n';
        }
        else if(type == 4){
            int u;
            cin >> u;

            cout << dsu.Min(u) << '\n';
        }
    }

    return 0;
}
