#include <bits/stdc++.h>
using namespace std;

const long double EPS = 1e-12;

int sgn(long double x){
    if(fabsl(x) < EPS) return 0;
    return x < 0 ? -1 : 1;
}

struct P{
    long double x,y;

    P(){}
    P(long double x,long double y):x(x),y(y){}

    P operator+(P o)const{return {x+o.x,y+o.y};}
    P operator-(P o)const{return {x-o.x,y-o.y};}
    P operator*(long double k)const{return {x*k,y*k};}
};

long double dot(P a,P b){
    return a.x*b.x + a.y*b.y;
}

long double cross(P a,P b){
    return a.x*b.y - a.y*b.x;
}

long double cross(P a,P b,P c){
    return cross(b-a,c-a);
}

long double norm(P a){
    return sqrtl(dot(a,a));
}

int ccw(P a,P b,P c){
    return sgn(cross(a,b,c));
}

bool onSeg(P a,P b,P p){
    if(ccw(a,b,p)!=0) return false;
    return sgn(dot(p-a,p-b)) <= 0;
}

long double dist(P a,P b){
    return norm(a-b);
}

long double distSeg(P p,P a,P b){
    P ab=b-a, ap=p-a, bp=p-b;

    if(sgn(dot(ap,ab))<0) return norm(ap);
    if(sgn(dot(bp,ab))>0) return norm(bp);

    return fabsl(cross(ab,ap))/norm(ab);
}

P project(P p,P a,P b){
    P ab=b-a;
    long double t=dot(p-a,ab)/dot(ab,ab);
    return a+ab*t;
}

P reflect(P p,P a,P b){
    P q=project(p,a,b);
    return q*2-p;
}

bool intersectSeg(P a,P b,P c,P d,P &out){

    int o1=ccw(a,b,c);
    int o2=ccw(a,b,d);
    int o3=ccw(c,d,a);
    int o4=ccw(c,d,b);

    if(o1==0 && o2==0 && o3==0 && o4==0)
        return false;

    if(o1*o2>0 || o3*o4>0)
        return false;

    P ab=b-a;
    P cd=d-c;

    long double den=cross(ab,cd);

    if(sgn(den)==0)
        return false;

    long double t=cross(c-a,cd)/den;
    out=a+ab*t;

    return true;
}

int main(){

    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,q;
    cin>>n>>q;

    vector<P> p(n+1);

    for(int i=1;i<=n;i++)
        cin>>p[i].x>>p[i].y;

    cout<<fixed<<setprecision(12);

    while(q--){

        string t;
        cin>>t;

        if(t=="ADD"){
            int i,j;
            cin>>i>>j;
            P r=p[i]+p[j];
            cout<<r.x<<" "<<r.y<<"\n";
        }

        else if(t=="SCALE"){
            int i;
            long double k;
            cin>>i>>k;
            P r=p[i]*k;
            cout<<r.x<<" "<<r.y<<"\n";
        }

        else if(t=="EQUAL"){
            int i,j;
            cin>>i>>j;

            if(sgn(p[i].x-p[j].x)==0 && sgn(p[i].y-p[j].y)==0)
                cout<<"YES\n";
            else
                cout<<"NO\n";
        }

        else if(t=="DOT"){
            int i,j;
            cin>>i>>j;
            cout<<dot(p[i],p[j])<<"\n";
        }

        else if(t=="CROSS"){
            int i,j;
            cin>>i>>j;
            cout<<cross(p[i],p[j])<<"\n";
        }

        else if(t=="CCW"){
            int a,b,c;
            cin>>a>>b>>c;
            cout<<ccw(p[a],p[b],p[c])<<"\n";
        }

        else if(t=="DIST"){
            int i,j;
            cin>>i>>j;
            cout<<dist(p[i],p[j])<<"\n";
        }

        else if(t=="ONSEG"){
            int i,a,b;
            cin>>i>>a>>b;
            cout<<(onSeg(p[a],p[b],p[i])?"YES\n":"NO\n");
        }

        else if(t=="DISTSEG"){
            int i,a,b;
            cin>>i>>a>>b;
            cout<<distSeg(p[i],p[a],p[b])<<"\n";
        }

        else if(t=="PROJECT"){
            int i,a,b;
            cin>>i>>a>>b;
            P r=project(p[i],p[a],p[b]);
            cout<<r.x<<" "<<r.y<<"\n";
        }

        else if(t=="REFLECT"){
            int i,a,b;
            cin>>i>>a>>b;
            P r=reflect(p[i],p[a],p[b]);
            cout<<r.x<<" "<<r.y<<"\n";
        }

        else if(t=="INTERSECT"){
            int a,b,c,d;
            cin>>a>>b>>c>>d;

            P r;

            if(intersectSeg(p[a],p[b],p[c],p[d],r))
                cout<<"YES "<<r.x<<" "<<r.y<<"\n";
            else
                cout<<"NO\n";
        }
    }
}
