/**
 *Copyright (c) 2023 Xi-Gong.All Right Reserved
 *Author : Xi-Gong
 *Date: 2023.02.05
 *Email: xi_gong@foxmail.com
 */

#ifndef RUNTIME_H
#define RUNTIME_H

#include <memory.h>

#include "GameData/GameData.h"
#include "UserData/UserData.h"

#define GAME_FONT_NAME_1 "resources/fonts/GameFont.ttf"
#define GAME_FONT_NAME_2 "resources/fonts/arial.ttf"

class Runtime {
  public:
    Runtime();
    ~Runtime();
    static Runtime* getInstance();

    void checkAnimationInterval();
    void resumeProhibit();

  public:
    int prohibitId;
    std::shared_ptr<GameData> gameData;
    std::shared_ptr<UserData> userData;

  private:
    static Runtime* _instance;
    int _frequence;
    float _sumAnimationInterval;
};

#endif  // RUNTIME_H
