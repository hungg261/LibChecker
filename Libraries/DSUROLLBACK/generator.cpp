#include<bits/stdc++.h>
#include "config/RandLib/RandLib.h"
#include "config/lib.h"
using namespace std;
using namespace RandLib;
using namespace File;

#define int long long

NumberGen NumGen;
StringGen StrGen;
VectorGen VecGen;
GraphGen GrGen;
int test = -1;

#define Rand(l, r) NumGen.Rand<long long>((l), (r))

void generate_test(){
    __seed__ = test * 69;
    NumGen.setSeed(__seed__);
    GrGen = GraphGen(NumGen);

    stringstream input;
    ///////////////////////////////////////
    int n = test <= 10 ? Rand(3, 1000) : Rand(1, 1e5);
    int q = test <= 10 ? Rand(3, 1000) : Rand(9e4, 1e5);
    if(test <= 8) n = Rand(3, 10), q = Rand(1, 10);
    if(test >= 13) n = q = 100000;
    if(test == 13) n = 10;
    if(test == 14) n = 100;

    int INF = test <= 6 ? 9 : (test <= 10 ? 1e5 : 1e9);
    input << n << ' ' << q << '\n';
    for (int i = 1; i <= n; i++) {
        long long ai = Rand(-INF, INF);
        input << ai << (i == n ? '\n' : ' ');
    }

    int alive_edges = 0;
    int prv = -1, prvw = -1;

    while (q--) {
        int type = Rand(0, 4);
        if(q == 0 && type <= 1){
            ++q;
            continue;
        }
        if(prv == 2 && type == 2){
            ++q;
            continue;
        }

        prv = type;

        if (type == 0) {
            int u = Rand(1, n);
            int v = Rand(1, n);
            input << "0 " << u << " " << v << '\n';
            alive_edges++;
        }
        else if (type == 1) {
            if (alive_edges == 0){
                ++q;
                continue;
            }
            input << "1\n";
            alive_edges--;

            prvw = -1;
        }
        else if (type == 2) {
            input << "2\n";

            prvw = -1;
        }
        else if (type == 3) {
            int u = Rand(1, n);
            if(prv == type && u == prvw){
                ++q;
                continue;
            }

            input << "3 " << u << '\n';

            prvw = u;
        }
        else {
            int u = Rand(1, n);
            if(prv == type && u == prvw){
                ++q;
                continue;
            }
            input << "4 " << u << '\n';

            prvw = u;
        }
    }

    ///////////////////////////////////////
    createFile("baitap.inp", input.str());
}

signed main(int32_t argc, char* argv[]){
    ios_base::sync_with_stdio(0); cin.tie(0);

    if (argc >= 3 && string(argv[1]) == "-test"){
        try{
            test = stoi(argv[2]);
        } catch (...){
            cerr << "Error: Invalid test number.\n";
            return -1;
        }
    } else{
        cerr << "Usage: generate.exe -test <number>\n";
        return -1;
    }

    generate_test();

    return 0;
}
