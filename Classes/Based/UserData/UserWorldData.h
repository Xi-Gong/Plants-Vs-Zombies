/**
 *Copyright (c) 2023 Xi-Gong.All Right Reserved
 *Author : Xi-Gong
 *Date: 2023.02.05
 *Email: xi_gong@foxmail.com
 */

#ifndef USERWORLDDATA_H
#define USERWORLDDATA_H

#include <cocos2d.h>

#include <vector>

#include "UserSelectCard.h"

struct UserWorldData {
    UserWorldData() :
        highestLevel(1), currentLevel(1), background(nullptr), mainToWorld(false),
        killZombiesNumbers(99999), sunNumbers(10000), coinNumbers(99999),
        isReadWoldInformation(false) {}
    ~UserWorldData() = default;

    int highestLevel;             // 目前通过最高的关卡数
    int currentLevel;             // 当前关卡数
    cocos2d::Sprite* background;  // 当前世界地图
    bool mainToWorld;             // 是否从主菜单切换到现代世界

    int killZombiesNumbers;
    int sunNumbers;
    int coinNumbers;
    std::vector<UserSelectCard> userSelectCard;  // 用户一次闯关所选植物

    bool isReadWoldInformation;
};

#endif  // USERWORLDDATA_H
