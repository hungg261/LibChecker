#ifdef _MSC_VER
#   pragma warning(push)
#   pragma warning(disable: 4459)
#endif
 
#include "testlib.h"
 
#ifdef _MSC_VER
#   pragma warning(pop)
#endif
 
#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
 
int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
 
    int n = inf.readInt();
    vector<pair<int, int>> edges;
    vector<vector<int>> orig_adj(n + 1);
    for (int i = 1; i < n; ++i) {
        int a = inf.readInt();
        int b = inf.readInt();
        edges.emplace_back(a, b);
        orig_adj[a].push_back(b);
        orig_adj[b].push_back(a);
    }
 
    vector<int> par(n + 1);
    int root = -1;
    for (int i = 1; i <= n; ++i) {
        int x = ouf.readInt();
        if (x < -1 || x > n)
            quitf(_wa, "parent value out of range for node %d", i);
        if (x == -1) {
            if (root != -1)
                quitf(_wa, "multiple roots found");
            root = i;
        } else if (x == i) {
            quitf(_wa, "node %d has self as parent", i);
        }
        par[i] = x;
    }
    ouf.skipBlanks();
    ouf.readEof();
 
    if (root == -1)
        quitf(_wa, "no root found");
 
    vector<vector<int>> children(n + 1);
    for (int i = 1; i <= n; ++i) {
        if (par[i] != -1)
            children[par[i]].push_back(i);
    }
 
    vector<int> tin(n + 1, 0), tout(n + 1, 0), sz_cent(n + 1, 0);
    int timer = 0;
    stack<pair<int, int>> st;
    st.push({root, 0});
 
    while (!st.empty()) {
        auto [u, state] = st.top();
        st.pop();
        if (state == 0) {
            tin[u] = ++timer;
            st.push({u, 1});
            for (int v : children[u])
                st.push({v, 0});
        } else {
            sz_cent[u] = 1;
            for (int v : children[u])
                sz_cent[u] += sz_cent[v];
            tout[u] = timer;
        }
    }
 
    for (int i = 1; i <= n; ++i) {
        if (tin[i] == 0)
            quitf(_wa, "node %d not reachable from root in centroid tree", i);
    }
 
    for (int u = 1; u <= n; ++u) {
        int max_child_sz = 0;
        for (int v : children[u])
            max_child_sz = max(max_child_sz, sz_cent[v]);
        if (max_child_sz * 2 > sz_cent[u])
            quitf(_wa, "node %d fails centroid condition: max child size = %d, total = %d",
                  u, max_child_sz, sz_cent[u]);
    }
 
    for (auto &e : edges) {
        int a = e.first, b = e.second;
        bool a_anc_of_b = (tin[a] <= tin[b] && tout[b] <= tout[a]);
        bool b_anc_of_a = (tin[b] <= tin[a] && tout[a] <= tout[b]);
        if (!a_anc_of_b && !b_anc_of_a)
            quitf(_wa, "original edge (%d,%d) connects nodes from different centroid subtrees", a, b);
    }
 
    quitf(_ok, "centroid decomposition is valid");
}
