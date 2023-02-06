/**
 *Copyright (c) 2019 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.4.20
 *Emal: 2117610943@qq.com
 */

#ifndef SPSCONTROLLAYER_H
#define SPSCONTROLLAYER_H

#include <cocos2d.h>

#include "Based/Runtime.h"

using namespace cocos2d;

class SPSControlLayer : public Layer {
  public:
    SPSControlLayer();
    virtual ~SPSControlLayer() = default;
    CREATE_FUNC(SPSControlLayer);
    virtual bool init() override;

  private:
    void createButton();
    void showUserName();
    void createDialog();

  private:
    Runtime* _runtime;
};

#endif  // SPSCONTROLLAYER_H
