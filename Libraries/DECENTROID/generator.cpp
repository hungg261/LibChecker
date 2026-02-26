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
    int n;
    if(test <= 5) n = Rand(3, 5);
    else if(test <= 7) n = Rand(5, 15);
    else if(test <= 10) n = Rand(50, 100);
    else if(test <= 13) n = Rand(1000, 5e4);
    else if(test <= 15) n = Rand(1e5, 2e5);
    else n = 2e5;

    if(test == 5) n = 10;
    if(test == 7) n = 15;
    if(test == 10) n = 100;
    if(test == 13) n = 1000;

    input << n << '\n';

    vector<pair<int32_t, int32_t>> edges;
    if(test == 5 || test == 7 || test == 10 || test == 13 || test == 16){
        for(int i = 1; i < n; ++i){
            edges.emplace_back(i, i + 1);
        }
    }
    else{
        edges = GrGen.randomTree(n);
    }

    shuffle(begin(edges), end(edges), NumGen.rng);

    for(const pair<int32_t, int32_t>& e: edges){
        input << e.first << ' ' << e.second << '\n';
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
