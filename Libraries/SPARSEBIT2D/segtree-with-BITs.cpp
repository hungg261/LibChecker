#include <bits/stdc++.h>
using namespace std;

using ll = long long;

struct BIT {
    int n;
    vector<ll> f;

    BIT() : n(0) {}
    BIT(int n_) : n(n_), f(n_ + 1, 0) {}

    void add(int i, ll v) {
        for (; i <= n; i += i & -i)
            f[i] += v;
    }

    ll sum(int i) const {
        ll s = 0;
        for (; i > 0; i -= i & -i)
            s += f[i];
        return s;
    }

    ll rangeSum(int l, int r) const {
        if (l > r) return 0;
        return sum(r) - sum(l - 1);
    }
};

struct SegNode {
    vector<int> ys;
    BIT bit;

    void build() {
        sort(ys.begin(), ys.end());
        ys.erase(unique(ys.begin(), ys.end()), ys.end());
        bit = BIT((int)ys.size());
    }

    void add(int y, ll v) {
        int idx = lower_bound(ys.begin(), ys.end(), y) - ys.begin() + 1;
        bit.add(idx, v);
    }

    ll query(int y1, int y2) const {
        int r = upper_bound(ys.begin(), ys.end(), y2) - ys.begin();
        int l = lower_bound(ys.begin(), ys.end(), y1) - ys.begin();
        return bit.rangeSum(l + 1, r);
    }
};

struct Query {
    int type;
    int x1, y1, x2, y2;
    ll k;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int q;
    cin >> q;

    vector<Query> queries(q);
    vector<int> xs;

    for (int i = 0; i < q; i++) {
        cin >> queries[i].type;
        if (queries[i].type == 1) {
            cin >> queries[i].x1 >> queries[i].y1 >> queries[i].k;
            xs.push_back(queries[i].x1);
        } else {
            cin >> queries[i].x1 >> queries[i].y1 >> queries[i].x2 >> queries[i].y2;
            xs.push_back(queries[i].x1);
            xs.push_back(queries[i].x2);
        }
    }

    // Compress X
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());
    int N = xs.size();

    auto getX = [&](int x) {
        return lower_bound(xs.begin(), xs.end(), x) - xs.begin();
    };

    vector<SegNode> seg(4 * N);

    // Collect Y-coordinates per segment node
    for (auto &qr : queries) {
        if (qr.type == 1) {
            int x = getX(qr.x1);
            int idx = 1, l = 0, r = N - 1;
            while (true) {
                seg[idx].ys.push_back(qr.y1);
                if (l == r) break;
                int mid = (l + r) >> 1;
                if (x <= mid) {
                    idx <<= 1;
                    r = mid;
                } else {
                    idx = idx << 1 | 1;
                    l = mid + 1;
                }
            }
        } else {
            int lx = getX(qr.x1);
            int rx = getX(qr.x2);
            function<void(int,int,int)> dfs =
                [&](int idx, int l, int r) {
                    if (r < lx || rx < l) return;
                    if (lx <= l && r <= rx) {
                        seg[idx].ys.push_back(qr.y1);
                        seg[idx].ys.push_back(qr.y2);
                        return;
                    }
                    int mid = (l + r) >> 1;
                    dfs(idx << 1, l, mid);
                    dfs(idx << 1 | 1, mid + 1, r);
                };
            dfs(1, 0, N - 1);
        }
    }

    // Build BITs
    for (int i = 1; i < 4 * N; i++) {
        if (!seg[i].ys.empty())
            seg[i].build();
    }

    // Update and query
    function<void(int,int,int,int,int,ll)> update =
        [&](int idx, int l, int r, int pos, int y, ll v) {
            seg[idx].add(y, v);
            if (l == r) return;
            int mid = (l + r) >> 1;
            if (pos <= mid)
                update(idx << 1, l, mid, pos, y, v);
            else
                update(idx << 1 | 1, mid + 1, r, pos, y, v);
        };

    function<ll(int,int,int,int,int,int,int)> query =
        [&](int idx, int l, int r, int ql, int qr, int y1, int y2) -> ll {
            if (r < ql || qr < l) return 0;
            if (ql <= l && r <= qr)
                return seg[idx].query(y1, y2);
            int mid = (l + r) >> 1;
            return query(idx << 1, l, mid, ql, qr, y1, y2)
                 + query(idx << 1 | 1, mid + 1, r, ql, qr, y1, y2);
        };

    for (auto &qr : queries) {
        if (qr.type == 1) {
            int x = getX(qr.x1);
            update(1, 0, N - 1, x, qr.y1, qr.k);
        } else {
            int lx = getX(qr.x1);
            int rx = getX(qr.x2);
            cout << query(1, 0, N - 1, lx, rx, qr.y1, qr.y2) << '\n';
        }
    }

    return 0;
}
