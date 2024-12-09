#include <bits/stdc++.h>
using namespace std;
#include "variable.h"
#include "input.h"
#include "TSP.h"
#include "first_love.h"

int n;  // 顧客数
int q;  // トラックの積載量
vector<int> coord_x, coord_y;   // 顧客のx座標，y座標
vector<int> luggage;            // 顧客の荷物量

vector<vector<int>> route;   // トラックの配送経路
int cost;

int main(){
    input();
    cout << n << endl;
    quota.resize(n);
    i.resize(n);
    cout << quota.size() << endl;

    int seed = 32467;
    /*
    cout << "初期解の乱数は？： "; cin >> seed;
    */
    vi p = random_permulation(n,seed);
    route = first_solver(n,seed);

    //初期解の列挙(デバッグ用)
    for(int i=1; i<=n; i++){
        cout << p.at(i) << " ";
    }
    cout << endl;

    for(int i=0;i<route.size();i++){
        for(int j=0;j<route.at(i).size();j++){
            cout << route.at(i).at(j) << " ";
        }
        cout << endl;
    }

    return 0;
}