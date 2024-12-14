//TSP.h
#ifndef TSP_H
#define TSP_H

#include <bits/stdc++.h>
#include <random>
#include "variable.h"
#include "input.h"
using namespace std;

using vvi = vector<vector<int>>;

double distance(int p, int q){ //顧客p,q間の距離計算
    double x2 = (coord_x.at(p) - coord_x.at(q)) * (coord_x.at(p) - coord_x.at(q));
    double y2 = (coord_y.at(p) - coord_y.at(q)) * (coord_y.at(p) - coord_y.at(q));
    return sqrt(x2+y2);
}

vector<int> tsp(int seed, int n){ //乱数のシード値を引数とする
    vector<int> quota(n); //quota.at(i)は顧客iの割当トラックの番号(-1ならば未定)
    vector<int> i(n);
    //bool judge(n); //全顧客が割り当てられたらtrueとなる．

    //1. すべての顧客の割当トラックを未定として,t=1とする
    for(int p=0; p<n; p++) quota.at(p) = -1; //全顧客割り合て未定
    bool judge = false; //全ての顧客が割り当てられたらtrueになる
    int t = 1; //トラック番号を示す変数t

    while(!judge){ //全てのトラックが割り当てられたら終わり
        //2. 割当が未定の顧客i.at(0)をランダムに１人選び，トラックtに割り当てる．j=2とする
        mt19937 generator(seed); //メルセンヌツイスターで乱数生成
        uniform_int_distribution<int> distribution(0,n-1);
        int rand_val = distribution(generator);; //乱数値
        while(quota.at(rand_val)!=-1){
            rand_val = distribution(generator);
        } //割当未定の顧客となるまで乱数生成

        i.at(0) = rand_val;
        quota.at(i.at(0)) = t;
        int j = 1; //iのインデックスの変数    

        //3. まだトラックに割り当てられていない顧客の中からi_{j-1}との距離が最小の顧客をkとする．
        int sum;
        int k;
        do{
            sum = 0;
            double dist = 1e9;
            k = -1; //距離distが最小となる顧客k
            for(int s=0;s<n;s++){
                if(quota.at(s)!=-1) continue; //既に割り当てられていたら次のsへ
                if(distance(s,i.at(j-1)) < dist){
                    k = s;
                    dist = distance(s,i.at(j-1));
                }
            }

            //4. 顧客i_0,i_1,…,i_{j−1}にkを加えても，届ける荷物の重量の和がトラックの制限を超えないなら,i_j=kとして顧客をトラックtに割り当て,j=j+1として 3.へ戻る
            for(int b=0; b<=j-1; b++){
                sum += luggage.at(i.at(b));
            }
            if(sum+luggage.at(k) <= q){
                i.at(j) = k;
                quota.at(i.at(j)) = t;
                j++;
            }

        }while(sum+luggage.at(k) <= q);
        //5. 顧客全員にトラックが割り当てられたならば終了する，そうでなければt=t+1として2. に戻る．
        t++; //次のトラックへ

        judge = true;
        for(int p=0; p<n; p++){
            if(quota.at(p)==-1) judge = false;
        }
    }

    return quota;
}

vvi tsp_first_solver(int n, int seed){
    vi rp = tsp(n,seed);
    vvi solver;
    int t = 1;
    while(t <= n){
        vi track;
        track.push_back(0);

        int weight = 0;
        do{
            weight += luggage.at(rp.at(t));
            track.push_back(rp.at(t));
            t++;
            
        }while(t<=n && weight + luggage.at(rp.at(t)) <= q);
        track.push_back(0);
        solver.push_back(track);
    }
    
    return solver;
}

#endif //TSP.h