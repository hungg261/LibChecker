#ifdef _MSC_VER
#   pragma warning(push)
#   pragma warning(disable: 4459)
#endif

#include "testlib.h"

#ifdef _MSC_VER
#   pragma warning(pop)
#endif

#include <vector>
#include <set>
#include <algorithm>

const int MAXN = 200005;
const int LOGN = 20;

std::vector<int> adj[MAXN];
int up_lca[MAXN][LOGN];
int entry_time[MAXN], exit_time[MAXN];
int timer_dfs;

void dfs_lca(int v, int p) {
    entry_time[v] = ++timer_dfs;
    up_lca[v][0] = p;
    for (int i = 1; i < LOGN; i++)
        up_lca[v][i] = up_lca[up_lca[v][i - 1]][i - 1];
    for (int u : adj[v]) {
        if (u != p) dfs_lca(u, v);
    }
    exit_time[v] = timer_dfs;
}

bool is_ancestor(int u, int v) {
    return entry_time[u] <= entry_time[v] && exit_time[u] >= exit_time[v];
}

int get_lca(int u, int v) {
    if (is_ancestor(u, v)) return u;
    if (is_ancestor(v, u)) return v;
    for (int i = LOGN - 1; i >= 0; i--) {
        if (!is_ancestor(up_lca[u][i], v)) {
            u = up_lca[u][i];
        }
    }
    return up_lca[u][0];
}

struct DsuVT {
    std::vector<int> parent;
    int components;
    DsuVT(int n) : components(0) {
        parent.resize(n + 1);
        for (int i = 0; i <= n; i++) parent[i] = i;
    }
    int find(int i) {
        return (parent[i] == i) ? i : (parent[i] = find(parent[i]));
    }
    void add_node() { components++; }
    bool unite(int i, int j) {
        int root_i = find(i), root_j = find(j);
        if (root_i != root_j) {
            parent[root_i] = root_j;
            components--;
            return true;
        }
        return false;
    }
};

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int q = inf.readInt();
    for (int i = 0; i < n - 1; i++) {
        int u = inf.readInt();
        int v = inf.readInt();
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    timer_dfs = 0;
    dfs_lca(1, 1);

    for (int t = 1; t <= q; t++) {
        int k = inf.readInt();
        std::vector<int> required_nodes(k);
        for (int i = 0; i < k; i++) {
            required_nodes[i] = inf.readInt();
        }

        // Tính số nút tối thiểu của cây ảo
        std::set<int> min_nodes_set(required_nodes.begin(), required_nodes.end());
        if (k > 1) {
            std::sort(required_nodes.begin(), required_nodes.end(),
                [](int a, int b) { return entry_time[a] < entry_time[b]; });
            for (int i = 0; i < k - 1; i++) {
                int lca_val = get_lca(required_nodes[i], required_nodes[i + 1]);
                min_nodes_set.insert(lca_val);
            }
        }
        int min_nodes = (int)min_nodes_set.size();

        int d_ouf = ouf.readInt();
        if (d_ouf < 1) {
            quitf(_wa, "Query %d: d must be positive, found %d", t, d_ouf);
        }

        // Nếu d_ouf không tối ưu, đọc phần còn lại của output và báo WA
        if (d_ouf != min_nodes) {
            if (d_ouf == 1) {
                ouf.readInt(1, n, "v");
            } else {
                for (int i = 0; i < d_ouf - 1; i++) {
                    ouf.readInt(1, n, "u");
                    ouf.readInt(1, n, "v");
                }
            }
            quitf(_wa, "Query %d: d = %d, but minimum possible is %d", t, d_ouf, min_nodes);
        }

        DsuVT dsu(n);
        std::set<int> nodes_in_vtree;

        if (d_ouf == 1) {
            int v = ouf.readInt(1, n, "v");
            nodes_in_vtree.insert(v);
            dsu.add_node();
        } else {
            for (int i = 0; i < d_ouf - 1; i++) {
                int u = ouf.readInt(1, n, "u");
                int v = ouf.readInt(1, n, "v");

                if (!nodes_in_vtree.count(u)) {
                    nodes_in_vtree.insert(u);
                    dsu.add_node();
                }
                if (!nodes_in_vtree.count(v)) {
                    nodes_in_vtree.insert(v);
                    dsu.add_node();
                }

                if (!is_ancestor(u, v) && !is_ancestor(v, u)) {
                    quitf(_wa, "Query %d: Edge (%d, %d) is not a parent-child relation", t, u, v);
                }

                if (!dsu.unite(u, v)) {
                    quitf(_wa, "Query %d: Cycle detected in Virtual Tree", t);
                }
            }
        }

        if ((int)nodes_in_vtree.size() != d_ouf) {
            quitf(_wa, "Query %d: Number of distinct nodes (%d) does not match d (%d)",
                  t, (int)nodes_in_vtree.size(), d_ouf);
        }

        for (int req : required_nodes) {
            if (!nodes_in_vtree.count(req)) {
                quitf(_wa, "Query %d: Required node %d is missing", t, req);
            }
        }

        if (dsu.components != 1) {
            quitf(_wa, "Query %d: Virtual Tree is disconnected", t);
        }

        if (nodes_in_vtree != min_nodes_set) {
            quitf(_wa, "Query %d: Virtual Tree nodes set is not minimal", t);
        }
    }

    quitf(_ok, "Correct.");
    return 0;
}