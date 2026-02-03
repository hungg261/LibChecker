#include <bits/stdc++.h>
using namespace std;

#define int long long
 
struct SparseBIT2D {
    int n;
    vector<vector<int>> ys;
    vector<vector<long long>> bit;
 
    SparseBIT2D(int n) : n(n) {
        ys.resize(n + 1);
        bit.resize(n + 1);
    }
 
    void fake_update(int x, int y) {
        for (int i = x; i <= n; i += i & -i) {
            ys[i].push_back(y);
        }
    }
 
    void build() {
        for (int i = 1; i <= n; i++) {
            sort(ys[i].begin(), ys[i].end());
            ys[i].erase(unique(ys[i].begin(), ys[i].end()), ys[i].end());
            bit[i].assign(ys[i].size() + 1, 0);
        }
    }
 
    void update(int x, int y, long long v) {
        for (int i = x; i <= n; i += i & -i) {
            int j = lower_bound(ys[i].begin(), ys[i].end(), y) - ys[i].begin() + 1;
            for (; j < (int)bit[i].size(); j += j & -j) {
                bit[i][j] += v;
            }
        }
    }
 
    long long query(int x, int y) const {
        long long res = 0;
        for (int i = x; i > 0; i -= i & -i) {
            int j = upper_bound(ys[i].begin(), ys[i].end(), y) - ys[i].begin();
            for (; j > 0; j -= j & -j) {
                res += bit[i][j];
            }
        }
        return res;
    }
 
    long long rect(int x1, int y1, int x2, int y2) const {
        return query(x2, y2)
             - query(x1 - 1, y2)
             - query(x2, y1 - 1)
             + query(x1 - 1, y1 - 1);
    }
};
 
signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
 
    int Q;
    cin >> Q;
 
    struct Query {
        int type;
        int x, y, w;
        int l, d, r, u;
    };
 
    vector<Query> queries(Q);
    vector<int> xs;
 
    for (int i = 0; i < Q; i++) {
        cin >> queries[i].type;
        if (queries[i].type == 1) {
            cin >> queries[i].x >> queries[i].y >> queries[i].w;
            xs.push_back(queries[i].x);
        } else {
            cin >> queries[i].l >> queries[i].d
                >> queries[i].r >> queries[i].u;
            xs.push_back(queries[i].l);
            xs.push_back(queries[i].r);
        }
    }
 
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
 
    auto cx = [&](int x) {
        return lower_bound(xs.begin(), xs.end(), x) - xs.begin() + 1;
    };
 
    SparseBIT2D bit(xs.size());
 
    for (auto &q : queries) {
        if (q.type == 1) {
            bit.fake_update(cx(q.x), q.y);
        }
    }
 
    bit.build();
 
    for (auto &q : queries) {
        if (q.type == 1) {
            bit.update(cx(q.x), q.y, q.w);
        } else {
            int l = cx(q.l);
            int r = cx(q.r);
            if (l > r) {
                cout << 0 << '\n';
            } else {
                cout << bit.rect(l, q.d, r, q.u) << '\n';
            }
        }
    }
 
    return 0;
}
