#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-9;
int sgn(double x){ return (x > EPS) - (x < -EPS); }

struct P{
    double x,y;
    P(){} P(double x,double y):x(x),y(y){}
    P operator+(P o)const{return {x+o.x,y+o.y};}
    P operator-(P o)const{return {x-o.x,y-o.y};}
    P operator*(double k)const{return {x*k,y*k};}
    bool operator==(P o)const{return sgn(x-o.x)==0 && sgn(y-o.y)==0;}
};

double dot(P a,P b){ return a.x*b.x+a.y*b.y; }
double cross(P a,P b){ return a.x*b.y-a.y*b.x; }
double norm(P a){ return sqrt(dot(a,a)); }

int ccw(P a,P b,P c){
    return sgn(cross(b-a,c-a));
}

bool onSeg(P a,P b,P p){
    if(ccw(a,b,p)!=0) return false;
    return sgn(dot(p-a,p-b))<=0;
}

double dist(P a,P b){
    return norm(a-b);
}

double distSeg(P p,P a,P b){
    P ab=b-a, ap=p-a, bp=p-b;
    if(sgn(dot(ap,ab))<0) return norm(ap);
    if(sgn(dot(bp,ab))>0) return norm(bp);
    return fabs(cross(ab,ap))/norm(ab);
}

P project(P p,P a,P b){
    P ab=b-a;
    double t=dot(p-a,ab)/dot(ab,ab);
    return a+ab*t;
}

P reflect(P p,P a,P b){
    P q=project(p,a,b);
    return q*2-p;
}

bool intersect(P a,P b,P c,P d,P &out){
    P ab=b-a, cd=d-c;
    double den=cross(ab,cd);
    if(sgn(den)==0) return false;
    double t=cross(c-a,cd)/den;
    out=a+ab*t;
    return onSeg(a,b,out)&&onSeg(c,d,out);
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n,q;
    cin>>n>>q;

    vector<P> p(n+1);
    for(int i=1;i<=n;i++) cin>>p[i].x>>p[i].y;

    cout<<fixed<<setprecision(12);

    while(q--){
        string t; cin>>t;

        if(t=="ADD"){
            int i,j; cin>>i>>j;
            P r=p[i]+p[j];
            cout<<r.x<<" "<<r.y<<"\n";
        }
        else if(t=="SCALE"){
            int i; double k; cin>>i>>k;
            P r=p[i]*k;
            cout<<r.x<<" "<<r.y<<"\n";
        }
        else if(t=="EQUAL"){
            int i,j; cin>>i>>j;
            cout<<(p[i]==p[j]?"YES\n":"NO\n");
        }
        else if(t=="DOT"){
            int i,j; cin>>i>>j;
            cout<<dot(p[i],p[j])<<"\n";
        }
        else if(t=="CROSS"){
            int i,j; cin>>i>>j;
            cout<<cross(p[i],p[j])<<"\n";
        }
        else if(t=="CCW"){
            int a,b,c; cin>>a>>b>>c;
            cout<<ccw(p[a],p[b],p[c])<<"\n";
        }
        else if(t=="DIST"){
            int i,j; cin>>i>>j;
            cout<<dist(p[i],p[j])<<"\n";
        }
        else if(t=="ONSEG"){
            int i,a,b; cin>>i>>a>>b;
            cout<<(onSeg(p[a],p[b],p[i])?"YES\n":"NO\n");
        }
        else if(t=="DISTSEG"){
            int i,a,b; cin>>i>>a>>b;
            cout<<distSeg(p[i],p[a],p[b])<<"\n";
        }
        else if(t=="PROJECT"){
            int i,a,b; cin>>i>>a>>b;
            P r=project(p[i],p[a],p[b]);
            cout<<r.x<<" "<<r.y<<"\n";
        }
        else if(t=="REFLECT"){
            int i,a,b; cin>>i>>a>>b;
            P r=reflect(p[i],p[a],p[b]);
            cout<<r.x<<" "<<r.y<<"\n";
        }
        else if(t=="INTERSECT"){
            int a,b,c,d; cin>>a>>b>>c>>d;
            P r;
            if(intersect(p[a],p[b],p[c],p[d],r))
                cout<<"YES "<<r.x<<" "<<r.y<<"\n";
            else
                cout<<"NO\n";
        }
    }
}