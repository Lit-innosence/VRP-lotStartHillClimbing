#include <bits/stdc++.h>
#include "variable.h"
#include "input.h"
#include "TSP.h"
//#include "first_love.h"
#include "f.h"
#include "solver.h"
#include "output.h"

using namespace std;

int n;  // 顧客数
int q = 100;  // トラックの積載量
vector<int> coord_x, coord_y;   // 顧客のx座標，y座標
vector<int> luggage;            // 顧客の荷物量

vector<vector<int>> route;   // トラックの配送経路
int cost;
int seed;

int main(){
    input();
    cout << n << endl;
    /*
    cout << "初期解の乱数は？： "; cin >> seed;
    */
    seed = 32467;

    /*//random_permutationで初期解生成
    vi p = random_permulation(n,seed);
    route = rand_first_solver(n,seed);*/

    //tspで初期解生成
    route = tsp(seed);

    //初期解の列挙(デバッグ用)
    /*for(int i=1; i<=n; i++){
        cout << p.at(i) << " ";
    }
    cout << endl;*/

    for(int i=0;i<route.size();i++){
        for(int j=0;j<route.at(i).size();j++){
            cout << route.at(i).at(j) << " ";
        }
        cout << endl;
    }

    cout << "最適値：" << f(route, 5000) << endl;

    Solver solver;

    // 焼きなまし
    // solver.annealingWithTimeThreshold(/*timte_threshold*/ 9950, /*start_temp*/ 150, /*end_temp*/ 0);

    // 山登り
    solver.lotStartHillClimbing(/*time_threshold*/ 9950, /*num_start*/ 100);

    /*
    // 解の列挙
    for (int i=0; i<route.size(); i++) {
        for (int j=0; j<route[i].size(); j++) {
            cout << route[i][j] << " ";
        }
        cout << endl;
    }

    cout << "最適値：" << f(route, 5000) << endl;
    */

    output();

    return 0;
}