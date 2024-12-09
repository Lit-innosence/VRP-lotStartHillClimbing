#include <bits/stdc++.h>
using namespace std;
#include "variable.h"
#include "input.h"
#include "TSP.h"


int main(){
    input();
    cout << n << endl;
    quota.resize(n);
    i.resize(n);
    cout << quota.size() << endl;

    int seed = 10;
    /*
    cout << "初期解の乱数は？： "; cin >> seed;
    */
    tsp(seed,n);

    //初期解の列挙(デバッグ用)
    for(int i=0; i<n; i++){
        cout << quota.at(i) << endl;
    }

    return 0;
}