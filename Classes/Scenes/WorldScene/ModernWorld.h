/**
 *Copyright (c) 2019 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.4.20
 *Emal: 2117610943@qq.com
 */

#ifndef MODERNWORLD_H
#define MODERNWORLD_H

#include <cocos2d.h>
#include <ui/CocosGUI.h>

#include "Based/GameData/LevelDataHandler.h"
#include "Based/Runtime.h"
#include "Based/UserData/UserDataHandler.h"

using namespace cocos2d;
using namespace cocos2d::ui;

class ModernWorld : public Scene {
  public:
    ModernWorld();
    ~ModernWorld();

    CREATE_FUNC(ModernWorld);
    virtual bool init() override;
    virtual void onEnter() override;

    static void setPopEnter(const bool isPopEnter);

  protected:
    virtual void readWorldLevel();
    virtual void setLevelVisible(Node* node);
    virtual void createButtonListener(ui::Button* button, const int ID);
    virtual ui::Button* createButton(Node* node, const std::string& name, const Vec2& position);
    virtual void createScrollView();
    virtual void createGoBack();

    void showLevels();
    void createBackground();
    void addScrollView(const int id);
    Sprite* createSprite(const std::string& name, const Vec2& position, const float scale,
                         const int zorder, const float speed, bool IsFlipped = false);
    Sprite* createSprite(Node* node, const std::string& name, const Vec2& position,
                         const float scale, const int zorder, bool IsFlipped = false);
    void createMouseListener();
    void playProhibitMusic(Button* button);
    void playLevelGameAndCaveThings(const int id);

  protected:
    Runtime* _runtime;
    LevelDataHandler* _levelDataHandler;
    UserDataHandler* _userDataHandler;

    Director* _director;
    ParallaxNode* _parallax;
    Size _backgroundSize;
    ui::ScrollView* _scrollView;
    int _level;
    float _worldPosition;        /* 世界初始位置 */
    float _worldRollingDistance; /* 计算鼠标滚动距离 */
    list<Button*> _levelButton;

  private:
    static bool _isPopEnter;
};

#endif  // MODERNWORLD_H
