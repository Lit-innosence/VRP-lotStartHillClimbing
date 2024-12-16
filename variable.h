//variable.h
#ifndef VARIABLE_H
#define VARIABLE_H

#include <bits/stdc++.h>

using namespace std;

extern int n;  // 顧客数
extern int q;  // トラックの積載量
extern vector<int> coord_x, coord_y;   // 顧客のx座標，y座標
extern vector<int> luggage;            // 顧客の荷物量

extern vector<vector<int>> route;   // トラックの配送経路
extern int cost;
extern int seed; // シード値

#endif // VARIABLE_H