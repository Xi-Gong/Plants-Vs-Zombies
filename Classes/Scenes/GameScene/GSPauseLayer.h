/**
 *Copyright (c) 2019 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.4.20
 *Emal: 2117610943@qq.com
 */

#ifndef GSPAUSELAYER_H
#define GSPAUSELAYER_H

#include <cocos2d.h>
#include <spine/spine-cocos2dx.h>
#include <ui/CocosGUI.h>

#include "Based/Runtime.h"

using namespace cocos2d;
using namespace spine;
using namespace cocos2d::ui;

class GSPauseLayer : public LayerColor {
  public:
    GSPauseLayer();
    ~GSPauseLayer() = default;
    virtual bool init() override;

    CREATE_FUNC(GSPauseLayer);
    static Layer* addLayer();

  private:
    void createShieldLayer();
    void createDialog();
    void showAniamtions();
    void showButton();

  private:
    Runtime* _runtime;

    Scale9Sprite* _levelObjectives;
};

#endif  // GSPAUSELAYER_H
