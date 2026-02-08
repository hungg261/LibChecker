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
    int n = test <= 10 ? Rand(30, 100) : Rand(1, 1e4);
    if(test <= 3){
        n = 10;
    }
    else if(test <= 5){
        n = 25;
    }
    if(test >= 12) n = 1e4;

    int k = test >= 16 ? Rand(1, min(n, 100LL)) : Rand(2, min({n, (n + 5) / 2, 100LL}));
    if(test == 13) k = 1;
    if(test == 14 || test == 15) k = Rand(2, 10);
    if(test >= 18) k = min(n, 100LL);

    int LIM = test <= 3 ? 9 : (test <= 8 ? 100 : 1e3);

    input << n << ' ' << k << '\n';
    for(int i = 1; i <= n; ++i){
        if(test == 16) input << LIM << ' ';
        else if(test == 17) input << Rand(LIM - 2, LIM) << ' ';
        else if(test == 18) input << Rand(LIM - 1, LIM) << ' ';
        else input << Rand(1, LIM) << ' ';
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
