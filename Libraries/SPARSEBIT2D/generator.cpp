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
    __seed__ = test * 67;
    NumGen.setSeed(__seed__);
    GrGen = GraphGen(NumGen);

    stringstream input;
    ///////////////////////////////////////
    int n = test <= 10 ? Rand(1000, 1000) : Rand(1e9, 1e9);
    int m = test <= 10 ? Rand(1000, 1000) : Rand(1e9, 1e9);
    int q = test <= 10 ? Rand(5, 1e3) : Rand(5e4, 8e4);
    if(test <= 5){
        n = m = 9;
        q = Rand(5, 10);
    }
    if(test == 16 || test == 17 || test == 18){
        n = 1e5;
        m = 1e9;
    }
    if(test >= 18) q = 2e5;

    int LIM = test <= 3 ? 9 : (test <= 8 ? 100 : (test <= 12 ? 1e5 : 1e9));
    if(test == 5){
        LIM = 1e9;
        q = 1e5;
    }
    if(test == 6){
        n = m = 10;
        LIM = 1e9;
        q = 100;
    }

    input << q << '\n';

    while(q--){
        int type = Rand(1, 2);
        if(q == 0 && type == 1){
            ++q;
            continue;
        }

        input << type << ' ';

        if(type == 1){
            int x = Rand(1, n), y = Rand(1, m), k = Rand(-LIM, LIM);
            input << x << ' ' << y << ' ' << k << '\n';
        }
        else{
            int x1 = Rand(1, n), y1 = Rand(1, m), x2 = Rand(x1, n), y2 = Rand(y1, m);
            input << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << '\n';
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
