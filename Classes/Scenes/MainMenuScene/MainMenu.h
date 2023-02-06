/**
 *Copyright (c) 2019 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.4.20
 *Emal: 2117610943@qq.com
 */

#ifndef MAINMENU_H
#define MAINMENU_H

#include <cocos2d.h>
#include <ui/CocosGUI.h>

#include <map>
#include <string>

#include "Based/Runtime.h"

using namespace cocos2d;
using namespace cocos2d::ui;
using std::map;
using std::string;

enum class MainMenuButton {
    NullButton = 0,
    AdventureButton,
    SurvivalButton,
    ChallengesButton,
    VasebreakerButton
};

class MainMenu : public Scene {
  public:
    MainMenu();
    ~MainMenu() = default;
    CREATE_FUNC(MainMenu);
    virtual bool init() override;

  private:
    // create main menu sprite
    void createMainSprite();

    void createMouseListener();
    void setMouseListenerEnable(bool isEnable);

    // check whether cursor is on the button
    MainMenuButton checkCurInButtons();

    // cursor timer
    void curUpdate(float time);
    void updateUserNameOnce(float Time);

    // play music
    void playMusicBleepInGameButtons(MainMenuButton button);
    void playMusicBleepInMainButtons(int ID, const Vec2& vec2);

    // game type choices
    void beginAdventureGame();

    // unimplement yet
    void beginSurvivalGame();
    void beginChallengesGame();
    void beginVasebreakerGame();

    // call back functions
    void menuHelpCallBack(Ref* pSender);
    void menuOptionCallBack(Ref* pSender);
    void menuQuitCallBack(Ref* pSender);
    void menuDataCallBack(Ref* pSender);

    void createMainButton();
    void createNewUserDataFileName();

  private:
    Runtime* _runtime;

    Sprite* _sprite[17];
    Sprite* _mainButton[9];
    Menu* _menu[2];
    MenuItemImage* _menuItem[5];
    Text* _userText;

    // mouse listener
    EventListenerMouse* _mouse;

    // curosr position
    Vec2 _cur;

    // Is music play
    bool _playMusic[8] = {false};

    Node* _userNameActionParent;
};

#endif  // MAINMENU_H
