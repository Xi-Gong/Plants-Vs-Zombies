/**
 *Copyright (c) 2019 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.4.20
 *Emal: 2117610943@qq.com
 */

#ifndef PLANTSINFORMATION_H
#define PLANTSINFORMATION_H

#include <cocos2d.h>
#include <ui/CocosGUI.h>

using namespace cocos2d;
using namespace cocos2d::ui;

class PlantsInformation {
  public:
    struct PlantsCards {
        PlantsCards() : timeBarIsFinished(false) {}
        Button* plantsCards;          /* 卡牌 */
        Text* plantsCardText;         /* 卡牌文字 */
        ProgressTimer* progressTimer; /* 倒计时 */
        int plantsNeedSunNumbers;     /* 所需阳光 */
        int tag;                      /* 编号 */
        bool timeBarIsFinished;       /* 倒计时是否完成 */
    };

    /* 植物冷却时间 */
    float PlantsCoolTime[3] = {
        /*向日葵*/ 7.5f, /*豌豆射手    */ 7.5f, /*坚果    */ 30};
    /* 植物所需阳光 */
    int PlantsNeedSunNumbers[3] = {
        /*向日葵*/ 50, /*豌豆射手    */ 100, /*坚果    */ 50};

    /* 植物剩余冷却时间 */
    struct PlantsCardFileData {
        static float PlantsSurPlusCoolTime[3];
        static float PlantsSurPlusPrecent[3];
    };
};

#endif  // PLANTSINFORMATION_H
