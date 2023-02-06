/**
 *Copyright (c) 2023 Xi-Gong.All Right Reserved
 *Author : Xi-Gong
 *Date: 2023.02.05
 *Email: xi_gong@foxmail.com
 */

#ifndef USERSETTING_H
#define USERSETTING_H

#include <ui/CocosGUI.h>

#include <list>

using cocos2d::ui::CheckBox;
using std::list;

struct UserSetting {
    UserSetting() :
        soundEffectVolume(0.5f), backgroundMusicVolume(0.2f),
        showFPS(CheckBox::EventType::SELECTED), highFPS(CheckBox::EventType::SELECTED),
        fullScreen(CheckBox::EventType::UNSELECTED), cursorNotHide(CheckBox::EventType::UNSELECTED),
        stretchingShow(CheckBox::EventType::SELECTED),
        verticalSynchronization(CheckBox::EventType::SELECTED){};
    ~UserSetting() = default;

    // sound settings
    float soundEffectVolume;
    float backgroundMusicVolume;
    list<int> backgroundMusic;

    // screen settings
    CheckBox::EventType showFPS;
    CheckBox::EventType highFPS;
    CheckBox::EventType fullScreen;
    CheckBox::EventType cursorNotHide;
    CheckBox::EventType stretchingShow;
    CheckBox::EventType easeAnimation;
    CheckBox::EventType verticalSynchronization;
};

#endif  // USERSETTING_H
