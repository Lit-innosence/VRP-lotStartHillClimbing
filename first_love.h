#pragma once

#include <bits/stdc++.h>
#include <random>
#include "variable.h"
using namespace std;

using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vector<int>>;

vi random_permulation(int n, int seed){
    vi number(n+9);
    vi permu(n+9);
    vb appear_judge(n+9); //0,...,n-1をインデックスiとして，appear_judge.at(i)は既に登場したかどうかを判定する
    vi seisuu(n+9);

    mt19937 generator(seed); //メルセンヌツイスターで乱数生成

    for(int i=1; i<=n; i++){
        appear_judge.at(i) = false;
        seisuu.at(i) = i;
    }

    for(int i=1; i<=n; i++){
        uniform_int_distribution<int> distribution(1,n-i+1);
        int val = distribution(generator);
        //cout << "i: " << i << ", val: " << val << endl;
        number.at(i) = val;
    }
    for(int i=1; i<=n; i++){
        while(appear_judge.at(number.at(i))){ //number.at(i)番目の値が既に登場している場合
            number.at(i)++;
            //cout << "i: " << i << ", number.at(i): " << number.at(i) << endl;
        } 
        permu.at(i) = seisuu.at(number.at(i));
        appear_judge.at(number.at(i)) = true;
    }

    return permu;
}

vvi rand_first_solver(int n, int seed){
    vi rp = random_permulation(n,seed);
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