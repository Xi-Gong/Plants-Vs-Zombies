/**
 *Copyright (c) 2019 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.4.20
 *Emal: 2117610943@qq.com
 */

#ifndef GSGAMERESULTJUDGEMENT_H
#define GSGAMERESULTJUDGEMENT_H

#include <cocos2d.h>

#include <list>

#include "Based/GameData/LevelDataHandler.h"
#include "Based/GameTypes.h"

using namespace cocos2d;

using std::list;

class Zombies;

class GSGameResultJudgement {
  public:
    GSGameResultJudgement();
    ~GSGameResultJudgement() = default;

    GameTypes judgeUserIsLose(list<Zombies*>::iterator& zombie);

  private:
    bool getZombieIsInHouse();

  private:
    LevelData* _levelData;
    LevelDataHandler* _levelDataHandler;
    list<Zombies*>::iterator _zombie;
};

#endif  // GSGAMERESULTJUDGEMENT_H
