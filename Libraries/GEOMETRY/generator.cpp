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
#define RandR(l, r) round(NumGen.Rand<double>((l), (r)) * 1000000.0) / 1000000.0;

void generate_test(){
    __seed__ = test * 67;
    NumGen.setSeed(__seed__);
    GrGen = GraphGen(NumGen);

    stringstream input;
    ///////////////////////////////////////

    int n, q;
    int LIM_L, LIM_R;
    if(test <= 3){
        n = 10; q = 20;
        LIM_L = -10; LIM_R = 10;
    }
    else if(test <= 5){
        n = 10; q = 20;
        LIM_L = -20; LIM_R = 20;
    }
    else if(test <= 8){
        n = 50; q = 100;
        LIM_L = -50; LIM_R = 50;
    }
    else if(test <= 10){
        n = 5000; q = 5000;
        LIM_L = -1e3; LIM_R = 1e3;
    }
    else if(test <= 15){
        n = 1e4; q = 1e4;
        LIM_L = -1e6; LIM_R = 1e6;
    }
    else if(test <= 18){
        n = 5e4; q = 1e5;
        LIM_L = -1e6; LIM_R = 1e6;
    }
    else{
        n = 1e5; q = 1e5;
        LIM_L = -1e6; LIM_R = 1e6;
    }

    if(test == 4 || test == 10 || test == 11 || test == 19){
        LIM_R = 1e6;
        LIM_L = LIM_R - (1e-6);
    }

    input << fixed << setprecision(6);

    input << n << ' ' << q << '\n';

    vector<pair<double, double>> pts(n + 1);
    map<pair<double, double>, vector<int>> mpIdx;
    for(int i = 1; i <= n; ++i){
        if(i > 1 && Rand(1, 5) == 1) pts[i] = pts[Rand(1, i - 1)];
        else{
            pts[i].first = RandR(LIM_L, LIM_R);
            pts[i].second = RandR(LIM_L, LIM_R);
        }

        mpIdx[pts[i]].push_back(i);

        input << pts[i].first << ' ' << pts[i].second << '\n';
    }

    vector<string> types = {
        "ADD","SCALE","EQUAL","DOT","CROSS","CCW",
        "DIST","ONSEG","DISTSEG","PROJECT","REFLECT","INTERSECT"
    };

    auto same = [&](int a, int b){
        return fabs(pts[a].first - pts[b].first) < 1e-9 &&
               fabs(pts[a].second - pts[b].second) < 1e-9;
    };

    while(q--){
        string type;

        if(test != 1 && test != 10 && test != 18)
            type = types[q % (int)types.size()];
        else type = types[Rand(0, (int)types.size()-1)];


        if(type == "ADD" || type == "EQUAL" || type == "DOT" ||
           type == "CROSS" || type == "DIST"){
            int i, j;
            if((type == "EQUAL" || type == "DIST" || type == "CROSS") && Rand(1, 3) == 1){
                i = Rand(1, n);
                const vector<int>& vec = mpIdx[pts[i]];

                if((int)vec.size() == 1){
                    ++q;
                    continue;
                }

                do{ j = vec[Rand(0, (int)vec.size() - 1)]; } while(i == j);

            }
            else{
                i = Rand(1, n);
                j = Rand(1, n);
            }


            input << type << ' ' << i << ' ' << j << '\n';
        }

        else if(type == "SCALE"){
            int i = Rand(1,n);
            double k = RandR(-10,10);
            input << type << ' ' << i << ' ' << k << '\n';
        }

        else if(type == "CCW"){
            int a = Rand(1,n);
            int b = Rand(1,n);
            int c = Rand(1,n);
            input << type << ' ' << a << ' ' << b << ' ' << c << '\n';
        }

        else if(type == "ONSEG" || type == "DISTSEG" ||
                type == "PROJECT" || type == "REFLECT"){
            int p = Rand(1,n);
            int a = Rand(1,n);
            int b = Rand(1,n);
            while(same(a,b)) b = Rand(1,n);

            input << type << ' ' << p << ' ' << a << ' ' << b << '\n';
        }

        else if(type == "INTERSECT"){
            int a = Rand(1,n);
            int b = Rand(1,n);
            int c = Rand(1,n);
            int d = Rand(1,n);

            while(same(a,b)) b = Rand(1,n);
            while(same(c,d)) d = Rand(1,n);

            input << type << ' ' << a << ' ' << b << ' ' << c << ' ' << d << '\n';
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
