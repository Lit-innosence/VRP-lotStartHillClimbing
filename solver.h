#include <bits/stdc++.h>
#include "variable.h"
#include "TSP.h"
#include "first_love.h"
#include "timemanager.h"
#include "f.h"
using namespace std;

#pragma once

class Random {
public:
    std::mt19937 mt_;

    uniform_real_distribution<double> dd_{0, 1.0};

    Random(const int seed = 0) : mt_(std::mt19937(seed)) {}

    inline int nextInt(const int m) {
        uniform_int_distribution<int> di(0, m-1);
        return di(mt_);
    }

    inline double nextDouble() { return dd_(mt_); }

    inline double nextLog() { return log(dd_(mt_)); }
};

Random rnd{};

struct Solver {

    // 初期解を生成する
    void solve_first(int seed) {
        route = tsp(seed);
    }

    void annealingWithTimeThreshold(const int64_t time_threshold,
                                    const double start_temp,
                                    const double end_temp) {
        // 時間計測開始
        auto time_manager = TimeManager(time_threshold);

        // 初期解を生成
        // this->solve_first();

        int cnt = 0;
        for (;;) {
            // cout << cnt++ << endl;

            // 制限時間の確認
            time_manager.setNowTime();
            if (time_manager.isTimeOver()) {
                break;
            }

            // 焼きなましの温度と遷移の閾値を設定する 調整可
            double temp = start_temp + (end_temp - start_temp) * (time_manager.getNowTime() / time_threshold);

            /* 近傍から1つ選んでスコアを計算 */

            // 顧客を一人選ぶ
            // cout << "choose" << endl;
            auto next_route = route;
            int now_score = f(route, 100);

            if (rnd.nextDouble() > 0.5) {
                int track = rnd.nextInt(route.size());
                int costomer_n = rnd.nextInt(route[track].size() - 2) + 1;
                int costomer = route[track][costomer_n];
                int new_track = rnd.nextInt(route.size());

                next_route[track].erase(next_route[track].begin() + costomer_n);
                next_route[new_track].pop_back();
                next_route[new_track].push_back(costomer);
                next_route[new_track].push_back(0);
            } else {
                int first_track = rnd.nextInt(route.size());
                int second_track = rnd.nextInt(route.size());
                if (first_track != second_track) {
                    int first_costomer_n = rnd.nextInt(route[first_track].size() - 2) + 1;
                    int second_costomer_n = rnd.nextInt(route[second_track].size() - 2) + 1;
                    int costomer_tmp = route[first_track][first_costomer_n];

                    next_route[first_track].erase(next_route[first_track].begin() + first_costomer_n);
                    next_route[first_track].pop_back();
                    next_route[first_track].push_back(route[second_track][second_costomer_n]);
                    next_route[first_track].push_back(0);

                    next_route[second_track].erase(next_route[second_track].begin() + second_costomer_n);
                    next_route[second_track].pop_back();
                    next_route[second_track].push_back(costomer_tmp);
                    next_route[second_track].push_back(0);
                }
            }


            /* 近傍に遷移する*/

            // cout << "calc" << endl;
            // 近傍のスコアを計算する
            int next_score = f(next_route, 100);
            int diff = next_score - now_score;

            // 遷移条件を満たしたら遷移する
             if (exp(-(diff / temp)) > rnd.nextDouble()) {
                route = next_route;
            }
        }

        cost = f(route, 5000);
    }

    void lotStartHillClimbing(const int64_t time_threshold,
                              const int64_t num_start) {
        // 時間計測開始
        auto time_manager = TimeManager(time_threshold);

        auto best_route = route;
        int best_score = f(best_route, 5000);

        int iter_time_threshold = time_threshold / num_start;

        for (int i=0; i<num_start; i++) {
            cout << i+1 << " iter start" << endl;

            auto time_manager_climb = TimeManager(iter_time_threshold);

            time_manager_climb.setNowTime();
            do {

                // 現在の解を記録
                auto next_route = route;
                int now_score = f(route, 100);
                // cout << "calc now score" << endl;

                // 近傍を決める
                if (rnd.nextDouble() > 0.5) {
                    // cout << "nearby-1" << endl;
                    int track = rnd.nextInt(next_route.size());

                    assert(track >= 0 and track < next_route.size());

                    /*
                    for (auto x : next_route[track]) {cout << x << " ";}
                    cout << endl;
                    */

                    if (next_route[track].size() != 2) {
                        int costomer_n = rnd.nextInt(next_route[track].size() - 2) + 1;

                        assert(costomer_n > 0 and costomer_n < next_route[track].size() - 1);

                        int costomer = next_route[track][costomer_n];
                        int new_track = rnd.nextInt(next_route.size());

                        /*
                        for (auto x : next_route[new_track]) {cout << x << " ";}
                        cout << endl;
                        */

                        next_route[track].erase(next_route[track].begin() + costomer_n);
                        next_route[new_track].pop_back();
                        next_route[new_track].push_back(costomer);
                        next_route[new_track].push_back(0);

                        /*
                        cout << "nearby-1 finish" << endl;
                        for (auto x : next_route[track]) {cout << x << " ";}
                        cout << endl;
                        for (auto x : next_route[new_track]) {cout << x << " ";}
                        cout << endl;
                        */
                    }
                } else {
                    // cout << "nearby-2" << endl;

                    int first_track = rnd.nextInt(next_route.size());
                    int second_track;

                    do {
                        second_track = rnd.nextInt(next_route.size());
                    } while (first_track == second_track);

                    assert(first_track >= 0 and first_track < next_route.size() and
                           second_track >= 0 and second_track < next_route.size());

                    /*
                    for (auto x : next_route[first_track]) {cout << x << " ";}
                    cout << endl;
                    for (auto x : next_route[second_track]) {cout << x << " ";}
                    cout << endl;
                    */

                    if (next_route[first_track].size() != 2 and
                        next_route[second_track].size() != 2) {

                        int first_costomer_n = rnd.nextInt(next_route[first_track].size() - 2) + 1;
                        int second_costomer_n = rnd.nextInt(next_route[second_track].size() - 2) + 1;

                        assert(first_costomer_n > 0 and first_costomer_n < next_route[first_track].size() -1);
                        assert(second_costomer_n > 0 and second_costomer_n < next_route[second_track].size() -1);

                        int costomer_tmp = next_route[first_track][first_costomer_n];

                        next_route[first_track].erase(next_route[first_track].begin() + first_costomer_n);
                        next_route[first_track].pop_back();
                        next_route[first_track].push_back(next_route[second_track][second_costomer_n]);
                        next_route[first_track].push_back(0);

                        next_route[second_track].erase(next_route[second_track].begin() + second_costomer_n);
                        next_route[second_track].pop_back();
                        next_route[second_track].push_back(costomer_tmp);
                        next_route[second_track].push_back(0);
                    }

                    /*
                    cout << "nearby-2 finish" << endl;
                    for (auto x : next_route[first_track]) {cout << x << " ";}
                    cout << endl;
                    for (auto x : next_route[second_track]) {cout << x << " ";}
                    cout << endl;
                    */
                }

                // cout << "detect nearby" << endl;

                // 近傍のスコアを計算
                int next_score = f(next_route, 100);
                int diff = next_score - now_score;

                // cout << "calc diff" << endl;

                // 最適値が更新されたら近傍に移る
                if (diff < 0) {
                    route = next_route;
                }

                // 時間を更新
                time_manager_climb.setNowTime();
            } while (!time_manager_climb.isTimeOver());

            // cout << "hill climb finish" << endl;

            // 新しい解のスコアを記録
            int new_score = f(route, 5000);

            // ベストスコアを更新する
            if (new_score < best_score) {
                best_route = route;
                best_score = new_score;
            }

            time_manager.setNowTime();
            if (time_manager.isTimeOver()) {
                cout << "Time Over!" << endl;
                break;
            }

            // 新たな初期解を生成
            this->solve_first(rnd.nextInt(10000));
            // cout << "next init created" << endl;
        }

        route = best_route;
        cost = f(route, 5000);
    }
};