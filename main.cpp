#include <bits/stdc++.h>
#include "variable.h"
#include "input.h"
//#include "TSP.h"
#include "first_love.h"

using namespace std;

int n;  // 顧客数
int q;  // トラックの積載量
vector<int> coord_x, coord_y;   // 顧客のx座標，y座標
vector<int> luggage;            // 顧客の荷物量

vector<vector<int>> route;   // トラックの配送経路
int cost;

int main(){
    input();
    cout << n << endl;

    int seed = 32467;
    /*
    cout << "初期解の乱数は？： "; cin >> seed;
    */

    //random_permutationで初期解生成
    vi p = random_permulation(n,seed);
    route = rand_first_solver(n,seed);

    //tspで初期解生成
    //vi p = tsp(n,seed);
    //route = tsp_first_solver(n,seed);

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