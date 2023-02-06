/**
 *Copyright (c) 2019 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.4.20
 *Emal: 2117610943@qq.com
 */

#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <cocos2d.h>
#include <spine/spine-cocos2dx.h>
#include <spine/spine.h>

#include "Based/Runtime.h"
#include "Scenes/SelectPlantsScene/SelectPlantsScene.h"

using namespace cocos2d;
using namespace spine;

class GameScene : public SelectPlantsScene {
  public:
    GameScene();
    ~GameScene();
    virtual bool init() override;
    CREATE_FUNC(GameScene);

  protected:
    virtual void controlPlayMusic();
    virtual void backgroundLayer();
    virtual void buttonLayer();
    virtual void informationLayer();
    virtual void controlLayer();
    virtual void animationLayer();
    virtual void pauseGame();

  private:
    Runtime* _runtime;
    Director* _director;
};

#endif  // GAMESCENE_H
