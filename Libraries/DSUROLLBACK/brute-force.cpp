#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<long long> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    vector<pair<int,int>> edges;

    while (q--) {
        int type;
        cin >> type;

        if (type == 0) {
            int u, v;
            cin >> u >> v;
            edges.push_back({u, v});
        }
        else if (type == 1) {
            if (!edges.empty()) edges.pop_back();
        }
        else {
            vector<vector<int>> adj(n + 1);
            for (auto &e : edges) {
                adj[e.first].push_back(e.second);
                adj[e.second].push_back(e.first);
            }

            vector<int> vis(n + 1, 0);

            if (type == 2) {
                int components = 0;
                for (int i = 1; i <= n; i++) {
                    if (!vis[i]) {
                        components++;
                        queue<int> qu;
                        qu.push(i);
                        vis[i] = 1;
                        while (!qu.empty()) {
                            int u = qu.front(); qu.pop();
                            for (int v : adj[u]) {
                                if (!vis[v]) {
                                    vis[v] = 1;
                                    qu.push(v);
                                }
                            }
                        }
                    }
                }
                cout << components << '\n';
            }
            else if (type == 3) {
                int u;
                cin >> u;
                int cnt = 0;
                queue<int> qu;
                qu.push(u);
                vis[u] = 1;
                while (!qu.empty()) {
                    int x = qu.front(); qu.pop();
                    cnt++;
                    for (int v : adj[x]) {
                        if (!vis[v]) {
                            vis[v] = 1;
                            qu.push(v);
                        }
                    }
                }
                cout << cnt << '\n';
            }
            else if (type == 4) {
                int u;
                cin >> u;
                long long mn = LLONG_MAX;
                queue<int> qu;
                qu.push(u);
                vis[u] = 1;
                while (!qu.empty()) {
                    int x = qu.front(); qu.pop();
                    mn = min(mn, a[x]);
                    for (int v : adj[x]) {
                        if (!vis[v]) {
                            vis[v] = 1;
                            qu.push(v);
                        }
                    }
                }
                cout << mn << '\n';
            }
        }
    }

    return 0;
}
