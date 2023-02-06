/**
 *Copyright (c) 2019 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.4.20
 *Emal: 2117610943@qq.com
 */

#ifndef GSGAMEENDLAYER_H
#define GSGAMEENDLAYER_H

#include <cocos2d.h>
#include <ui/CocosGUI.h>

#include "Based/GameData/LevelDataHandler.h"
#include "Based/Runtime.h"
#include "Based/UserData/UserDataHandler.h"
#include "Based/UserWinRequireMent.h"

using namespace cocos2d;
using namespace cocos2d::ui;

enum class GameTypes;

class GSGameEndLayer : public LayerColor {
  public:
    GSGameEndLayer();
    ~GSGameEndLayer();
    bool init() override;

    CREATE_FUNC(GSGameEndLayer);
    void successfullEntry();
    void breakThrough(GameTypes gameType);

  private:
    void createShieldLayer();
    void showFailDialog(GameTypes gameType);
    void showFailText();
    void caveLevelNumber();
    void carsToCoins();
    void rewardCoin(Button* button);
    void coinAction(const Vec2& position, const int id, const bool big = false);
    void rewardThing();
    void quitScene();

  private:
    Runtime* _runtime;
    UserWinRequirement* _userWinRequirement;
    LevelDataHandler* _levelDataHandler;
    UserDataHandler* _userDataHandler;
};

#endif  // GSGAMEENDLAYER_H
