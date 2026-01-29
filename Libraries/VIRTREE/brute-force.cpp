#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
vector<int> g[MAXN];
int parent[MAXN], depth[MAXN], tin[MAXN];
int timer = 0;

void dfs(int u, int p) {
    parent[u] = p;
    depth[u] = (p == 0 ? 0 : depth[p] + 1);
    tin[u] = ++timer;
    for (int v : g[u]) {
        if (v == p) continue;
        dfs(v, u);
    }
}

// LCA trâu vừa - leo từng bước
int lca(int u, int v) {
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

    int n, q;
    cin >> n >> q;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1, 0);

    while (q--) {
        int k;
        cin >> k;
        vector<int> v(k);
        for (int i = 0; i < k; i++) cin >> v[i];

        sort(v.begin(), v.end(), [&](int a, int b) {
            return tin[a] < tin[b];
        });

        vector<int> nodes = v;

        // thêm LCA của các cặp liên tiếp
        for (int i = 0; i + 1 < (int)v.size(); i++) {
            nodes.push_back(lca(v[i], v[i + 1]));
        }

        sort(nodes.begin(), nodes.end(), [&](int a, int b) {
            return tin[a] < tin[b];
        });
        nodes.erase(unique(nodes.begin(), nodes.end()), nodes.end());

        // build virtual tree bằng stack
        vector<pair<int,int>> edges;
        vector<int> st;
        for (int u : nodes) {
            while (!st.empty()) {
                int w = lca(st.back(), u);
                if (w == st.back()) break;
                st.pop_back();
            }
            if (!st.empty()) {
                edges.push_back({st.back(), u});
            }
            st.push_back(u);
        }

        cout << nodes.size() << "\n";
        for (auto [u, v] : edges) {
            cout << u << " " << v << "\n";
        }
    }
    return 0;
}
