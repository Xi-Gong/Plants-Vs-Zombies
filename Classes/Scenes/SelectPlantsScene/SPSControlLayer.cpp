/**
 *Copyright (c) 2019 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.4.20
 *Emal: 2117610943@qq.com
 */

#include "SPSControlLayer.h"

#include <ui/CocosGUI.h>

#include "Based/MusicPlayer.h"
#include "SPSQuitLayer.h"

using namespace cocos2d::ui;

SPSControlLayer::SPSControlLayer() : _runtime(Runtime::getInstance()) {}

bool SPSControlLayer::init() {
    if (!Layer::init()) {
        return false;
    }

    /* 创建按钮 */
    createButton();

    /* 显示用户名字 */
    showUserName();

    return true;
}

void SPSControlLayer::createButton() {
    /* 创建退出按钮 */
    auto button = Button::create("StopButton.png", "StopButtonDown.png", "", TextureResType::PLIST);
    button->setPosition(Vec2(1870, 1030));
    button->setScale(0.7f);
    this->addChild(button);
    button->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type) {
            case cocos2d::ui::Widget::TouchEventType::BEGAN:
                MusicPlayer::playMusic("gravebutton");
                break;
            case cocos2d::ui::Widget::TouchEventType::ENDED: createDialog(); break;
            default: break;
        }
    });
}

void SPSControlLayer::showUserName() {
    char buff[128];
    auto userData = _runtime->userData;
    auto& userWorldData = userData->getUserWorldData();
    snprintf(buff, 128, "第 %d 天", userWorldData.currentLevel);

    auto userName = Text::create();
    userName->setString("“" + userData->getUserName() + "”" +
                        _runtime->gameData->getGameText().find("的时空冒险之旅")->second + buff);
    userName->setFontName(GAME_FONT_NAME_1);
    userName->setFontSize(60);
    userName->setColor(Color3B::YELLOW);
    userName->setName("username");
    userName->setPosition(Vec2(_director->getWinSize().width / 2.0f, 150));
    this->addChild(userName);
}

void SPSControlLayer::createDialog() { this->addChild(SPSQuitLayer::create(), 1, "_quitLayer"); }
