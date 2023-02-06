/**
 *Copyright (c) 2019 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.4.20
 *Emal: 2117610943@qq.com
 */

#include "GSBackgroundLayer.h"

#include "GSData.h"

GSBackgroundLayer::GSBackgroundLayer() : _runtime(Runtime::getInstance()) {}

void GSBackgroundLayer::backgroundRunAction() {
    Vec2 begin[4] = {Vec2(2, 2), Vec2(-2, 2), Vec2(2, -2), Vec2(-2, -2)};
    auto move = MoveBy::create(0.1f, begin[rand() % 4]);
    backgroundLayerInformation->runAction(
        Sequence::create(move, move->reverse(), move, move->reverse(), nullptr));
}

bool GSBackgroundLayer::init() {
    if (!Layer::init()) {
        return false;
    }

    createBackGroundEffect();

    setBackgroundImagePosition();

    return true;
}

void GSBackgroundLayer::setBackgroundImagePosition() {
    auto userWorldData = _runtime->userData->getUserWorldData();
    auto background = userWorldData.background;
    if (background != nullptr) {
        background->setAnchorPoint(Point(0, 0));
        background->setContentSize(Size(2930, 1081));
        background->setPosition(Vec2(-220, 0));
        this->addChild(background);
    }
}
