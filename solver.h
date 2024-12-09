#include <bits/stdc++.h>
#include "variable.h"
#include "TSP.h"
#include "timemanager.h"
using namespace std;

struct Solver {

    // 初期解を生成する
    void solve_first() {
        tsp(100, n);
    }

    void annealingWithTimeThreshold(const int64_t time_threshold,
                                    const double start_temp,
                                    const double end_temp) {
        // 時間計測開始
        auto time_manager = TimeManager(time_threshold);

        // 初期解を生成
        this->solve_first();

        for (;;) {

            // 制限時間の確認
            time_manager.setNowTime();
            if (time_manager.isTimeOver()) {
                break;
            }

            // 焼きなましの温度と遷移の閾値を設定する 調整可
            double temp = start_temp + (end_temp - start_temp) * (time_manager.getNowTime() / time_threshold);

            // TODO 近傍から1つ選んでスコアを計算

            // TODO 近傍に遷移する
        }
    }
};