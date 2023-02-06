/**
 *Copyright (c) 2019 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.4.20
 *Emal: 2117610943@qq.com
 */

#ifndef GSBUTTONLAYER_H
#define GSBUTTONLAYER_H

#include <cocos2d.h>

#include "Based/GameData/LevelDataHandler.h"
#include "Plants/Plants.h"
#include "Plants/PlantsInformation.h"
#include "Scenes/SelectPlantsScene/SPSControlLayer.h"

using namespace cocos2d;
using namespace cocos2d::ui;

struct MouseSelectImage /* 鼠标选择的植物 */
{
    MouseSelectImage() : Iamge(nullptr), isSelectPlants(false), isSelectShovel(false) {}
    Sprite* Iamge;             /* 图片 */
    PlantsType selectPlantsId; /* 所选植物编号 */
    bool isSelectPlants;       /* 是否选择了植物 */
    bool isSelectShovel;       /* 是否选择了铲子 */
};

enum class GSLayerButton { stopButton = 1, accelerateButton, decelerateButton };

class GSButtonLayer : public SPSControlLayer {
  public:
    GSButtonLayer();
    ~GSButtonLayer();
    virtual bool init() override;
    CREATE_FUNC(GSButtonLayer);

    // 添加到主场景中
    void addLayer(Node* node, const int order, const string& name) {
        node->addChild(this, order, name);
    }

  private:
    Button* createButton(const string& normal, const string& select, const Vec2& position,
                         GSLayerButton buttonName, const bool isFlippedX = false);
    void createKeyBoardListener();
    void createQuitDialog();
    void controlAccelerateScheduler();
    void controlDecelerateScheduler();
    void showSeedBank();
    void showShovelBank();
    void createPlantsCard();
    ProgressTimer* createProgressTimer(Button* button, const float _time, const int from,
                                       const unsigned int& id);

  public:
    MouseSelectImage* mouseSelectImage;              // 鼠标选择
    PlantsInformation* plantsInformation;            // 植物属性
    PlantsInformation::PlantsCards plantsCards[20];  // 植物卡片

  private:
    Runtime* _runtime;  // 全局变量
    LevelDataHandler* _levelDataHandler;

    Director* _director;        // 导演单例
    Layer* _quitLayer;          // 退出屏蔽层
    Button* _accelerateButton;  // 加速按钮
    Button* _decelerateButton;  // 减速按钮
};

#endif  // GSBUTTONLAYER_H
