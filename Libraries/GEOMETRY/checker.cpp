#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
 
bool isDoubleEqual(double a, double b){
    return fabs(a - b) <= 1e-6 + 1e-9;
}
 
int main(int argc, char* argv[]){
    registerTestlibCmd(argc, argv);
 
    int n = inf.readInt();
    int q = inf.readInt();
 
    for(int i = 0; i < n; i++){
        inf.readDouble();
        inf.readDouble();
    }
 
    for(int i = 1; i <= q; i++){
        string type = inf.readToken();
 
        if(type=="ADD"||type=="EQUAL"||type=="DOT"||type=="CROSS"||type=="DIST"){
            inf.readInt(); inf.readInt();
        }
        else if(type=="SCALE"){
            inf.readInt(); inf.readDouble();
        }
        else if(type=="CCW"||type=="ONSEG"||type=="DISTSEG"||type=="PROJECT"||type=="REFLECT"){
            inf.readInt(); inf.readInt(); inf.readInt();
        }
        else if(type=="INTERSECT"){
            inf.readInt(); inf.readInt(); inf.readInt(); inf.readInt();
        }
 
        /* YES / NO queries */
 
        if(type=="EQUAL" || type=="ONSEG"){
            string a = ans.readToken();
            string o = ouf.readToken();
 
            if(a != o){
                quitf(_wa,
                      "Query %d (%s): expected %s, got %s",
                      i, type.c_str(), a.c_str(), o.c_str());
            }
        }
 
        /* INTERSECTION */
 
        else if(type=="INTERSECT"){
            string a = ans.readToken();
            string o = ouf.readToken();
 
            if(a != o){
                quitf(_wa,
                      "Query %d (%s): expected %s, got %s",
                      i, type.c_str(), a.c_str(), o.c_str());
            }
 
            if(a=="YES"){
                double ax = ans.readDouble();
                double ay = ans.readDouble();
                double ox = ouf.readDouble();
                double oy = ouf.readDouble();
 
                if(!isDoubleEqual(ax,ox) || !isDoubleEqual(ay,oy)){
                    quitf(_wa,
                        "Query %d (%s): expected (%.12f %.12f), got (%.12f %.12f)",
                        i, type.c_str(), ax, ay, ox, oy);
                }
            }
        }
 
        /* CCW */
 
        else if(type=="CCW"){
            int a = ans.readInt();
            int o = ouf.readInt();
 
            if(a != o){
                quitf(_wa,
                      "Query %d (%s): expected %d, got %d",
                      i, type.c_str(), a, o);
            }
        }
 
        /* single numeric answer */
 
        else if(type=="DOT" || type=="CROSS" || type=="DIST" || type=="DISTSEG"){
            double a = ans.readDouble();
            double o = ouf.readDouble();
 
            if(!isDoubleEqual(a,o)){
                quitf(_wa,
                      "Query %d (%s): expected %.12f, got %.12f",
                      i, type.c_str(), a, o);
            }
        }
 
        /* point answer */
 
        else if(type=="ADD" || type=="SCALE" || type=="PROJECT" || type=="REFLECT"){
            double ax = ans.readDouble();
            double ay = ans.readDouble();
            double ox = ouf.readDouble();
            double oy = ouf.readDouble();
 
            if(!isDoubleEqual(ax,ox) || !isDoubleEqual(ay,oy)){
                quitf(_wa,
                      "Query %d (%s): expected (%.12f %.12f), got (%.12f %.12f)",
                      i, type.c_str(), ax, ay, ox, oy);
            }
        }
    }
 
    quitf(_ok, "%d queries checked", q);
}
