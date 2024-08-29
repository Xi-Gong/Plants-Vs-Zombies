/**
 *Copyright (c) 2019 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.4.20
 *Emal: 2117610943@qq.com
 */

#include "GSGameResultJudgement.h"

#include "GSBackgroundLayer.h"
#include "Scenes/GameScene/GSData.h"
#include "Zombies/Zombies.h"

GSGameResultJudgement::GSGameResultJudgement() :
    _levelDataHandler(LevelDataHandler::getInstance()) {
    _levelData = _levelDataHandler->readLevelData(_levelDataHandler->getLevelNumber());
}

bool GSGameResultJudgement::getZombieIsInHouse() {
    return (*_zombie)->getZombieAnimation()->getPositionX() < _levelData->userLose ? true : false;
}

GameTypes GSGameResultJudgement::judgeUserIsLose(list<Zombies*>::iterator& zombie) {
    _zombie = zombie;

    if ((*_zombie)->getZombieIsSurvive() && getZombieIsInHouse()) /* 僵尸存活 && 僵尸进入房间*/
    {
        if (getZombieIsInHouse()) {
            return GameTypes::UserLose;
        }
    }
    return GameTypes::None;
}
