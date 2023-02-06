/**
 *Copyright (c) 2019 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.4.20
 *Emal: 2117610943@qq.com
 */

#ifndef GSBACKGROUNDLAYER_H
#define GSBACKGROUNDLAYER_H

#include <cocos2d.h>

#include "Scenes/SelectPlantsScene/SPSBackgroundLayer.h"

using namespace cocos2d;

class GSBackgroundLayer : public SPSBackgroundLayer {
  public:
    GSBackgroundLayer();
    ~GSBackgroundLayer() = default;
    virtual bool init() override;
    CREATE_FUNC(GSBackgroundLayer);

    static void backgroundRunAction();
    void addLayer(Node* node, const int order, const string& name) {
        node->addChild(this, order, name);
    }

  private:
    void setBackgroundImagePosition();

  private:
    Runtime* _runtime;
};

#endif  // GSBACKGROUNDLAYER_H
