#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;

int n;
vector<int> adj[MAXN];
bool removed[MAXN];
int centroidPar[MAXN];

int findSubSz(int u, int p){
    int s = 1;
    for(int v : adj[u]){
        if(v == p || removed[v]) continue;
        s += findSubSz(v, u);
    }
    return s;
}

// ❌ recomputes size repeatedly → O(n²)
int findCentroid(int u, int p){
    int subsz = findSubSz(u, -1);

    for(int v : adj[u]){
        if(v == p || removed[v]) continue;
        if(findSubSz(v, u) > subsz / 2)
            return findCentroid(v, u);
    }
    return u;
}

void decompose(int u, int p){
    int c = findCentroid(u, -1);
    centroidPar[c] = p;
    removed[c] = true;

    for(int v : adj[c]){
        if(!removed[v])
            decompose(v, c);
    }
}

int main(){
    cin >> n;
    for(int i = 1; i < n; i++){
        int a,b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    decompose(1, -1);

    for(int i = 1; i <= n; i++)
        cout << centroidPar[i] << " ";
}