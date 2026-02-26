#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
vector<int> adj[MAXN];
int removed[MAXN];
int centroidPar[MAXN];

void decompose(int u, int p){
    centroidPar[u] = p;     // not necessarily centroid
    removed[u] = 1;

    for(int v : adj[u]){
        if(!removed[v])
            decompose(v, u);
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