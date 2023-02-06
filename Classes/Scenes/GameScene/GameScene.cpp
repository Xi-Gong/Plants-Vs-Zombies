/**
 *Copyright (c) 2019 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.4.20
 *Emal: 2117610943@qq.com
 */

#include "GameScene.h"

#include "Based/Car.h"
#include "Based/Coin.h"
#include "Based/MusicPlayer.h"
#include "GSAnimationLayer.h"
#include "GSBackgroundLayer.h"
#include "GSButtonLayer.h"
#include "GSControlLayer.h"
#include "GSData.h"
#include "GSInformationLayer.h"
#include "GSMacro.h"
#include "GSPauseLayer.h"
#include "GSPauseQuitLayer.h"
#include "Plants/DefensePlants/Sun.h"
#include "Plants/EmissonPlants/Bullet/Bullet.h"
#include "Zombies/Zombies.h"

GameScene::GameScene() : _runtime(Runtime::getInstance()), _director(Director::getInstance()) {}

GameScene::~GameScene() {
    DELETE_MAP_GROUP(PlantsGroup);
    DELETE_LIST_GROUP(ZombiesGroup);
    DELETE_LIST_GROUP(SunsGroup);
    DELETE_LIST_GROUP(BulletGroup);
    DELETE_LIST_GROUP(CarsGroup);
    DELETE_LIST_GROUP(CoinsGroup);

    Zombies::setZombiesNumbers(0);
    Zombies::zombiesWinOrLoseInit();

    _director->getEventDispatcher()->removeCustomEventListeners(GLViewImpl::EVENT_WINDOW_UNFOCUSED);
}

bool GameScene::init() {
    if (!Scene::init()) {
        return false;
    }

    controlPlayMusic();
    backgroundLayer();   // 背景层
    informationLayer();  // 信息层
    buttonLayer();       // 按钮层
    controlLayer();      // 控制层
    animationLayer();    // 动画层

    pauseGame();

    return true;
}

void GameScene::controlPlayMusic() {
    auto& userWorldData = _runtime->userData->getUserWorldData();
    if (userWorldData.currentLevel == 5) {
        MusicPlayer::changeBackgroundMusic("secretlabs", true);
    } else {
        MusicPlayer::changeBackgroundMusic("KitanaiSekai", true);
    }
}

void GameScene::backgroundLayer() {
    backgroundLayerInformation = GSBackgroundLayer::create();
    backgroundLayerInformation->addLayer(this, 0, "backgroundLayer");
}

void GameScene::controlLayer() {
    controlLayerInformation = GSControlLayer::create();
    controlLayerInformation->addLayer(this, 1, "controlLayer");
}

void GameScene::animationLayer() {
    animationLayerInformation = GSAnimationLayer::create(this);
    animationLayerInformation->addLayer(this, 2, "animationLayer");
}

void GameScene::informationLayer() {
    informationLayerInformation = GSInformationLayer::create();
    informationLayerInformation->addLayer(this, 3, "informationLayer");
}

void GameScene::buttonLayer() {
    buttonLayerInformation = GSButtonLayer::create();
    buttonLayerInformation->addLayer(this, 4, "buttonLayer");
}

void GameScene::pauseGame() {
    schedule([this](float) { _runtime->checkAnimationInterval(); }, 1.f, "FPS");

    _director->getEventDispatcher()->addCustomEventListener(
        GLViewImpl::EVENT_WINDOW_UNFOCUSED, [&](EventCustom* evt) {
            if (!GSPauseQuitLayer::getPauseNumbers()) {
                MusicPlayer::playMusic("pause");
                GSPauseQuitLayer::pauseLayer();
                _director->getRunningScene()->addChild(GSPauseLayer::addLayer(), 10);
            }
        });
}
