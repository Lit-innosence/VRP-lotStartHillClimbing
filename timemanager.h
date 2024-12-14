#pragma once

#include <bits/stdc++.h>
using namespace std;

class TimeManager
{
private:
    std::chrono::high_resolution_clock::time_point start_time_;
    double now_time_;
    double time_threshold_;

public:
    // コンストラクタ
    // 時間制限をmsで指定する
    TimeManager(const double time_threshold)
        : start_time_(std::chrono::high_resolution_clock::now()),
          time_threshold_(time_threshold) {}

    // 現在時間を格納する
    void setNowTime() {
        auto diff = std::chrono::high_resolution_clock::now() - this->start_time_;
        this->now_time_ =
            std::chrono::duration_cast<std::chrono::microseconds>(diff).count() *
            1e-3;
    }

    // 経過時間を取得する
    double getNowTime() const { return this->now_time_; }

    // インスタンス生成時から時間制限を超過したか判定する
    bool isTimeOver() const { return now_time_ >= time_threshold_; }
};