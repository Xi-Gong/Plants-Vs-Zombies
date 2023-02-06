/**
 *Copyright (c) 2019 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.4.20
 *Emal: 2117610943@qq.com
 */

#ifndef DIALOG_H
#define DIALOG_H

#include <cocos2d.h>

#include "Runtime.h"

using namespace cocos2d;
using namespace cocos2d::experimental;

class Dialog : public LayerColor {
  public:
    Dialog();
    virtual ~Dialog() = default;

    static EventListenerTouchOneByOne* createTouchListener(Sprite* sprite);

    virtual void setMouseListener(EventListenerMouse* listener);

  protected:
    // create label
    virtual Label* label(const std::string& name, const float& fontsize,
                         const Vec2& vec2 = Vec2(0, 0), const float& space = 0,
                         const Color3B& color = Color3B::GREEN, const float& scale = 1);

    // create label on button
    virtual void createLabel(Sprite* sprite, MenuItemImage* MenuItem, const std::string& name,
                             Vec2& vec2, float& fontsize, const float& space = 0,
                             const Color3B& color = Color3B::GREEN);

    virtual void createShieldLayer(Node* node);
    virtual void deleteDialog(){};
    virtual void setMouseListenerEnable(bool isEnable = true);

  protected:
    Runtime* _runtime;
    EventListenerMouse* _mouseListener;

  private:
    Vec2 _phasePosition;
    EventListenerTouchOneByOne* _shieldListener;
};

#endif  // DIALOG_H
