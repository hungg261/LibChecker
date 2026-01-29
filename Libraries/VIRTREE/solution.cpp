#include<bits/stdc++.h>
using namespace std;

const int MAXN = 2e5, MAXLG = __lg(MAXN) + 1;
int n, q;
vector<int> adj[MAXN + 5];
int h[MAXN + 5], table[MAXN + 5][MAXLG + 5];
int tin[MAXN + 5], tout[MAXN + 5], Time = 0;

void compute(){
    for(int j = 1; j <= MAXLG; ++j){
        for(int i = 1; i <= n; ++i){
            table[i][j] = table[table[i][j - 1]][j - 1];
        }
    }
}

void dfs(int u, int prv){
    tin[u] = ++Time;
    for(int v: adj[u]){
        if(v == prv) continue;

        h[v] = h[u] + 1;
        table[v][0] = u;
        dfs(v, u);
    }

    tout[u] = Time;
}

int lift(int u, int s){
    for(int b = MAXLG; b >= 0; --b){
        if(s >> b & 1)
            u = table[u][b];
    }
    return u;
}

int find_lca(int u, int v){
    if(h[u] > h[v]) swap(u, v);
    v = lift(v, h[v] - h[u]);

    if(u == v) return u;

    for(int b = MAXLG; b >= 0; --b){
        if(table[u][b] != table[v][b]){
            u = table[u][b];
            v = table[v][b];
        }
    }

    return table[u][0];
}

bool inSubtree(int v, int u){ // does u contain v?
    return tin[u] <= tin[v] && tout[v] <= tout[u];
}

int test;
void query(){
    int k; cin >> k;
    vector<int> arr(k);
    for(int& ele: arr) cin >> ele;

    if(test == 8076){
        cerr << k << '\n';
        for(int ele: arr) cerr << ele << ' '; cerr << '\n';
    }

    sort(arr.begin(), arr.end(), [](const int& a, const int& b){
         return tin[a] < tin[b];
        });

    for(int i = 1; i < k; ++i)
        arr.push_back(find_lca(arr[i - 1], arr[i]));


    sort(arr.begin(), arr.end(), [](const int& a, const int& b){
         return tin[a] < tin[b];
        });
    arr.erase(unique(arr.begin(), arr.end()), arr.end());
    int d = arr.size();

    vector<int> sta;
    sta.push_back(arr[0]);

    cout << d << '\n';
    for(int i = 1; i < d; ++i){
        while(!inSubtree(arr[i], sta.back())) sta.pop_back();
        cout << sta.back() << ' ' << arr[i] << '\n';

        sta.push_back(arr[i]);
    }
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    freopen("16.INP","r",stdin);
    freopen("16.OUT","w",stdout);

    cin >> n >> q;
    for(int i = 1; i < n; ++i){
        int a, b;
        cin >> a >> b;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(1, -1);
    compute();

    for(test = 1; test <= q; ++test){
        query();
        if(test == 8076) break;
    }

    return 0;
}
