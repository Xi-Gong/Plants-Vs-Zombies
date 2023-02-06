/**
 *Copyright (c) 2019 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.4.20
 *Emal: 2117610943@qq.com
 */

#include "GSGameEndLayer.h"

#include <AudioEngine.h>

#include "Based/Car.h"
#include "Based/Coin.h"
#include "Based/MusicPlayer.h"
#include "GSInformationLayer.h"
#include "GSPauseQuitLayer.h"
#include "Scenes/GameScene/GSData.h"
#include "Scenes/WorldScene/ModernWorld.h"

GSGameEndLayer::GSGameEndLayer() :
    _userWinRequirement(nullptr), _runtime(Runtime::getInstance()),
    _levelDataHandler(LevelDataHandler::getInstance()),
    _userDataHandler(UserDataHandler::getInstance()) {
    srand(time(nullptr));
}

GSGameEndLayer::~GSGameEndLayer() {
    if (_userWinRequirement) {
        delete _userWinRequirement;
    }
}

bool GSGameEndLayer::init() {
    if (!LayerColor::initWithColor(Color4B(0, 0, 0, 180))) {
        return false;
    }

    createShieldLayer();

    return true;
}

void GSGameEndLayer::createShieldLayer() {
    auto shieldListener = EventListenerTouchOneByOne::create();
    shieldListener->onTouchBegan = [](Touch* touch, Event* event) -> bool { return true; };
    shieldListener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(shieldListener, this);
}

void GSGameEndLayer::successfullEntry() {
    Director::getInstance()->getScheduler()->setTimeScale(1.0f); /* 恢复播放倍数 */
    Director::getInstance()->getOpenGLView()->setCursor("resources/images/System/cursor.png",
                                                        Point::ANCHOR_TOP_LEFT);

    _userDataHandler->createNewLevelDataDocument();
    const char* key = _runtime->userData->getCurrentCaveFileLevelWorldName();
    _userDataHandler->removeLevelData(key);

    caveLevelNumber();
    carsToCoins();

    rewardThing();
}

void GSGameEndLayer::breakThrough(GameTypes gameType) {
    GSPauseQuitLayer::pauseLayer();
    Director::getInstance()->getScheduler()->setTimeScale(1.0f); /* 恢复播放倍数 */
    Director::getInstance()->getOpenGLView()->setCursor("resources/images/System/cursor.png",
                                                        Point::ANCHOR_TOP_LEFT);

    _userDataHandler->createNewLevelDataDocument();
    const char* key = _runtime->userData->getCurrentCaveFileLevelWorldName();
    _userDataHandler->removeLevelData(key);

    MusicPlayer::playMusic("losemusic");

    if (gameType == GameTypes::UserLose) {
        showFailText();
    } else {
        showFailDialog(gameType);
    }
}

void GSGameEndLayer::showFailDialog(GameTypes gameType) {
    _userWinRequirement = new UserWinRequirement(this);
    _userWinRequirement->createDialogBox(gameType);
    _userWinRequirement->setShowDialogAction();

    auto button = Button::create("Continue1.png", "Continue.png", "", TextureResType::PLIST);
    button->setTitleText(_runtime->gameData->getGameText().find("继续")->second);
    button->setTitleFontName(GAME_FONT_NAME_1);
    button->setTitleFontSize(30);
    button->setTitleColor(Color3B::YELLOW);
    button->setPosition(Vec2(_userWinRequirement->getDialog()->getContentSize().width / 2.0f, 10));
    button->setGlobalZOrder(10);
    button->setScale(0.5f);
    button->runAction(FadeIn::create(0.5f));
    button->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type) {
            case ui::Widget::TouchEventType::BEGAN: MusicPlayer::playMusic("gravebutton"); break;
            case ui::Widget::TouchEventType::ENDED:
                _userWinRequirement->setDelectDialogAction();
                ModernWorld::setPopEnter(true);
                quitScene();
                break;
            default: break;
        }
    });
    _userWinRequirement->getDialog()->addChild(button);
}

void GSGameEndLayer::showFailText() {
    auto brain = Sprite::createWithSpriteFrameName("Brain.png");
    brain->setPosition(_director->getWinSize() / 2.0f);
    brain->setScale(2.0f);
    brain->runAction(RepeatForever::create(Sequence::create(
        MoveBy::create(0.05f, Vec2(10, 0)), MoveBy::create(0.05f, Vec2(-10, 0)), nullptr)));
    this->addChild(brain);

    auto lose =
        Sprite::createWithSpriteFrameName(rand() % 2 == 0 ? "zombieswon.png" : "zombieswon1.png");
    lose->setScale(2.0f);
    lose->setPosition(Vec2(2500, Director::getInstance()->getWinSize().height / 2.0f));
    lose->runAction(RepeatForever::create(Sequence::create(
        MoveBy::create(0.05f, Vec2(10, 0)), MoveBy::create(0.05f, Vec2(-10, 0)), nullptr)));
    lose->runAction(
        Sequence::create(JumpTo::create(1.0f, Director::getInstance()->getWinSize() / 2.0f, 250, 3),
                         DelayTime::create(5), CallFunc::create([this]() {
                             ModernWorld::setPopEnter(true);
                             quitScene();
                         }),
                         nullptr));
    this->addChild(lose);
}

void GSGameEndLayer::rewardThing() {
    ui::Button* moneybag_hi_res;
    moneybag_hi_res = ui::Button::create("moneybag_hi_res.png", "", "", TextureResType::PLIST);

    moneybag_hi_res->setPosition(Vec2(700 + rand() % 1000, 100 + rand() % 700));
    moneybag_hi_res->runAction(
        JumpBy::create(0.5f, Vec2(100 - rand() % 200, 0), 100 + rand() % 100, 1));
    moneybag_hi_res->setName("moneybag_hi_res");
    moneybag_hi_res->setLocalZOrder(2);
    this->addChild(moneybag_hi_res);

    moneybag_hi_res->runAction(RepeatForever::create(Sequence::create(
        TintTo::create(0.3f, 150, 150, 150), TintTo::create(0.3f, 255, 255, 255), nullptr)));
    moneybag_hi_res->addTouchEventListener(
        [this, moneybag_hi_res](Ref* sender, ui::Widget::TouchEventType type) {
            switch (type) {
                case cocos2d::ui::Widget::TouchEventType::BEGAN:
                    MusicPlayer::playMusic("coin");
                    break;
                case cocos2d::ui::Widget::TouchEventType::ENDED:
                    moneybag_hi_res->setEnabled(false);
                    moneybag_hi_res->setBright(true);

                    MusicPlayer::playMusic("moneyfalls");
                    rewardCoin(moneybag_hi_res);
                    break;
                default: break;
            }
        });
}

void GSGameEndLayer::caveLevelNumber() {
    char worldFile[128];
    auto& caveFile = _runtime->userData->getCaveFile();
    auto& userWorldData = _runtime->userData->getUserWorldData();
    snprintf(worldFile, 128, caveFile.systemCaveFileName[caveFile.userCaveFileNumber].c_str(),
             userWorldData.currentLevel + 1);
    _userDataHandler->caveUserData(worldFile, userWorldData.currentLevel + 1);
}

void GSGameEndLayer::carsToCoins() {
    int i = -1;
    for (auto car : CarsGroup) {
        if (!car->getLive()) {
            auto cars = car;
            runAction(Sequence::create(
                DelayTime::create(0.4f * ++i), CallFunc::create([this, cars]() {
                    MusicPlayer::playMusic("coin");
                    cars->getCar()->runAction(Sequence::create(
                        Spawn::create(ScaleTo::create(0.2f, 0), FadeOut::create(0.2f), nullptr),
                        nullptr));
                    cars->getCar()->setVisible(false);
                    coinAction(cars->getCar()->getPosition(), 0, true);
                }),
                nullptr));
        }
    }
}

void GSGameEndLayer::rewardCoin(Button* button) {
    int levelNumber = _levelDataHandler->getLevelNumber();
    LevelData* levelData = _levelDataHandler->readLevelData(levelNumber);
    const int coins = levelData->rewardCoinNumbers / 2;
    const int number = coins + rand() % coins;

    button->runAction(Sequence::create(
        Repeat::create(Sequence::create(MoveBy::create(0.05f, Vec2(5, 5)),
                                        MoveBy::create(0.05f, Vec2(-5, -5)), nullptr),
                       number / 2),
        DelayTime::create(0.5f), FadeOut::create(0.5f),
        CallFunc::create([button]() { button->removeFromParent(); }), nullptr));

    for (int i = 0; i < number; i++) {
        coinAction(button->getPosition() - Vec2(-10, 55), i);

        if (i >= number - 1) {
            this->runAction(Sequence::create(
                DelayTime::create(2.0f), CallFunc::create([=]() {
                    auto audio = MusicPlayer::playMusic("winmusic", 0);
                    MusicPlayer::setMusicVolume(audio);
                    AudioEngine::setFinishCallback(
                        audio, [=](int i, string name) { MusicPlayer::playMusic("lightfill"); });

                    auto AwardRays = Sprite::createWithSpriteFrameName("AwardRays.png");
                    AwardRays->setPosition(_director->getWinSize() / 2.0f);
                    AwardRays->runAction(RepeatForever::create(Spawn::create(
                        RotateBy::create(0.5f, 30), ScaleBy::create(0.5f, 1.5f), nullptr)));
                    AwardRays->setGlobalZOrder(20);
                    this->addChild(AwardRays);

                    auto White = Sprite::createWithSpriteFrameName("White.png");
                    White->setAnchorPoint(Vec2(0, 0));
                    White->setContentSize(_director->getWinSize());
                    White->setOpacity(0);
                    White->setGlobalZOrder(20);
                    this->addChild(White);
                    White->runAction(Sequence::create(
                        DelayTime::create(1.0f), FadeIn::create(7.0f), CallFunc::create([=]() {
                            /* 保存金币数 */
                            auto& userWorldData = _runtime->userData->getUserWorldData();
                            _userDataHandler->caveUserData("COINNUMBERS",
                                                           userWorldData.coinNumbers);

                            ModernWorld::setPopEnter(true);
                            _director->popScene();
                        }),
                        nullptr));
                }),
                nullptr));
        }
    }
}

void GSGameEndLayer::coinAction(const Vec2& position, const int id, const bool big) {
    auto coin = SkeletonAnimation::createWithData(
        _runtime->gameData->getAnimationData().find("coin")->second);
    coin->setPosition(position);
    coin->setScale(0.05f);
    this->addChild(coin);

    auto callFunc = CallFunc::create([=]() {
        MusicPlayer::playMusic("moneyfalls");
        coin->removeFromParent();
        auto& userWorldData = _runtime->userData->getUserWorldData();
        big ? userWorldData.coinNumbers += 10 : userWorldData.coinNumbers += 1;
        informationLayerInformation->updateCoinNumbers();
    });

    auto action = Spawn::create(
        FadeIn::create(0.5f), ScaleTo::create(0.5f, 0.3f),
        JumpBy::create(0.5f, Vec2(150 - rand() % 300, 100 - rand() % 100), rand() % 100 + 200, 1),
        Sequence::create(DelayTime::create(0.25f),
                         CallFunc::create([coin]() { coin->setLocalZOrder(3); }), nullptr),
        nullptr);
    auto action1 =
        Spawn::create(ScaleTo::create(0.2f, 0.5f), FadeOut::create(0.2f), callFunc, nullptr);

    coin->runAction(Sequence::create(DelayTime::create(id * 0.05f), action,
                                     DelayTime::create(0.05f),
                                     MoveTo::create(0.5f, Vec2(1650, -40)), action1, nullptr));
}

void GSGameEndLayer::quitScene() {
    auto layer = LayerColor::create(Color4B(0, 0, 0, 0));
    this->addChild(layer);
    layer->runAction(Sequence::create(FadeIn::create(1.0f), CallFunc::create([=]() {
                                          layer->removeFromParent();
                                          _director->popScene();
                                      }),
                                      nullptr));
}
