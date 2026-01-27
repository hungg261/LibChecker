#include<bits/stdc++.h>
using namespace std;

#define int long long

const int INF = 1e18;
struct Node{
    int sum, mn, mx;
    Node *l, *r;

    Node(): sum(0), mn(INF), mx(-INF), l(nullptr), r(nullptr){}
    Node(int val): sum(val), mn(val), mx(val), l(nullptr), r(nullptr){}
    Node(Node *_l, Node *_r): l(_l), r(_r){
        sum = l->sum + r->sum;
        mn = min(l->mn, r->mn);
        mx = max(l->mx, r->mx);
    }
};

Node *build(int l, int r, int arr[]){
    if(l == r){
        return new Node(arr[l]);
    }

    int mid = (l + r) >> 1;
    return new Node(build(l, mid, arr), build(mid + 1, r, arr));
}

Node *add(Node *node, int l, int r, int idx, int val){
    if(l == r) return new Node(node->sum + val);

    int mid = (l + r) >> 1;
    if(idx <= mid) return new Node(add(node->l, l, mid, idx, val), node->r);
    else return new Node(node->l, add(node->r, mid + 1, r, idx, val));
}

int getSum(Node *node, int l, int r, int u, int v){
    if(!node || v < l || r < u) return 0;
    if(u <= l && r <= v) return node->sum;

    int mid = (l + r) >> 1;
    return getSum(node->l, l, mid, u, v) + getSum(node->r, mid + 1, r, u, v);
}

int getMin(Node *node, int l, int r, int u, int v){
    if(!node || v < l || r < u) return INF;
    if(u <= l && r <= v) return node->mn;

    int mid = (l + r) >> 1;
    return min(getMin(node->l, l, mid, u, v), getMin(node->r, mid + 1, r, u, v));
}

int getMax(Node *node, int l, int r, int u, int v){
    if(!node || v < l || r < u) return -INF;
    if(u <= l && r <= v) return node->mx;

    int mid = (l + r) >> 1;
    return max(getMax(node->l, l, mid, u, v), getMax(node->r, mid + 1, r, u, v));
}

const int MAXN = 1e5;
const int MAXQ = 1e5;
int arr[MAXN + 5];
Node *versions[MAXQ + 5];
int V;

signed main(){
    ios_base::sync_with_stdio(0); cin.tie(0);

    int n, q;
    cin >> n >> q;

    for(int i = 1; i <= n; ++i)
        cin >> arr[i];
    versions[++V] = build(1, n, arr);

    while(q--){
        int type;
        cin >> type;

        if(type == 1){
            int v, i, k;
            cin >> v >> i >> k;

            versions[++V] = add(versions[v], 1, n, i, k);
        }
        else if(type == 2){
            int v, l, r;
            cin >> v >> l >> r;

            cout << getSum(versions[v], 1, n, l, r) << '\n';
        }
        else if(type == 3){
            int v, l, r;
            cin >> v >> l >> r;

            cout << getMin(versions[v], 1, n, l, r) << '\n';
        }
        else if(type == 4){
            int v, l, r;
            cin >> v >> l >> r;

            cout << getMax(versions[v], 1, n, l, r) << '\n';
        }
    }

    return 0;
}
