/**
 *Copyright (c) 2019 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.4.20
 *Emal: 2117610943@qq.com
 */

#include "QuitMenu.h"

#include <ui/CocosGUI.h>

#include "Based/DataLoader.h"
#include "Based/MusicPlayer.h"

using namespace cocos2d::ui;

bool QuitMenu::init() {
    if (!LayerColor::initWithColor(Color4B(0, 0, 0, 180))) {
        return false;
    }

    createShieldLayer(this);

    this->createDialog();

    return true;
}

int QuitMenu::getSumRunTime() {
    time_t tt;
    struct tm* nowtime;
    time(&tt);
    nowtime = localtime(&tt);

    auto beginday = UserDefault::getInstance()->getIntegerForKey("BEGINDAY");
    auto beginhour = UserDefault::getInstance()->getIntegerForKey("BEGINHOUR");
    auto beginmin = UserDefault::getInstance()->getIntegerForKey("BEGINMIN");
    auto beginsec = UserDefault::getInstance()->getIntegerForKey("BEGINSEC");

    int sumTime = 0;

    sumTime = UserDefault::getInstance()->getIntegerForKey("SUMRUNTIME") +
              (nowtime->tm_mday * 24 * 3600 + nowtime->tm_hour * 3600 + nowtime->tm_min * 60 +
               nowtime->tm_sec) -
              (beginday * 24 * 3600 + beginhour * 3600 + beginmin * 60 + beginsec);

    return sumTime;
}

void QuitMenu::createDialog() {
    _quitDialog = Sprite::createWithSpriteFrameName("QuitDialog.png");
    _quitDialog->setPosition(Director::getInstance()->getWinSize() / 2);
    _quitDialog->setScale(2.0f);
    this->addChild(_quitDialog);

    this->createButtons(_runtime->gameData->getGameText().find("退出游戏")->second, Vec2(90, 65),
                        1);
    this->createButtons(_runtime->gameData->getGameText().find("取消")->second, Vec2(225, 65), 2);

    /* 创建触摸监听 */
    this->createTouchListener(_quitDialog);
}

void QuitMenu::createButtons(const std::string& Label, const Vec2& vec2, const int ID) {
    auto button = Button::create("button.png", "button_down.png", "", TextureResType::PLIST);
    button->setTitleLabel(label(Label, 20));
    button->setPosition(vec2);
    _quitDialog->addChild(button);

    _quitDialog->addChild(label(_runtime->gameData->getGameText().find("退出")->second, 25,
                                Vec2(155, 160), 0, Color3B::YELLOW));
    _quitDialog->addChild(
        label(_runtime->gameData->getGameText().find("确定要退出游戏吗？")->second, 15,
              Vec2(160, 130), 0, Color3B::YELLOW));

    button->addTouchEventListener([=](Ref* sender, Widget::TouchEventType type) {
        switch (type) {
            case Widget::TouchEventType::BEGAN: {
                MusicPlayer::playMusic("gravebutton");
                break;
            }

            case Widget::TouchEventType::ENDED: {
                switch (ID) {
                    case 1: {
                        cocos2d::log("trigger");
                        caveTime(getSumRunTime());
                        DataLoader::caveUserFileData();
                        _runtime->resumeProhibit();
                        if (_runtime->prohibitId == -1)
                            Director::getInstance()->end();
                        break;
                    }

                    case 2: {
                        deleteDialog();
                        break;
                    }
                }
            }

            default: {
                cocos2d::log("Enumeration values 'MOVED' and 'CANCELED' not handled in switch");
                break;
            }
        }
    });
}

void QuitMenu::caveTime(const int time) {
    UserDefault::getInstance()->setIntegerForKey("SUMRUNTIME", time);
}

void QuitMenu::deleteDialog() {
    setMouseListenerEnable();
    this->removeFromParent();
}
