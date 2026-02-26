#include<bits/stdc++.h>
using namespace std;

const int MAXN = 2e5;
int n;
vector<int> adj[MAXN + 5];
int Sz[MAXN + 5];
int removed[MAXN + 5];
int centroidPar[MAXN + 5];

int findSubSz(int u, int prv){
    int depth = 1;
    for(int v: adj[u]){
        if(v == prv || removed[v]) continue;

        depth += findSubSz(v, u);
    }

    return Sz[u] = depth;
}

int findCentroid(int u, int prv, int subsz){
    for(int v: adj[u]){
        if(v == prv || removed[v]) continue;

        if(Sz[v] > subsz / 2)
            return findCentroid(v, u, subsz);
    }

    return u;
}

void decompose(int u, int prv){
    int subsz = findSubSz(u, -1);
    int centroid = findCentroid(u, -1, subsz);

    centroidPar[centroid] = prv;
    removed[centroid] = true;

    for(int v: adj[centroid]){
        if(removed[v]) continue;
        decompose(v, centroid);
    }
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    cin >> n;
    for(int i = 1; i < n; ++i){
        int a, b;
        cin >> a >> b;

        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    decompose(1, -1);

    for(int u = 1; u <= n; ++u){
        cout << centroidPar[u] << ' ';
    }

    return 0;
}
