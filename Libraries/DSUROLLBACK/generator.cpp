#include<bits/stdc++.h>
#include "config/lib.h"
using namespace std;
using namespace RandomGen;
using namespace File;

#define int long long

NumberGen NumGen;
StringGen StrGen;
VectorGen VecGen;
int test = -1;

#define Rand(l, r) NumGen.Rand<long long>((l), (r))

void generate_test(){
    NumGen.setSeed(test);
    stringstream input;
    ///////////////////////////////////////
    int n = test <= 10 ? Rand(1, 1000) : Rand(1, 1e5);
    int q = test <= 10 ? Rand(1, 1000) : Rand(1, 1e5);
    if(test <= 8) n = Rand(1, 5), q = Rand(1, 5);
    if(test == 20) n = q = 100000;

    input << n << " " << q << '\n';

    int LIM = test <= 6 ? 5 : 1e6;

    for (int i = 1; i <= n; i++) {
        long long ai = Rand(-LIM, LIM);
        input << ai << (i == n ? '\n' : ' ');
    }

    while (q--) {
        int type = Rand(1, 4);
        int l = Rand(1, n);
        int r = Rand(l, n);

        if (type == 1) {
            int k = Rand(1, r - l + 5);
            input << "1 " << l << " " << r << " " << k << '\n';
        }
        else if (type == 2) {
            long long x = Rand(-LIM, LIM);
            input << "2 " << l << " " << r << " " << x << '\n';
        }
        else if (type == 3) {
            long long x = Rand(-LIM, LIM);
            input << "3 " << l << " " << r << " " << x << '\n';
        }
        else {
            long long x = Rand(-LIM, LIM);
            input << "4 " << l << " " << r << " " << x << '\n';
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
