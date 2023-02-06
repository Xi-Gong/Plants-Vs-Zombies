/**
 *Copyright (c) 2019 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.4.20
 *Emal: 2117610943@qq.com
 */

#ifndef SPSQUITLAYER_H
#define SPSQUITLAYER_H

#include <cocos2d.h>

#include "Scenes/GameScene/GSPauseQuitLayer.h"

using namespace cocos2d;

class SPSQuitLayer : public GSPauseQuitLayer {
  public:
    SPSQuitLayer() : _shieldListener(nullptr) {}
    ~SPSQuitLayer() = default;
    CREATE_FUNC(SPSQuitLayer);
    virtual bool init() override;

  protected:
    virtual void createButton(const Vec2& vec2, const std::string name,
                              PauseQuitLayer_Button type) override;

  private:
    void createDialog() override;

  private:
    EventListenerTouchOneByOne* _shieldListener;
};

#endif  // SPSQUITLAYER_H
