/**
 *Copyright (c) 2019 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.4.20
 *Emal: 2117610943@qq.com
 */

#include "GSAnimationLayer.h"

#include "Based/Car.h"
#include "Based/Coin.h"
#include "Based/MusicPlayer.h"
#include "GSButtonLayer.h"
#include "GSControlLayer.h"
#include "GSData.h"
#include "GSMacro.h"
#include "Plants/Plants-Files.h"
#include "Zombies/Zombies-Files.h"
#include "ZombiesAppearControl.h"

GSAnimationLayer::GSAnimationLayer(Node* node) :
    _gameScene(node), _runtime(Runtime::getInstance()),
    _levelDataHandler(LevelDataHandler::getInstance()), _randomSuns(nullptr), _sunLayer(nullptr) {
    _random.seed(_device());
}

GSAnimationLayer::~GSAnimationLayer() {
    if (_randomSuns) {
        delete _randomSuns;
    }
}

GSAnimationLayer* GSAnimationLayer::create(Node* node) {
    GSAnimationLayer* object = new (std::nothrow) GSAnimationLayer(node);
    if (object && object->init()) {
        object->autorelease();
        return object;
    }
    CC_SAFE_DELETE(object);
    return nullptr;
}

void GSAnimationLayer::stopRandomSun() { _sunLayer->stopAllActions(); }

bool GSAnimationLayer::init() {
    if (!Layer::init()) {
        return false;
    }

    createSunLayer();
    createRandomSuns();
    showCars();

    schedule([&](float delta) { gameMainLoop(delta); }, "gameMainLoop");
    schedule(
        [&](float) {
            sunsDeleteUpdate();
            coinDeleteUpdate();
        },
        2.0f, "sunDeleteUpdate");

    return true;
}

void GSAnimationLayer::plantPlants() {
    MusicPlayer::playMusic(rand() % 2 == 0 ? "plant2" : "plant");

    auto plants = createDifferentPlants(buttonLayerInformation->mouseSelectImage->selectPlantsId);
    plants->setPlantPosition(ROW_COLUMN_TO_POSITION(controlLayerInformation->_plantsPosition));
    plants->setPlantLocalZOrder(SET_ANIMATION_Z_ORDER(controlLayerInformation->_plantsPosition));
    plants->setPlantRowAndColumn(controlLayerInformation->_plantsPosition);
    plants->setPlantTag(SET_TAG(controlLayerInformation->_plantsPosition));
    plants->createPlantAnimation();

    PlantsGroup.insert(
        pair<int, Plants*>(SET_TAG(controlLayerInformation->_plantsPosition), plants));
}

Plants* GSAnimationLayer::createDifferentPlants(PlantsType plantsType) {
    Plants* plants = nullptr;
    switch (plantsType) {
        case PlantsType::SunFlower: plants = new SunFlower(this, _sunLayer); break;
        case PlantsType::PeaShooter: plants = new PeaShooter(this); break;
        case PlantsType::WallNut: plants = new WallNut(this); break;
        default: break;
    }
    return plants;
}

void GSAnimationLayer::deletePlants() {
    auto multimap_iter = PlantsGroup.equal_range(SET_TAG(controlLayerInformation->_plantsPosition));
    for (auto plant = multimap_iter.first; plant != multimap_iter.second; ++plant) {
        plant->second->setPlantHealthPoint(0);
        plant->second->setPlantVisible(false);
        plant->second->getPlantAnimation()->stopAllActions();
    }

    controlLayerInformation->_gameMapInformation
        ->plantsMap[static_cast<int>(controlLayerInformation->_plantsPosition.y)]
                   [static_cast<int>(controlLayerInformation->_plantsPosition.x)] = NO_PLANTS;
}

Zombies* GSAnimationLayer::createDifferentZombies(ZombiesType zombiesType) {
    Zombies* zombies = nullptr;
    switch (zombiesType) {
        case ZombiesType::CommonZombies: zombies = new CommonZombies(this); break;
        case ZombiesType::ConeZombies: zombies = new ConeZombies(this); break;
        case ZombiesType::BucketZombies: zombies = new BucketZombies(this); break;
        case ZombiesType::CommonFlagZombies: zombies = new CommonFlagZombies(this); break;
        default: break;
    }
    return zombies;
}

void GSAnimationLayer::createZombies() {
    uniform_int_distribution<unsigned> number(0, 500);
    auto zombies = createDifferentZombies(static_cast<ZombiesType>(
        controlLayerInformation->_zombiesAppearControl->createDifferentTypeZombies(
            controlLayerInformation->_zombiesAppearControl->getZombiesAppearFrequency())));
    zombies->setZombiePosition(
        Vec2(1780 + number(_random),
             controlLayerInformation->_zombiesAppearControl->getEqualProbabilityForRow()));
    zombies->createZombie();
    ZombiesGroup.push_back(zombies);
    Zombies::zombiesNumbersChange("++");
}

void GSAnimationLayer::createZombiesOnSurvival() {
    uniform_int_distribution<unsigned> number(0, 500);
    auto zombies = createDifferentZombies(static_cast<ZombiesType>(
        controlLayerInformation->_zombiesAppearControl->createDifferentTypeZombies()));
    zombies->setZombiePosition(
        Vec2(1780 + number(_random),
             controlLayerInformation->_zombiesAppearControl->getEqualProbabilityForRow()));
    zombies->createZombie();
    ZombiesGroup.push_back(zombies);
    Zombies::zombiesNumbersChange("++");
}

Layer* GSAnimationLayer::getSunLayer() const { return _sunLayer; }

GSAnimationLayer* GSAnimationLayer::getAnimationLayer() { return this; }

void GSAnimationLayer::createSunLayer() {
    _sunLayer = Layer::create();
    _gameScene->addChild(_sunLayer, 6, "sunLayer");
}

void GSAnimationLayer::createRandomSuns() {
    // ? 条件......
    auto& userWorldData = _runtime->userData->getUserWorldData();
    auto level = userWorldData.currentLevel;
    if (level != 36 && level != 50 && level != 52) {
        _randomSuns = new SunFlower(this, _sunLayer);
        _randomSuns->createRandomSuns();
    }
}

void GSAnimationLayer::showCars() {
    if (!_runtime->userData->getIsReadFileLevelData()) {
        const int carpositions[5] = {180, 318, 456, 594, 732};
        for (int i = 0; i < 5; i++) {
            this->runAction(Sequence::create(DelayTime::create(0.5f + 0.1 * i),
                                             CallFunc::create([=]() {
                                                 MusicPlayer::playMusic("plastichit2");

                                                 auto car = new Car(this);
                                                 car->setPosition(Vec2(455, carpositions[i]));
                                                 car->showCar();

                                                 CarsGroup.push_back(car);
                                             }),
                                             nullptr));
        }
    }
}

void GSAnimationLayer::gameMainLoop(float delta) {
    zombiesEventUpdate(delta); /* 僵尸事件更新 */
    plantsEventUpdate();       /* 植物事件更新 */
    bulletEventUpdate();       /* 子弹事件更新 */
    carsEventUpdate();         /* 小车事件更新 */
}

void GSAnimationLayer::zombiesEventUpdate(float delta) {
    for (auto zombie = ZombiesGroup.begin(); zombie != ZombiesGroup.end();) {
        (*zombie)->setZombieMove(delta);
        (*zombie)->zombieInjuredEventUpdate();
        (*zombie)->playZombieSoundEffect();
        Zombies::judgeZombieWin(zombie);
        Zombies::zombiesDeleteUpdate(zombie);
    }
}

void GSAnimationLayer::plantsEventUpdate() {
    for (auto plant = PlantsGroup.begin(); plant != PlantsGroup.end(); /*++plant*/) {
        plant->second->determineRelativePositionPlantsAndZombies();
        plant->second->checkPlantHealthPoint();

        plantsDeleteUpdate(plant);
    }
}

void GSAnimationLayer::plantsDeleteUpdate(map<int, Plants*>::iterator& plant) {
    if (!plant->second->getPlantVisible()) /* 植物死亡 */
    {
        if (!plant->second->getPlantIsCanDelete()[0]) {
            plant->second->getPlantIsCanDelete()[0] = true;
            GSControlLayer::setPlantMapCanPlant(plant->second->getPlantColumn(),
                                                plant->second->getPlantRow());

            auto plants = plant;
            plant->second->getPlantAnimation()->runAction(Sequence::create(
                DelayTime::create(4.0f),
                CallFunc::create([plants]() { plants->second->getPlantIsCanDelete()[1] = true; }),
                nullptr));
        }
        if (plant->second->getPlantIsCanDelete()[1]) {
            plant->second->getPlantAnimation()->removeFromParent();
            delete plant->second;
            plant->second = nullptr;
            PlantsGroup.erase(plant++);
        } else {
            ++plant;
        }
    } else {
        ++plant;
    }
}

void GSAnimationLayer::bulletEventUpdate() {
    for (auto bullet = BulletGroup.begin(); bullet != BulletGroup.end();) {
        (*bullet)->bulletAndZombiesCollisionDetect();

        Bullet::bulletDeleteUpdate(bullet);
    }
}

void GSAnimationLayer::sunsDeleteUpdate() {
    for (auto sun = SunsGroup.begin(); sun != SunsGroup.end();) {
        Sun::deleteSun(sun);
    }
}

void GSAnimationLayer::coinDeleteUpdate() {
    for (auto coin = CoinsGroup.begin(); coin != CoinsGroup.end();) {
        Coin::deleteCoin(coin);
    }
}

void GSAnimationLayer::carsEventUpdate() {
    for (auto car = CarsGroup.begin(); car != CarsGroup.end();) {
        (*car)->createCarListener();
        (*car)->deleteCar(car);
    }
}
