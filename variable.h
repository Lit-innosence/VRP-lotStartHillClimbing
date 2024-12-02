// input.h
#ifndef VARIABLE_H
#define VARIABLE_H

#include <bits/stdc++.h>

using namesapce std;

int n;  // 顧客数
int q;  // トラックの積載量
vector<int> coord_x, coord_y;   // 顧客のx座標，y座標
vector<int> luggage;            // 顧客の荷物量

vector<vector<int>> route;   // トラックの配送経路
int cost;

#endif // VARIABLE_H