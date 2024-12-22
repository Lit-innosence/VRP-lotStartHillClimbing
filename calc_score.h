#include<bits/stdc++.h>
using namespace std;

#include "variable.h"
#include "f.h"

#pragma once

// スコア計算関数
int calc_score(vector<vector<int>> path, int alpha) {
    int sum = 0;

    // 各トラックについて
    for (int i=0; i<path.size(); i++) {

        // トラックが回る顧客数
        int m = path[i].size() - 2;

        // 全列挙して最小値を求める
        // cout << "all" << endl;
        int p_sum = INT_MAX;
        vector<int> best_perm;
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
            if (p_sum > s) {
                p_sum = s;
                best_perm = a;
            }
        } while (next_permutation(a.begin(), a.end()));

        // トラックの積載量を計算
        int l_sum = 0;
        for (int j=0; j<path[i].size(); j++) {
            l_sum += luggage[path[i][j]];
        }

        // 積載量が多すぎたらペナルティを課す
        p_sum += alpha * max(0, l_sum - q);

        sum += p_sum;
        for (int j=0; j<m; j++) {
            route[i][j+1] = path[i][best_perm[j]];
        }
    }

    return sum;
}