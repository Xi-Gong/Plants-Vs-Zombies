/**
 *Copyright (c) 2019 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.4.20
 *Emal: 2117610943@qq.com
 */

#ifndef SELECTPLANTSSCENE_H
#define SELECTPLANTSSCENE_H

#define SCROLLRIGHTFINISHED -1010
#define SCROLLLEFTFINISHED -220

#include <cocos-ext.h>
#include <cocos2d.h>

#include "Based/Runtime.h"
#include "SPSControlLayer.h"
#include "SPSSpriteLayer.h"

using namespace cocos2d;
using namespace cocos2d::extension;

class SelectPlantsScene : public Scene {
  public:
    SelectPlantsScene();
    ~SelectPlantsScene() = default;
    CREATE_FUNC(SelectPlantsScene);
    virtual bool init() override;

  protected:
    virtual void createReadyText(const std::string& name, const int& id);
    virtual void readyTextCallBack(Node* node, const std::string& name, const int& id);
    virtual void replaceScene();
    virtual void createBackgroundLayer();
    virtual void createControlLayer();
    virtual void eventUpdate(float Time);
    virtual void createSelectPlantsDialog();
    virtual void selectPlantsCallBack();

  protected:
    Runtime* _runtime;

    Layer* _scrollLayer;
    Director* _director;
    SPSControlLayer* _controlLayer;
    SPSSpriteLayer* _spriteLayer;
    extension::ScrollView* _scrollView;
};

#endif  // SELECTPLANTSSCENE_H
