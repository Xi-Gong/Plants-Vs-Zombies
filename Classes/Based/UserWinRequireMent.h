/**
 *Copyright (c) 2019 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.4.20
 *Emal: 2117610943@qq.com
 */

#ifndef USERWINREQUIREMENT_H
#define USERWINREQUIREMENT_H

#include <cocos2d.h>

#include "Based/GameTypes.h"
#include "Based/Runtime.h"

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace cocos2d::experimental;

class UserWinRequirement : public Node {
  public:
    UserWinRequirement(Node* node = nullptr);
    ~UserWinRequirement() = default;

    static UserWinRequirement* create(Node* node);
    void createDialogBox(GameTypes finishedid);
    void setParent(Node* node);
    void setButtonVisible(bool visible);
    void setDialogOpacity(const int opacity);
    void setListenerEnable(bool enable);
    void setShowDialogAction();
    void setDelectDialogAction();
    Sprite* getDialog() const;

  private:
    void showRequirement(GameTypes finishedid); /* 显示要求 */
    void showText(const string& text, const int& ID, Color3B color = Color3B::BLACK);
    void createShieldLayer();

  private:
    Runtime* _runtime;
    Node* _node;
    Button* _continuesGame;
    Scale9Sprite* _levelObjiectives;
    EventListenerTouchOneByOne* _listener;
    EventListenerTouchOneByOne* _shieldListener;
    Vec2 _phasePosition; /* 相差位置 */

    Vec2 _textPosition[4][4] = /* 文字位置 */
        {{
             Vec2(100, 135),
         },
         {
             Vec2(100, 110),
             Vec2(100, 160),
         },
         {Vec2(100, 90), Vec2(100, 135), Vec2(100, 180)},
         {Vec2(100, 80), Vec2(100, 115), Vec2(100, 150), Vec2(100, 185)}};
};

#endif  // USERWINREQUIREMENT_H
