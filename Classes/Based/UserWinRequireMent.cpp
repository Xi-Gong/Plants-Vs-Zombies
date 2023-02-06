/**
 *Copyright (c) 2019 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.4.20
 *Emal: 2117610943@qq.com
 */

#include "UserWinRequireMent.h"

#include "Based/Dialog.h"
#include "Based/GameData/LevelDataHandler.h"
#include "Scenes/WorldScene/ModernWorld.h"

UserWinRequirement::UserWinRequirement(Node* node) :
    _node(node), _listener(nullptr), _shieldListener(nullptr), _levelObjiectives(nullptr),
    _runtime(Runtime::getInstance()) {}

UserWinRequirement* UserWinRequirement::create(Node* node) {
    UserWinRequirement* userWinRequirement = new (std::nothrow) UserWinRequirement(node);
    if (userWinRequirement && userWinRequirement->init()) {
        userWinRequirement->autorelease();
        return userWinRequirement;
    }
    CC_SAFE_DELETE(userWinRequirement);
    return nullptr;
}

void UserWinRequirement::createShieldLayer() {
    // set shieldLayer
    _shieldListener = EventListenerTouchOneByOne::create();
    _shieldListener->onTouchBegan = [](Touch* touch, Event* event) -> bool { return true; };
    _shieldListener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_shieldListener, _node);
}

void UserWinRequirement::createDialogBox(GameTypes finishedid) {
    createShieldLayer();

    _levelObjiectives = Scale9Sprite::createWithSpriteFrameName("LevelObjiectives.png");
    _levelObjiectives->setPosition(Director::getInstance()->getWinSize() / 2.0f);
    _levelObjiectives->setScale(2.0f);
    _node->addChild(_levelObjiectives);

    auto LevelObjiectivesText = Text::create();
    auto& gameText = _runtime->gameData->getGameText();
    LevelObjiectivesText->setString(gameText.find("通关要求！")->second);
    LevelObjiectivesText->setFontName(GAME_FONT_NAME_1);
    LevelObjiectivesText->setFontSize(50);
    LevelObjiectivesText->setScale(0.5f);
    LevelObjiectivesText->setColor(Color3B(0, 255, 255));
    LevelObjiectivesText->setPosition(Vec2(_levelObjiectives->getContentSize().width / 2, 245));
    _levelObjiectives->addChild(LevelObjiectivesText);

    /* 显示要求 */
    showRequirement(finishedid);

    Dialog::createTouchListener(_levelObjiectives);
}

void UserWinRequirement::setParent(Node* node) { _node = node; }

void UserWinRequirement::setButtonVisible(bool visible) { _continuesGame->setVisible(visible); }

void UserWinRequirement::setDialogOpacity(const int opacity) {
    _levelObjiectives->setOpacity(opacity);
}

void UserWinRequirement::setListenerEnable(bool enable) { _listener->setEnabled(enable); }

void UserWinRequirement::setShowDialogAction() {
    if (_levelObjiectives) {
        _levelObjiectives->setPosition(
            Vec2(Director::getInstance()->getWinSize().width / 2.0f, 3000));
        _levelObjiectives->runAction(EaseBounceOut::create(
            MoveTo::create(0.5f, Director::getInstance()->getWinSize() / 2.0f)));
    }
}

void UserWinRequirement::setDelectDialogAction() {
    if (_levelObjiectives) {
        _levelObjiectives->runAction(MoveBy::create(0.2f, Vec2(0, -1000)));
    }
}

Sprite* UserWinRequirement::getDialog() const { return _levelObjiectives; }

void UserWinRequirement::showRequirement(GameTypes finishedid) {
    int levelNumber = LevelDataHandler::getInstance()->getLevelNumber();
    LevelData* leveldata = LevelDataHandler::getInstance()->readLevelData(levelNumber);
    for (unsigned int i = 0; i < leveldata->gameType.size(); i++) {
        switch (static_cast<GameTypes>(leveldata->gameType.at(i))) {
            case GameTypes::CreateWall:
                showText(_runtime->gameData->getGameText()
                             .find("建立你的防线，阻止僵尸的进攻！")
                             ->second,
                         i);
                break;
            default: break;
        }
    }
}

void UserWinRequirement::showText(const string& text, const int& ID, Color3B color) {
    auto requiretext = Label::createWithTTF(text, GAME_FONT_NAME_1, 40);
    requiretext->setColor(Color3B::BLACK);
    requiretext->setScale(0.5f);
    requiretext->setLineBreakWithoutSpace(true);
    requiretext->setWidth(790);

    int levelNumber = LevelDataHandler::getInstance()->getLevelNumber();
    LevelData* levelData = LevelDataHandler::getInstance()->readLevelData(levelNumber);

    requiretext->setPosition(_textPosition[levelData->gameType.size() - 1][ID]);
    requiretext->setAnchorPoint(Vec2(0, 1));
    requiretext->setColor(color);
    _levelObjiectives->addChild(requiretext);

    auto LevelObjiectives2 = Sprite::createWithSpriteFrameName("LevelObjiectives2.png");
    LevelObjiectives2->setPosition(_textPosition[levelData->gameType.size() - 1][ID] +
                                   Vec2(-40, +6));
    LevelObjiectives2->setAnchorPoint(Vec2(0, 1));
    LevelObjiectives2->setScale(0.5f);
    _levelObjiectives->addChild(LevelObjiectives2);
}
