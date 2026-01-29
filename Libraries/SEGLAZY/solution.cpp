#include<bits/stdc++.h>
using namespace std;

#define int long long

const int MAXN = 1e5;
const int INF = 1e18;
struct Node{
    long long lazy;
    long long sum;
    int mn, mx;

    Node(): lazy(0), sum(0), mn(0), mx(0){}

    static Node Identity(){
        Node res;
        res.lazy = 0;
        res.sum = 0;
        res.mn = INF;
        res.mx = -INF;

        return res;
    }

    void inc(int x, int l, int r){
        lazy += x;

        sum += x * (r - l + 1);
        mn += x;
        mx += x;
    }

    Node operator + (const Node& other) const{
        Node res;
        res.sum = sum + other.sum;
        res.mn = min(mn, other.mn);
        res.mx = max(mx, other.mx);

        return res;
    }
} nodes[MAXN * 4 + 5];

void push(int id, int l, int r){
    int mid = (l + r) >> 1;
    int& lz = nodes[id].lazy;

    nodes[id << 1].inc(lz, l, mid);
    nodes[id << 1 | 1].inc(lz, mid + 1, r);

    lz = 0;
}

void add(int id, int l, int r, int u, int v, int val){
    if(r < u || v< l) return;
    if(u <= l && r <= v){
        nodes[id].inc(val, l, r);
        return;
    }

    push(id, l, r);

    int mid = (l + r) >> 1;
    add(id << 1, l, mid, u, v, val);
    add(id << 1 | 1, mid + 1, r, u, v, val);
    nodes[id] = nodes[id << 1] + nodes[id << 1 | 1];
}

Node get(int id, int l, int r, int u, int v){
    if(v < l || r < u) return Node::Identity();
    if(u <= l && r <= v) return nodes[id];

    push(id, l, r);

    int mid = (l + r) >> 1;
    return get(id << 1, l, mid, u, v) + get(id << 1 | 1, mid + 1, r, u, v);
}

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);

    int n, q;
    cin >> n >> q;

    for(int i = 1; i <= n; ++i){
        int cur; cin >> cur;
        add(1, 1, n, i, i, cur);
    }

    while(q--){
        int type;
        cin >> type;

        if(type == 1){
            int u, v, x;
            cin >> u >> v >> x;

            add(1, 1, n, u, v, x);
        }
        else{
            int l, r;
            cin >> l >> r;

            Node res = get(1, 1, n, l, r);

            if(type == 2) cout << res.sum << '\n';
            else if(type == 3) cout << res.mn << '\n';
            else cout << res.mx << '\n';
        }
    }

    return 0;
}
