#include <bits/stdc++.h>
using namespace std;

#define int long long

struct SparseFenwickTree2D{
    vector<vector<int>> nodes;
    vector<vector<int>> BIT;
    int n, m;

    SparseFenwickTree2D() = default;
    SparseFenwickTree2D(int _n, int _m): n(_n), m(_m){
        nodes.resize(_n + 1);
        BIT.resize(_n + 1);
    }

    void fakeUpdate(int x, int y){
        for(int i = x; i <= n; i += i & -i)
            nodes[i].push_back(y);
    }

    void fakeQuery(int x, int y){
        for(int i = x; i > 0; i -= i & -i)
            nodes[i].push_back(y);
    }

    void compress(){
        for(int i = 1; i <= n; ++i){
            nodes[i].push_back(0);
            sort(begin(nodes[i]), end(nodes[i]));
            nodes[i].erase(unique(begin(nodes[i]), end(nodes[i])), end(nodes[i]));
            BIT[i].resize((int)nodes[i].size() + 1, 0);
        }
    }

    void update(int x, int y, int val){
        for(int i = x; i <= n; i += i & -i){
            int j = lower_bound(begin(nodes[i]), end(nodes[i]), y) - begin(nodes[i]) + 1;
            for(; j <= (int)nodes[i].size(); j += j & -j)
                BIT[i][j] += val;
        }
    }

    int get(int x, int y){
        int res = 0;
        for(int i = x; i > 0; i -= i & -i){
            int j = lower_bound(begin(nodes[i]), end(nodes[i]), y) - begin(nodes[i]) + 1;
            for(; j > 0; j -= j & -j)
                res += BIT[i][j];
        }
        return res;
    }

    int get(int x1, int y1, int x2, int y2){
        return get(x2, y2)
             - get(x1 - 1, y2)
             - get(x2, y1 - 1)
             + get(x1 - 1, y1 - 1);
    }
};

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);

    int Q;
    cin >> Q;

    struct Query{
        int type;
        int x, y, w;
        int x1, y1, x2, y2;
    };

    vector<Query> queries(Q);
    vector<int> xs;

    for(int i = 0; i < Q; i++){
        cin >> queries[i].type;
        if(queries[i].type == 1){
            cin >> queries[i].x >> queries[i].y >> queries[i].w;
            xs.push_back(queries[i].x);
        }else{
            cin >> queries[i].x1 >> queries[i].y1
                >> queries[i].x2 >> queries[i].y2;
            xs.push_back(queries[i].x1);
            xs.push_back(queries[i].x2);
        }
    }

    // compress x
    sort(xs.begin(), xs.end());
    xs.erase(unique(xs.begin(), xs.end()), xs.end());

    auto cx = [&](int x){
        return lower_bound(xs.begin(), xs.end(), x) - xs.begin() + 1;
    };

    SparseFenwickTree2D bit(xs.size(), 0);

    for(auto &q : queries){
        if(q.type == 1){
            bit.fakeUpdate(cx(q.x), q.y);
        }else{
            bit.fakeQuery(cx(q.x2), q.y2);
            bit.fakeQuery(cx(q.x1) - 1, q.y2);
            bit.fakeQuery(cx(q.x2), q.y1 - 1);
            bit.fakeQuery(cx(q.x1) - 1, q.y1 - 1);
        }
    }

    bit.compress();

    for(auto &q : queries){
        if(q.type == 1){
            bit.update(cx(q.x), q.y, q.w);
        }else{
            int l = cx(q.x1);
            int r = cx(q.x2);
            if(l > r){
                cout << 0 << '\n';
            }else{
                cout << bit.get(l, q.y1, r, q.y2) << '\n';
            }
        }
    }

    return 0;
}
