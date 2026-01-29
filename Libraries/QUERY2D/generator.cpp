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
    int n = test <= 10 ? Rand(3, 1000) : Rand(500, 1000);
    int m = test <= 10 ? Rand(3, 1000) : Rand(500, 1000);
    int q = test <= 10 ? Rand(3, 1000) : Rand(1, 1e5);

    if (test <= 8) {
        n = Rand(3, 5);
        m = Rand(3, 5);
        q = Rand(5, 10);
    }

    if (test >= 18) {
        n = m = 1000;
        q = 100000;
    }
    if(test == 18) n = m = 100, q = 100000;

    int LIM = test <= 3 ? 5 : (test <= 10 ? 1e3 : (test <= 15 ? 1e6 : 1e9));

    input << n << ' ' << m << ' ' << q << '\n';

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            input << Rand(-LIM, LIM) << ' ';
        }
        input << '\n';
    }

    while (q--) {
        int type = Rand(1, 2);

        if (q == 0 && type == 1) {
            ++q;
            continue;
        }

        if (type == 1) {
            int x = Rand(1, n);
            int y = Rand(1, m);
            int k = Rand(-LIM, LIM);
            input << "1 " << x << ' ' << y << ' ' << k << '\n';
        } else {
            int x1 = Rand(1, n);
            int x2 = Rand(x1, n);
            int y1 = Rand(1, m);
            int y2 = Rand(y1, m);
            input << "2 " << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << '\n';
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
