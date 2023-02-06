/**
 *Copyright (c) 2019 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.4.20
 *Emal: 2117610943@qq.com
 */

#include "GSPauseLayer.h"

#include "Based/MusicPlayer.h"
#include "GSPauseQuitLayer.h"
#include "GameScene.h"

GSPauseLayer::GSPauseLayer() : _levelObjectives(nullptr), _runtime(Runtime::getInstance()) {}

Layer* GSPauseLayer::addLayer() { return GSPauseLayer::create(); }

bool GSPauseLayer::init() {
    if (!LayerColor::initWithColor(Color4B(0, 0, 0, 180))) {
        return false;
    }

    createShieldLayer();
    createDialog();
    showAniamtions();
    showButton();
    return true;
}

void GSPauseLayer::createShieldLayer() {
    // set shieldLayer
    auto shieldListener = EventListenerTouchOneByOne::create();
    shieldListener->onTouchBegan = [](Touch* touch, Event* event) -> bool { return true; };
    shieldListener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(shieldListener, this);
}

void GSPauseLayer::createDialog() {
    _levelObjectives = Scale9Sprite::createWithSpriteFrameName("LevelObjiectives.png");
    _levelObjectives->setPosition(Director::getInstance()->getWinSize() / 2.0f);
    _levelObjectives->setGlobalZOrder(10);
    _levelObjectives->setScale(2.0f);
    this->addChild(_levelObjectives);

    auto LevelObjiectivesText = Text::create();
    LevelObjiectivesText->setString("休息一会吧！");
    LevelObjiectivesText->setFontName(GAME_FONT_NAME_1);
    LevelObjiectivesText->setFontSize(50);
    LevelObjiectivesText->setScale(0.5f);
    LevelObjiectivesText->setColor(Color3B(0, 255, 255));
    LevelObjiectivesText->setPosition(Vec2(_levelObjectives->getContentSize().width / 2, 245));
    LevelObjiectivesText->setGlobalZOrder(10);
    _levelObjectives->addChild(LevelObjiectivesText);

    Dialog::createTouchListener(_levelObjectives);
}

void GSPauseLayer::showAniamtions() {
    auto& animationData = _runtime->gameData->getAnimationData();
    auto pauseAnimation = SkeletonAnimation::createWithData(animationData.find("raptor")->second);
    pauseAnimation->setAnimation(0, "walk", true);
    pauseAnimation->setPosition(Vec2(_levelObjectives->getContentSize().width / 2.f - 40, 50));
    pauseAnimation->setGlobalZOrder(10);
    pauseAnimation->setScale(0.2f);
    _levelObjectives->addChild(pauseAnimation);
}

void GSPauseLayer::showButton() {
    auto button = Button::create("Continue1.png", "Continue.png", "", TextureResType::PLIST);
    auto& gameText = _runtime->gameData->getGameText();
    button->setTitleText(gameText.find("确定")->second);
    button->setTitleFontName(GAME_FONT_NAME_1);
    button->setTitleFontSize(30);
    button->setTitleColor(Color3B::YELLOW);
    button->setPosition(Vec2(_levelObjectives->getContentSize().width / 2.0f, 10));
    button->setGlobalZOrder(10);
    button->setScale(0.5f);
    button->runAction(FadeIn::create(0.5f));
    button->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type) {
            case ui::Widget::TouchEventType::BEGAN: MusicPlayer::playMusic("gravebutton"); break;
            case ui::Widget::TouchEventType::ENDED:
                GSPauseQuitLayer::resumeLayer();
                this->removeFromParent();
                break;
            default: break;
        }
    });
    _levelObjectives->addChild(button);
}
