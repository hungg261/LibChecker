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
    int n = test <= 10 ? Rand(3, 1000) : Rand(5, 1e5);
    int q = test <= 10 ? Rand(3, 1000) : Rand(9e4, 1e5);
    if(test <= 8) n = Rand(3, 10), q = Rand(5, 10);
    if(test >= 15) n = q = 100000;

    int LIM = test <= 3 ? 5 : (test <= 10 ? 1e3 : 1e9);

    input << n << ' ' << q << '\n';
    for(int i = 1; i <= n; ++i)
        input << Rand(-LIM, LIM) << ' ';
    input << '\n';

    while(q--){
        int type = Rand(1, 4), l = Rand(1, n), r = Rand(l, n);
        if(q == 0 && type == 1){
            ++q;
            continue;
        }

        input << type << ' ' << l << ' ' << r;
        if(type == 1) input << ' ' << Rand(-LIM, LIM);

        input << '\n';
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
