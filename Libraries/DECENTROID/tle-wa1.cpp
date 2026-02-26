#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
vector<int> adj[MAXN];
int Sz[MAXN], removed[MAXN], centroidPar[MAXN];

int findSubSz(int u, int p){
    Sz[u] = 1;
    for(int v : adj[u]){
        if(v == p) continue;      // forgot removed check
        Sz[u] += findSubSz(v, u);
    }
    return Sz[u];
}

int findCentroid(int u, int p, int subsz){
    for(int v : adj[u]){
        if(v == p || removed[v]) continue;
        if(Sz[v] > subsz/2)
            return findCentroid(v, u, subsz);
    }
    return u;
}

void decompose(int u, int p){
    int subsz = findSubSz(u, -1);
    int c = findCentroid(u, -1, subsz);
    centroidPar[c] = p;
    removed[c] = 1;

    for(int v : adj[c]){
        if(!removed[v])
            decompose(v, c);
    }
}

int main(){
    int n;
    cin >> n;
    for(int i = 1; i < n; i++){
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    decompose(1, -1);

    for(int i = 1; i <= n; i++)
        cout << centroidPar[i] << " ";
}