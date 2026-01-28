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
int v_tin[MAXN], v_tout[MAXN]; // Đã đổi tên để tránh lỗi C2040
int timer_dfs;

void dfs_lca(int v, int p) {
    v_tin[v] = ++timer_dfs;
    up_lca[v][0] = p;
    for (int i = 1; i < LOGN; i++)
        up_lca[v][i] = up_lca[up_lca[v][i - 1]][i - 1];
    for (int u : adj[v]) {
        if (u != p) dfs_lca(u, v);
    }
    v_tout[v] = timer_dfs;
}

bool is_ancestor(int u, int v) {
    return v_tin[u] <= v_tin[v] && v_tout[u] >= v_tout[v];
}

struct DsuVT {
    std::vector<int> parent;
    int components;
    DsuVT(int n) : components(0) {
        parent.resize(n + 1);
        for(int i = 0; i <= n; i++) parent[i] = i;
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
        std::set<int> required_nodes;
        for (int i = 0; i < k; i++) {
            required_nodes.insert(inf.readInt());
        }

        int d_ouf = ouf.readInt();
        if (d_ouf < 1) quitf(_wa, "Query %d: d must be positive", t);

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
                
                if (nodes_in_vtree.find(u) == nodes_in_vtree.end()) {
                    nodes_in_vtree.insert(u);
                    dsu.add_node();
                }
                if (nodes_in_vtree.find(v) == nodes_in_vtree.end()) {
                    nodes_in_vtree.insert(v);
                    dsu.add_node();
                }
                
                if (!is_ancestor(u, v) && !is_ancestor(v, u))
                    quitf(_wa, "Query %d: Edge (%d, %d) is not a parent-child relation", t, u, v);
                
                if (!dsu.unite(u, v))
                    quitf(_wa, "Query %d: Cycle detected in Virtual Tree", t);
            }
        }

        if ((int)nodes_in_vtree.size() != d_ouf)
            quitf(_wa, "Query %d: Number of distinct nodes does not match d", t);

        for (int req : required_nodes) {
            if (nodes_in_vtree.find(req) == nodes_in_vtree.end())
                quitf(_wa, "Query %d: Required node %d is missing", t, req);
        }

        if (dsu.components != 1)
            quitf(_wa, "Query %d: Virtual Tree is disconnected", t);
    }

    quitf(_ok, "Correct.");
    return 0;
}
