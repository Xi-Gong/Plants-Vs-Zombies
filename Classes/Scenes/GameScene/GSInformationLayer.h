/**
 *Copyright (c) 2019 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.4.20
 *Emal: 2117610943@qq.com
 */

#ifndef GSINFORMATIONLAYER_H
#define GSINFORMATIONLAYER_H

#include <cocos2d.h>
#include <ui/CocosGUI.h>

#include "Based/GameData/LevelDataHandler.h"
#include "Based/Runtime.h"

using namespace cocos2d;
using namespace cocos2d::ui;

class GSInformationLayer : public Layer {
  public:
    GSInformationLayer();
    ~GSInformationLayer() = default;
    virtual bool init() override;
    CREATE_FUNC(GSInformationLayer);

    void addLayer(Node* node, const int order, const string& name) {
        node->addChild(this, order, name);
    }
    void updateZombiesDieNumbers();
    void updateCoinNumbers();
    void updateSunNumbers();
    void updateProgressBar(const int& zombiesAppearFrequency);
    void updateProgressBar(const int& zombiesAppearFrequency, const int& maxFrequency);
    bool updateProgressBarFlag();
    bool updateProgressBarFlag(const int& id);
    void updateProgressBarFinalFlag();
    void updateProgressBarHead();
    void sunNumberTextWarning();
    void createPromptText();
    void setProgressBarPercent(const float precent);
    float getProgressBarPercent() const;
    void setProgressBarLastPercent(const float precent);
    float getProgressBarLastPercent() const;

  private:
    void showUserText();
    void showProgressBar();
    void showZombiesDieNumbers();
    void showCoinNumbers();
    void showSunNumbers();
    void showPromptMuchZombiesText(const string& textName);

  private:
    Runtime* _runtime;  // 全局变量
    LevelDataHandler* _levelDataHandler;

    float _levelLastPrecent;      // 进度条上一次进度
    Text* _zombiesDieText;        // 僵尸死亡数文本
    Text* _coinNumbersText;       // 金币数文本
    Text* _sunNumbersText;        // 阳光数文本
    ProgressTimer* _progressBar;  // 进度条
};

#endif  // GSINFORMATIONLAYER_H
