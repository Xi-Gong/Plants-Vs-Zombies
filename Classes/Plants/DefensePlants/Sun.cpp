/**
 *Copyright (c) 2019 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.4.20
 *Emal: 2117610943@qq.com
 */

#include "Sun.h"

#include "Scenes/GameScene/GSData.h"

Sun::Sun(Node* node) :
    _node(node), _sunTag(0), _sun(nullptr), _isEnable(true), _runtime(Runtime::getInstance()) {}

void Sun::createSuns() {
    auto& animationData = _runtime->gameData->getAnimationData();
    _sun = SkeletonAnimation::createWithData(animationData.find("Sun")->second);
    _sun->addAnimation(0, "Sun_rotate", true);
    _sun->setPosition(_position);
    _sun->runAction(Sequence::create(
        Spawn::create(ScaleTo::create(0.5f, 1.2f),
                      JumpBy::create(0.6f, Vec2(rand() % 120 - 60, 0), rand() % 100 + 100, 1),
                      nullptr),
        DelayTime::create(14), FadeOut::create(0.5f), DelayTime::create(5.0f),
        CallFunc::create([this]() { _sun->setVisible(false); }), nullptr));
    _node->addChild(_sun);
}

void Sun::setSunTag(const int& sunTag) { _sunTag = sunTag; }

void Sun::setPosition(const Vec2& position) { _position = position; }

void Sun::setEnable(bool isUsed) { _isEnable = isUsed; }

int Sun::getSunTag() const { return _sunTag; }

bool Sun::getEnable() const { return _isEnable; }

void Sun::releaseSun() const { _sun->removeFromParent(); }

SkeletonAnimation* Sun::getSun() { return _sun; }

void Sun::deleteSun(list<Sun*>::iterator& sun) {
    if (!(*sun)->getSun()->isVisible()) {
        (*sun)->releaseSun();
        delete *sun;
        *sun = nullptr;
        SunsGroup.erase(sun++);
    } else {
        ++sun;
    }
}
