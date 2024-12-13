#include<bits/stdc++.h>
using namespace std;

#include "variable.h"

#pragma once

constexpr int alpha = 100; // 目的関数のペナルティ

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

    for (int i=1; i<(int)track.size()-1; i++) {
        int min_dist = INT_MAX;
        int min_dist_pos = i;
        for (int j=0; j<(int)track.size(); j++) {
            if (i==j) continue;
            int dx = calc_dist(coord_x[track[i]],
                               coord_y[track[i]],
                               coord_x[track[j]],
                               coord_y[track[j]]);
            if (min_dist < dx) {
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
int f() {
    int sum = 0;

    // 各トラックについて
    for (int i=0; i<route.size(); i++) {

        // トラックが回る顧客数
        int n = route[i].size() - 2;

        // 顧客数が少ない場合、全列挙して最小値を求める
        if (n < 15) {
            int p_sum = INT_MAX;
            vector<int> a(n);
            iota(a.begin(), a.end(), 1);
            do {
                int s = 0;
                for (int j=0; j<n; j++) {
                    s += calc_dist(coord_x[route[i][a[j]]],
                                   coord_y[route[i][a[j]]],
                                   coord_x[route[i][a[j+1]]],
                                   coord_y[route[i][a[j+1]]]);
                }
                p_sum = min(p_sum, s);
            } while (next_permutation(a.begin(), a.end()));

            // トラックの積載量を計算
            int l_sum = 0;
            for (int j=0; j<n; j++) {
                l_sum += luggage[route[i][j]];
            }

            // 積載量が多すぎたらペナルティを課す
            p_sum += alpha * max(0, l_sum - q);

            sum += p_sum;
        } else {
            // TSPの貪欲解を求める
            auto track = greedyTSP(route[i]);

            // 移動距離を求める
            int p_sum = 0;
            for (int i=0; i<track.size()-1; i++) {
                p_sum += calc_dist(coord_x[track[i]], coord_y[track[i]], coord_x[track[i+1]], coord_y[track[i+1]]);
            }

            // トラックの積載量を計算
            int l_sum = 0;
            for (int j=0; j<n; j++) {
                l_sum += luggage[route[i][j]];
            }

            // 積載量が多すぎたらペナルティを課す
            p_sum += alpha * max(0, l_sum - q);

            sum += p_sum;
        }
    }

    return sum;
}