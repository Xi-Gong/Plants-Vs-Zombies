/**
 *Copyright (c) 2019 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.4.20
 *Emal: 2117610943@qq.com
 */

#include "SPSBackgroundLayer.h"

SPSBackgroundLayer::SPSBackgroundLayer() :
    _runtime(Runtime::getInstance()), _levelDataHandler(LevelDataHandler::getInstance()),
    _previewZombiesTag(0) {
    _random.seed(_device());
}

bool SPSBackgroundLayer::init() {
    if (!Layer::init()) {
        return false;
    }

    /* 创建背景 */
    createBackGroundEffect();

    setBackgroundImagePosition();

    /* 创建预览僵尸 */
    createPreviewZombie();

    return true;
}

void SPSBackgroundLayer::createBackGroundEffect() { createMordernBackgroundImage(); }

void SPSBackgroundLayer::createMordernBackgroundImage() {
    auto& userWorldData = _runtime->userData->getUserWorldData();
    userWorldData.background = Sprite::createWithSpriteFrameName("background.png");
}

void SPSBackgroundLayer::createFireEffect(Sprite* name) {
    auto fire = ParticleFire::create();
    fire->setPosition(Vec2(1900, 30));
    name->addChild(fire);

    auto fire1 = ParticleFire::create();
    fire1->setPosition(Vec2(1820, 1000));
    name->addChild(fire1);
}

void SPSBackgroundLayer::createPreviewZombie() {
    srand(time(nullptr));
    createMordernPreviewZombies();
    sortZombiesPosition();
}

void SPSBackgroundLayer::createMordernPreviewZombies() {
    uniform_int_distribution<unsigned> n(0, 2);
    uniform_int_distribution<unsigned> n1(0, 550);
    uniform_int_distribution<unsigned> n2(0, 650);

    int levelNumber = _levelDataHandler->getLevelNumber();
    LevelData* levelData = _levelDataHandler->readLevelData(levelNumber);
    int zombiesTypeSize = levelData->zombiesType.size();

    for (int i = 0; i < zombiesTypeSize; ++i) {
        int k;
        _previewZombies.size() < 15 ? k = n(_random) + 1 : k = 1;
        for (int j = 0; j < k; ++j) {
            auto zombies = createDifferentZombies(i);
            zombies->setZombiePosition(getPreviewZombiesPosition(n1, n2));
            zombies->setZombieTag(_previewZombiesTag++);
            zombies->createPreviewZombie();

            PreviewZombies previewzombies;
            previewzombies.animation = zombies->getZombieAnimation();
            previewzombies.position_y = previewzombies.animation->getPositionY();
            previewzombies.position_x = previewzombies.animation->getPositionX();
            _previewZombies.push_back(previewzombies);
        }
    }
}

void SPSBackgroundLayer::setBackgroundImagePosition() {
    auto& background = _runtime->userData->getUserWorldData().background;
    if (background != nullptr) {
        background->setAnchorPoint(Point(0, 0));
        background->setContentSize(Size(2930, 1081));
        this->addChild(background, 0, "previewBackgroundImage");
    }
}

void SPSBackgroundLayer::sortZombiesPosition() {
    std::sort(_previewZombies.begin(), _previewZombies.end(), cmp);

    int i = 0;
    for (auto& pre : _previewZombies) {
        pre.animation->setLocalZOrder(110 + i++);
        pre.animation->setOpacity(255);
        pre.animation->getChildByName("shadow")->setOpacity(255);
    }
}

Vec2 SPSBackgroundLayer::getPreviewZombiesPosition(UID& n1, UID& n2) {
    Vec2 vec2;
    bool can;
    int x, y;
    do {
        can = false;
        x = 2050 + n1(_random);
        y = n2(_random) + 80;
        for (auto p : _previewZombies) {
            if (sqrt(pow(p.position_x - x, 2) + pow(p.position_y - y, 2)) < 100) {
                can = true;
                break;
            }
        }
    } while (can);

    vec2.x = x;
    vec2.y = y;

    return vec2;
}

bool SPSBackgroundLayer::cmp(PreviewZombies& a, PreviewZombies& b) {
    return a.position_y > b.position_y;
}

Zombies* SPSBackgroundLayer::createDifferentZombies(const int& id) {
    int levelNumber = _levelDataHandler->getLevelNumber();
    LevelData* levelData = _levelDataHandler->readLevelData(levelNumber);

    Zombies* zombies;
    switch (static_cast<ZombiesType>(levelData->zombiesType.at(id))) {
        case ZombiesType::CommonZombies: zombies = CommonZombies::create(this); break;
        case ZombiesType::ConeZombies: zombies = ConeZombies::create(this); break;
        case ZombiesType::BucketZombies: zombies = BucketZombies::create(this); break;
        case ZombiesType::CommonFlagZombies: zombies = CommonFlagZombies::create(this); break;
        default: break;
    }
    return zombies;
}
