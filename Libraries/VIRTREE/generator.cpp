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
    int n = test <= 10 ? Rand(3, 1000) : Rand(5e4, 2e5);
    int q = test <= 10 ? Rand(3, 1000) : Rand(3, 2e5);
    if(test <= 8) n = Rand(3, 10), q = Rand(1, 5);
    if(test >= 12) n = 2e5, q = Rand(1, 1000);
    if(test >= 15) n = 2e5, q = Rand(1, 10000);

    if(test == 20) n = q = 2e5;
    if(test == 19) n = 2e5, q = 100;
    if(test == 18) n = 2e5, q = 5;
    if(test == 17) n = 2e5, q = n / 2;
    if(test == 16) n = 2e5, q = n / 2;

    input << n << " " << q << '\n';

    vector<int> deg(n + 1, 0);
    if(test == 1 || test == 15){
        for(int i = 1; i < n; ++i)
            input << i << ' ' << i + 1 << '\n';
    }
    else for(const auto& e: GrGen.randomTree(n)){
        input << e.first << ' ' << e.second << '\n';
        ++deg[e.first];
        ++deg[e.second];
    }

    vector<int> leaves;
    for(int i = 1; i <= n; ++i)
        if(deg[i] == 1) leaves.push_back(i);

    int left = 5e5;
    vector<int> perm(n);
    iota(begin(perm), end(perm), 1);

    vector<vector<int>> queries;

    while(q--){
        int k = 2;
        if(test == 18 && q == 4){
            k = n - 300;
        }
        else if(test == 16){
            k = 2;
            input << k << ' ';

            int a = Rand(0, (int)leaves.size() - 2), b = Rand(a + 1, (int)leaves.size() - 1);
            input << leaves[a] << ' ' << leaves[b] << '\n';
            continue;
        }
        else{
            int min_k = 2;
            int max_k = left - 2 * q;

            k = Rand(min_k, min(n, max_k));
            left -= k;
        }

        for (int i = 0; i < k; ++i) {
            int j = Rand(i, (int)perm.size() - 1);
            swap(perm[i], perm[j]);
        }

        vector<int> qr;
        for(int i = 0; i < k; ++i)
            qr.push_back(perm[i]);

        queries.push_back(qr);
    }

    shuffle(begin(queries), end(queries), NumGen.rng);
    for(const auto& vec: queries){
        input << (vec.size()) << ' ';
        for(int ele: vec) input << ele << ' ';
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
