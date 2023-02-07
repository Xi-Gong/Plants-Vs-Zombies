/**
 *Copyright (c) 2023 Xi-Gong.All Right Reserved
 *Author : Xi-Gong
 *Date: 2023.02.05
 *Email: xi_gong@foxmail.com
 */

#ifndef LEVELDATA_H
#define LEVELDATA_H

#include <vector>

using std::vector;

struct LevelData {
    LevelData() : zombiesFrequency(0), rewardCoinNumbers(0), firstFrequencyTime(18), userLose(0) {}
    ~LevelData() = default;

    // number of zombie attacks
    int zombiesFrequency;

    int rewardCoinNumbers;

    // first zombie attack time
    int firstFrequencyTime;

    float userLose; /* 玩家失败 */

    vector<int> zombiesType;
    vector<int> zombiesNumbers;

    // number of multiple zombie attacks
    vector<int> munchZombiesFrequency;

    // each type of zombie appear probability in every attack
    vector<vector<int> > zombiesTypeProbabilityFrequency;

    vector<int> gameType; /* 游戏类型 */
};

#endif  // LEVELDATA_H
