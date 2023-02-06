/**
 *Copyright (c) 2019 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.4.20
 *Emal: 2117610943@qq.com
 */

#include "MainMenu.h"

#include <tinyxml2.h>

#include "Based/MusicPlayer.h"
#include "InputDataMenu.h"
#include "OptionsMenu.h"
#include "QuitMenu.h"
#include "Scenes/WorldScene/ModernWorld.h"

MainMenu::MainMenu() :
    _runtime(Runtime::getInstance()), _userNameActionParent(nullptr), _userText(nullptr),
    _mouse(nullptr) {
    MusicPlayer::changeBackgroundMusic("mainmusic", true);
    //    cocos2d::log("play roll_in");
    MusicPlayer::playMusic("roll_in");
}

bool MainMenu::init() {
    if (!Scene::init()) {
        return false;
    }

    createMainSprite();
    createMouseListener();
    createMainButton();
    schedule(schedule_selector(MainMenu::curUpdate), 0.05f);  // timer
    schedule([this](float) { _runtime->checkAnimationInterval(); }, 1.f, "FPS");

    createNewUserDataFileName();

    return true;
}

void MainMenu::updateUserNameOnce(float Time) {
    // if have children
    if (_userNameActionParent != nullptr) {
        for (unsigned int i = 0; i < _runtime->userData->getUserName().size(); i++) {
            _userNameActionParent->removeChildByTag(1000);
        }
    }

    srand(time(nullptr));

    // get user name length
    auto const len = _userText->getStringLength();
    for (int i = 0; i < len; i++) {
        auto userNameAction = _userText->getLetter(i);
        if (userNameAction != nullptr && len > 3) {
            userNameAction->setTag(1000);
            _userNameActionParent = userNameAction->getParent();
            userNameAction->setColor(Color3B(rand() % 256, rand() % 256, rand() % 256));
        }
    }
}

void MainMenu::createMainSprite() {
    const string selectorScreenName[] = {
        {"SelectorScreen_BG"},       {"SelectorScreen_BG_Center"}, {"SelectorScreen_BG_Left"},
        {"SelectorScreen_BG_Right"}, {"SelectorScreen_WoodSign1"}, {"SelectorScreen_WoodSign3"},
    };

    for (int i = 0; i < 6; i++) {
        _sprite[i] = Sprite::createWithSpriteFrameName(selectorScreenName[i] + ".png");
    }

    Size size[] = {{1930, 1090}, {1440, 700}, {785, 1140}, {1314, 1008}, {586, 300}, {184, 80}};
    for (int i = 0; i < 6; i++) {
        _sprite[i]->setContentSize(size[i]);
        _sprite[i]->setAnchorPoint(Vec2(0, 0));
    }
    this->addChild(_sprite[0], -1);  // sky

    Vec2 vec2[] = {{300, -100}, {0, -60}, {606, -1000}, {150, 1200}, {150, 1080}};
    int number[] = {1, 2, 3, 4, 5};
    for (int i = 1; i < 6; i++) {
        _sprite[i]->setPosition(vec2[i - 1]);
        i == 5 ? this->addChild(_sprite[number[i - 1]], 1) : this->addChild(_sprite[number[i - 1]]);
    }

    _sprite[1]->runAction(MoveBy::create(0.5f, Vec2(0, 60)));
    _sprite[2]->runAction(MoveBy::create(0.5f, Vec2(0, 60)));
    _sprite[3]->runAction(MoveBy::create(0.5f, Vec2(0, 1000)));
    _sprite[4]->runAction(
        Sequence::create(DelayTime::create(0.8f),
                         EaseElasticOut::create(MoveBy::create(1.0f, Vec2(0, -400))), nullptr));
    _sprite[5]->runAction(
        Sequence::create(DelayTime::create(0.8f),
                         EaseElasticOut::create(MoveBy::create(1.15f, Vec2(0, -440))), nullptr));

    // create user name
    _userText = Text::create();
    _userText->setFontName(GAME_FONT_NAME_1);
    _userText->setFontSize(30);
    _userText->setTextColor(Color4B::YELLOW);
    _userText->setPosition(Vec2(300, 90));
    _sprite[4]->addChild(_userText);

    // if user name empty
    _runtime->userData->getUserName().empty() ?
        _userText->setString(_runtime->gameData->getGameText().find("愤怒的小僵尸")->second) :
        _userText->setString(_runtime->userData->getUserName());

    this->scheduleOnce(schedule_selector(MainMenu::updateUserNameOnce), 0);

    _mainButton[1] = Sprite::createWithSpriteFrameName("SelectorScreen_Adventure_button.png");
    _mainButton[2] = Sprite::createWithSpriteFrameName("SelectorScreen_Survival_button.png");
    _mainButton[3] = Sprite::createWithSpriteFrameName("SelectorScreen_Challenges_button.png");
    _mainButton[4] = Sprite::createWithSpriteFrameName("SelectorScreen_Vasebreaker_button.png");
    _mainButton[5] = Sprite::createWithSpriteFrameName("SelectorScreen_Shadow_Adventure.png");
    _mainButton[6] = Sprite::createWithSpriteFrameName("SelectorScreen_Shadow_Survival.png");
    _mainButton[7] = Sprite::createWithSpriteFrameName("SelectorScreen_Shadow_Challenge.png");
    _mainButton[8] = Sprite::createWithSpriteFrameName("SelectorScreen_Shadow_ZenGarden.png");

    Vec2 Point[] = {{0, 0},     {900, 830}, {880, 650}, {870, 510}, {850, 385},
                    {910, 826}, {890, 644}, {880, 506}, {864, 377}};
    Size buttonSize[] = {{
                             0,
                             0,
                         },
                         {594, 216},
                         {563.4f, 239.4f},
                         {514.8f, 219.6f},
                         {478.8f, 221.4f},
                         {606.6f, 226.8f},
                         {572.4f, 244.8f},
                         {520.2f, 228.6f},
                         {484.2f, 228.6f}};
    for (int i = 8; i > 0; --i) {
        _mainButton[i]->setPosition(Point[i]);
        _mainButton[i]->setContentSize(buttonSize[i]);
        _sprite[3]->addChild(_mainButton[i]);
    }

    char worldFile[128];
    auto& caveFile = _runtime->userData->getCaveFile();
    const char* fileName = caveFile.systemCaveFileName[caveFile.userCaveFileNumber].c_str();
    snprintf(worldFile, 128, fileName, 1);
}

void MainMenu::createMouseListener() {
    // create mouse listener
    _mouse = EventListenerMouse::create();

    // move listener
    _mouse->onMouseMove = [=](Event* event) { _cur = ((EventMouse*)event)->getLocationInView(); };

    // mouse down listener
    _mouse->onMouseDown = [&](Event* event) {
        if (static_cast<bool>(checkCurInButtons())) {
            MusicPlayer::playMusic("gravebutton");
        }
        switch (checkCurInButtons()) {
                // beginAdventureGame
            case MainMenuButton::AdventureButton:
                _mainButton[1]->setPosition(Vec2(902, 828));
                break;

                // beginSurvivalGame
            case MainMenuButton::SurvivalButton:
                _mainButton[2]->setPosition(Vec2(882, 648));
                break;

                // beginChallengesGame
            case MainMenuButton::ChallengesButton:
                _mainButton[3]->setPosition(Vec2(872, 508));
                break;

                // beginVasebreakerGame
            case MainMenuButton::VasebreakerButton:
                _mainButton[4]->setPosition(Vec2(852, 383));
                break;

            default: break;
        }
    };

    // mouse up listener
    _mouse->onMouseUp = [&](Event* event) {
        switch (checkCurInButtons()) {
            case MainMenuButton::AdventureButton:
                _mainButton[1]->setPosition(Vec2(900, 830));
                beginAdventureGame();
                break;
            case MainMenuButton::SurvivalButton:
                _mainButton[2]->setPosition(Vec2(880, 650));
                beginSurvivalGame();
                break;
            case MainMenuButton::ChallengesButton:
                _mainButton[3]->setPosition(Vec2(870, 510));
                beginChallengesGame();
                break;
            case MainMenuButton::VasebreakerButton:
                _mainButton[4]->setPosition(Vec2(850, 385));
                beginVasebreakerGame();
                break;
            default: break;
        }
    };

    _director->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_mouse, this);
}

MainMenuButton MainMenu::checkCurInButtons() {
    // check whether cursor is on the button
    if ((_cur.x >= 1210 && _cur.x <= 1800 && _cur.y >= 800 && _cur.y <= 900) ||
        (_cur.x >= 1210 && _cur.x <= 1600 && _cur.y >= 900 && _cur.y <= 930) ||
        (_cur.x >= 1580 && _cur.x <= 1790 && _cur.y >= 730 && _cur.y <= 800) ||
        (_cur.x >= 1390 && _cur.x <= 1580 && _cur.y >= 745 && _cur.y <= 800)) {
        return MainMenuButton::AdventureButton;
    } else if ((_cur.x >= 1210 && _cur.x <= 1770 && _cur.y >= 630 && _cur.y <= 700) ||
               (_cur.x >= 1210 && _cur.x <= 1500 && _cur.y >= 700 && _cur.y <= 730) ||
               (_cur.x >= 1210 && _cur.x <= 1400 && _cur.y >= 730 && _cur.y <= 740) ||
               (_cur.x >= 1210 && _cur.x <= 1350 && _cur.y >= 740 && _cur.y <= 760) ||
               (_cur.x >= 1500 && _cur.x <= 1600 && _cur.y >= 700 && _cur.y <= 720) ||
               (_cur.x >= 1350 && _cur.x <= 1760 && _cur.y >= 610 && _cur.y <= 630) ||
               (_cur.x >= 1450 && _cur.x <= 1750 && _cur.y >= 590 && _cur.y <= 610) ||
               (_cur.x >= 1550 && _cur.x <= 1750 && _cur.y >= 570 && _cur.y <= 590) ||
               (_cur.x >= 1660 && _cur.x <= 1750 && _cur.y >= 550 && _cur.y <= 570)) {
        return MainMenuButton::SurvivalButton;
    } else if ((_cur.x >= 1220 && _cur.x <= 1730 && _cur.y >= 500 && _cur.y <= 535) ||
               (_cur.x >= 1220 && _cur.x <= 1600 && _cur.y >= 535 && _cur.y <= 560) ||
               (_cur.x >= 1220 && _cur.x <= 1450 && _cur.y >= 560 && _cur.y <= 590) ||
               (_cur.x >= 1220 && _cur.x <= 1350 && _cur.y >= 590 && _cur.y <= 610) ||
               (_cur.x >= 1350 && _cur.x <= 1730 && _cur.y >= 480 && _cur.y <= 500) ||
               (_cur.x >= 1430 && _cur.x <= 1720 && _cur.y >= 460 && _cur.y <= 480) ||
               (_cur.x >= 1520 && _cur.x <= 1720 && _cur.y >= 440 && _cur.y <= 460) ||
               (_cur.x >= 1590 && _cur.x <= 1710 && _cur.y >= 420 && _cur.y <= 440)) {
        return MainMenuButton::ChallengesButton;
    } else if ((_cur.x >= 1230 && _cur.x <= 1300 && _cur.y >= 380 && _cur.y <= 485) ||
               (_cur.x >= 1300 && _cur.x <= 1380 && _cur.y >= 360 && _cur.y <= 470) ||
               (_cur.x >= 1380 && _cur.x <= 1400 && _cur.y >= 350 && _cur.y <= 460) ||
               (_cur.x >= 1400 && _cur.x <= 1500 && _cur.y >= 330 && _cur.y <= 440) ||
               (_cur.x >= 1500 && _cur.x <= 1550 && _cur.y >= 310 && _cur.y <= 430) ||
               (_cur.x >= 1550 && _cur.x <= 1650 && _cur.y >= 290 && _cur.y <= 410) ||
               (_cur.x >= 1650 && _cur.x <= 1690 && _cur.y >= 280 && _cur.y <= 400)) {
        return MainMenuButton::VasebreakerButton;
    } else {
        _mainButton[1]->setPosition(Vec2(900, 830));
        _mainButton[2]->setPosition(Vec2(880, 650));
        _mainButton[3]->setPosition(Vec2(870, 510));
        _mainButton[4]->setPosition(Vec2(850, 385));
        return MainMenuButton::NullButton;
    }
}

void MainMenu::curUpdate(float time) {
    // play music when cursor move over the button
    this->playMusicBleepInMainButtons(0, Vec2(_cur.x - 606, _cur.y));
    this->playMusicBleepInMainButtons(1, Vec2(_cur.x - 606, _cur.y));
    this->playMusicBleepInMainButtons(2, Vec2(_cur.x - 606, _cur.y));
    this->playMusicBleepInMainButtons(3, _cur);

    this->playMusicBleepInGameButtons(MainMenuButton::AdventureButton);
    this->playMusicBleepInGameButtons(MainMenuButton::SurvivalButton);
    this->playMusicBleepInGameButtons(MainMenuButton::ChallengesButton);
    this->playMusicBleepInGameButtons(MainMenuButton::VasebreakerButton);

    // change pictures when cursor move over the button
    _menuItem[0]->getBoundingBox().containsPoint(Vec2(_cur.x - 606, _cur.y)) ?
        _menuItem[0]->setColor(Color3B::WHITE) :
        _menuItem[0]->setColor(Color3B::BLACK);
    _menuItem[1]->getBoundingBox().containsPoint(Vec2(_cur.x - 606, _cur.y)) ?
        _menuItem[1]->setColor(Color3B::WHITE) :
        _menuItem[1]->setColor(Color3B::BLACK);
    _menuItem[2]->getBoundingBox().containsPoint(Vec2(_cur.x - 606, _cur.y)) ?
        _menuItem[2]->setColor(Color3B::WHITE) :
        _menuItem[2]->setColor(Color3B::BLACK);
    _menuItem[3]->getBoundingBox().containsPoint(_cur) ?
        _menuItem[3]->setNormalImage(
            Sprite::createWithSpriteFrameName("SelectorScreen_WoodSign2_press.png")) :
        _menuItem[3]->setNormalImage(
            Sprite::createWithSpriteFrameName("SelectorScreen_WoodSign2.png"));

    // if user name update
    if (_runtime->userData->getIsUpdate()) {
        _userText->setString(_runtime->userData->getUserName());
        this->scheduleOnce(schedule_selector(MainMenu::updateUserNameOnce), 0);
        _runtime->userData->setIsUpdate(false);
    }
}

void MainMenu::playMusicBleepInGameButtons(MainMenuButton button) {
    auto ID = static_cast<int>(button);
    // check whether cursor is on the button
    if (checkCurInButtons() == button) {
        switch (button) {
            case MainMenuButton::AdventureButton: _mainButton[ID]->setColor(Color3B::WHITE); break;
            default: _mainButton[ID]->setColor(Color3B(110, 110, 110)); break;
        }

        // if no music play
        if (!_playMusic[ID - 1]) {
            MusicPlayer::playMusic("bleep");
            _playMusic[ID - 1] = true;
        }
    } else {
        if (_playMusic[ID - 1])
            _playMusic[ID - 1] = false;

        switch (button) {
            case MainMenuButton::AdventureButton:
                _mainButton[ID]->setColor(Color3B(150, 150, 150));
                break;
            default: _mainButton[ID]->setColor(Color3B(80, 80, 80)); break;
        }
    }
}

void MainMenu::playMusicBleepInMainButtons(int ID, const Vec2& vec2) {
    if (_menuItem[ID]->getBoundingBox().containsPoint(vec2)) {
        // if no music play
        if (!_playMusic[ID + 4]) {
            MusicPlayer::playMusic("bleep");
            _playMusic[ID + 4] = true;
        }
    } else {
        if (_playMusic[ID + 4])
            _playMusic[ID + 4] = false;
    }
}

void MainMenu::beginAdventureGame() {
    auto& userWorldData = _runtime->userData->getUserWorldData();
    userWorldData.mainToWorld = true;
    //    MusicPlayer::stopMusic();
    Director::getInstance()->replaceScene(TransitionFade::create(1.f, ModernWorld::create()));
}

void MainMenu::beginSurvivalGame() {}

void MainMenu::beginChallengesGame() {}

void MainMenu::beginVasebreakerGame() {}

void MainMenu::menuHelpCallBack(Ref* pSender) {
    MusicPlayer::playMusic("tap2");
    //    Director::getInstance()->replaceScene(
    //        TransitionCrossFade::create(0.5f, HelpScene::createHelpScene()));
}

void MainMenu::menuOptionCallBack(Ref* pSender) {
    MusicPlayer::playMusic("tap");
    setMouseListenerEnable(false);
    auto option = OptionsMenu::create();
    if (option) {
        option->setMouseListener(_mouse);
        this->addChild(option, 1, "_optionLayer");
    }
}

void MainMenu::menuQuitCallBack(Ref* pSender) {
    MusicPlayer::playMusic("tap2");
    setMouseListenerEnable(false);
    auto quit = QuitMenu::create();
    if (quit) {
        quit->setMouseListener(_mouse);
        this->addChild(quit, 1, "_quitLayer");
    }
}

void MainMenu::menuDataCallBack(Ref* pSender) {
    MusicPlayer::playMusic("tap");
    //    cocos2d::log("multiple user archive not support yet");
    setMouseListenerEnable(false);
    auto input = InputDataMenu::create();
    if (input) {
        input->setMouseListener(_mouse);
        this->addChild(input, 1, "_inputLayer");
    }
}

void MainMenu::createMainButton() {
    // create buttons
    _menuItem[0] = MenuItemImage::create("", "", CC_CALLBACK_1(MainMenu::menuOptionCallBack, this));
    _menuItem[1] = MenuItemImage::create("", "", CC_CALLBACK_1(MainMenu::menuHelpCallBack, this));
    _menuItem[2] = MenuItemImage::create("", "", CC_CALLBACK_1(MainMenu::menuQuitCallBack, this));
    _menuItem[3] = MenuItemImage::create("", "", CC_CALLBACK_1(MainMenu::menuDataCallBack, this));

    _menuItem[0]->setNormalSpriteFrame(
        SpriteFrameCache::getInstance()->getSpriteFrameByName("SelectorScreen_Options2.png"));
    _menuItem[1]->setNormalSpriteFrame(
        SpriteFrameCache::getInstance()->getSpriteFrameByName("SelectorScreen_Help2.png"));
    _menuItem[2]->setNormalSpriteFrame(
        SpriteFrameCache::getInstance()->getSpriteFrameByName("SelectorScreen_Quit2.png"));
    _menuItem[3]->setNormalSpriteFrame(
        SpriteFrameCache::getInstance()->getSpriteFrameByName("SelectorScreen_WoodSign2.png"));

    _menuItem[0]->setCallback(CC_CALLBACK_1(MainMenu::menuOptionCallBack, this));
    _menuItem[1]->setCallback(CC_CALLBACK_1(MainMenu::menuHelpCallBack, this));
    _menuItem[2]->setCallback(CC_CALLBACK_1(MainMenu::menuQuitCallBack, this));
    _menuItem[3]->setCallback(CC_CALLBACK_1(MainMenu::menuDataCallBack, this));

    _menuItem[0]->setPosition(Vec2(960, 175));
    _menuItem[1]->setPosition(Vec2(1080, 130));
    _menuItem[2]->setPosition(Vec2(1210, 140));
    _menuItem[3]->setPosition(Vec2(145, 1080));

    _menuItem[3]->setAnchorPoint(Vec2(0, 0));
    _menuItem[3]->runAction(
        Sequence::create(DelayTime::create(0.8f),
                         EaseElasticOut::create(MoveBy::create(1.1f, Vec2(0, -400))), NULL));

    _menu[0] = Menu::create(_menuItem[0], _menuItem[1], _menuItem[2], NULL);
    _menu[1] = Menu::create(_menuItem[3], NULL);

    _menu[0]->setPosition(Vec2(0, 0));
    _menu[1]->setPosition(Vec2(0, 0));

    _sprite[3]->addChild(_menu[0]);
    this->addChild(_menu[1]);
}

void MainMenu::createNewUserDataFileName() {
    if (_runtime->userData->getUserName() == "未命名存档") {
        menuDataCallBack(nullptr);
    }
}

void MainMenu::setMouseListenerEnable(bool isEnable) { _mouse->setEnabled(isEnable); }
