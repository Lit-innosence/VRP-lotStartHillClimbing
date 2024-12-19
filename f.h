#include<bits/stdc++.h>
using namespace std;

#include "variable.h"

#pragma once

// 座標間の距離を求める関数
int calc_dist(int x, int y, int z, int w) {
    int dx = x - z;
    int dy = y - w;
    return round(sqrt(dx*dx+dy*dy));
}

// TSPの貪欲解を求める
vector<int> greedyTSP(vector<int> track) {
    vector<int> res; // 解
    res.push_back(0);

    for (int i=0; i<(int)track.size()-1; i++) {
        int min_dist = INT_MAX;
        int min_dist_pos = i;
        for (int j=1; j<(int)track.size()-1; j++) {
            if (i==j) continue;
            int dx = calc_dist(coord_x[track[i]],
                               coord_y[track[i]],
                               coord_x[track[j]],
                               coord_y[track[j]]);
            if (min_dist > dx) {
                min_dist_pos = j;
                min_dist = dx;
            }
        }
        res.push_back(min_dist_pos);
    }
    res.push_back(0);

    assert(res.size() != track.size());

    return res;
}

// 目的関数f
int f(vector<vector<int>> path, int alpha) {
    int sum = 0;

    // 各トラックについて
    for (int i=0; i<path.size(); i++) {

        // トラックが回る顧客数
        int m = path[i].size() - 2;

        // 顧客数が少ない場合、全列挙して最小値を求める
        if (m == 0) continue;
        if (m < 11) {
            // cout << "all" << endl;
            int p_sum = INT_MAX;
            vector<int> a(m);
            iota(a.begin(), a.end(), 1);
            do {
                int s = 0;
                s += calc_dist(coord_x[0], coord_y[0], coord_x[path[i][a[0]]], coord_y[path[i][a[0]]]);
                for (int j=0; j<m-1; j++) {
                    assert(a[j]<path[i].size() and a[j+1]<path[i].size());
                    s += calc_dist(coord_x[path[i][a[j]]],
                                   coord_y[path[i][a[j]]],
                                   coord_x[path[i][a[j+1]]],
                                   coord_y[path[i][a[j+1]]]);
                }
                s += calc_dist(coord_x[0], coord_y[0], coord_x[path[i][a[m-1]]], coord_y[path[i][a[m-1]]]);
                p_sum = min(p_sum, s);
            } while (next_permutation(a.begin(), a.end()));

            // トラックの積載量を計算
            int l_sum = 0;
            for (int j=0; j<path[i].size(); j++) {
                l_sum += luggage[path[i][j]];
            }

            // 積載量が多すぎたらペナルティを課す
            p_sum += alpha * max(0, l_sum - q);

            sum += p_sum;
        } else {
            // cout << "greedy" << endl;
            // TSPの貪欲解を求める
            auto track = greedyTSP(path[i]);

            // 移動距離を求める
            int p_sum = 0;
            for (int i=0; i<track.size()-1; i++) {
                p_sum += calc_dist(coord_x[track[i]], coord_y[track[i]], coord_x[track[i+1]], coord_y[track[i+1]]);
            }

            // トラックの積載量を計算
            int l_sum = 0;
            for (int j=0; j<track.size(); j++) {
                l_sum += luggage[path[i][j]];
            }

            // 積載量が多すぎたらペナルティを課す
            p_sum += alpha * max(0, l_sum - q);

            sum += p_sum;
        }
    }

    return sum;
}