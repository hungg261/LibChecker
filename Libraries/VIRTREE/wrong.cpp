#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200000;

int n, q;
vector<int> adj[MAXN + 5];
int parent[MAXN + 5];
int depth[MAXN + 5];

void dfs(int u, int p) {
    parent[u] = p;
    for (int v : adj[u]) {
        if (v == p) continue;
        depth[v] = depth[u] + 1;
        dfs(v, u);
    }
}

int lca_slow(int u, int v) {
    // VERY SLOW LCA
    while (depth[u] > depth[v]) u = parent[u];
    while (depth[v] > depth[u]) v = parent[v];
    while (u != v) {
        u = parent[u];
        v = parent[v];
    }
    return u;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs(1, 0);

    while (q--) {
        int k;
        cin >> k;
        vector<int> v(k);
        for (int i = 0; i < k; i++)
            cin >> v[i];

        // Brute force: mark all nodes on all pair paths
        set<int> nodes;
        for (int i = 0; i < k; i++) {
            for (int j = i + 1; j < k; j++) {
                int u = v[i], w = v[j];
                int l = lca_slow(u, w);

                // go up from u to lca
                while (u != l) {
                    nodes.insert(u);
                    u = parent[u];
                }

                // go up from w to lca
                while (w != l) {
                    nodes.insert(w);
                    w = parent[w];
                }

                nodes.insert(l);
            }
        }

        if (nodes.empty()) {
            // k = 1 case
            cout << 1 << '\n';
            continue;
        }

        vector<int> vt(nodes.begin(), nodes.end());

        // Try to output a "tree" (WRONG)
        cout << vt.size() << '\n';
        for (int i = 1; i < (int)vt.size(); i++) {
            cout << vt[i - 1] << " " << vt[i] << '\n';
        }
    }

    return 0;
}
