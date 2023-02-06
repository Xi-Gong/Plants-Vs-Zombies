/**
 *Copyright (c) 2019 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.4.20
 *Emal: 2117610943@qq.com
 */

#include "Coin.h"

#include "MusicPlayer.h"
#include "Scenes/GameScene/GSData.h"
#include "Scenes/GameScene/GSInformationLayer.h"

Coin::Coin(Node* node) :
    _node(node), _loaclZOrder(0), _coin(nullptr), _isEnable(true),
    _runtime(Runtime::getInstance()) {}

void Coin::createCoin() { coinInit(); }

void Coin::setPosition(const Vec2& position) { _position = position; }

void Coin::setEnable(bool isUsed) { _isEnable = isUsed; }

void Coin::setCoinLocalZOrder(const int loaclZOrder) { _loaclZOrder = loaclZOrder; }

SkeletonAnimation* Coin::getCoin() { return _coin; }

bool Coin::getEnable() const { return _isEnable; }

void Coin::releaseCoin() const { _coin->removeFromParent(); }

// static method
void Coin::coinRecoveryAction(Coin* coin) {
    auto temporary = coin;
    coin->setEnable(false);
    coin->getCoin()->stopAllActions();

    coin->getCoin()->runAction(Sequence::create(
        MoveTo::create(0.5f, Vec2(1650, -40)),
        Spawn::create(ScaleTo::create(0.2f, 0.3f), FadeOut::create(0.2f),
                      CallFunc::create([temporary]() { temporary->getCoin()->setGlobalZOrder(1); }),
                      nullptr),
        CallFunc::create([=]() {
            auto& userWorldData = Runtime::getInstance()->userData->getUserWorldData();
            userWorldData.coinNumbers += 1;
            informationLayerInformation->updateCoinNumbers();
            MusicPlayer::playMusic("moneyfalls");
        }),
        DelayTime::create(5.0f),
        CallFunc::create([temporary]() { temporary->getCoin()->setVisible(false); }), nullptr));

    MusicPlayer::playMusic("coin");
}

// static method
void Coin::deleteCoin(list<Coin*>::iterator& coin) {
    if (!(*coin)->getCoin()->isVisible()) {
        (*coin)->releaseCoin();
        delete *coin;
        *coin = nullptr;
        CoinsGroup.erase(coin++);
    } else {
        ++coin;
    }
}

void Coin::coinInit() {
    _coin = SkeletonAnimation::createWithData(
        _runtime->gameData->getAnimationData().find("coin")->second);
    _coin->addAnimation(0, "rotate", true);
    _coin->setScale(0.05f);
    _coin->setLocalZOrder(_loaclZOrder);
    _coin->setPosition(_position);
    _node->addChild(_coin);
    _coin->runAction(Spawn::create(
        FadeIn::create(0.5f), ScaleTo::create(0.5f, 0.3f),
        JumpBy::create(0.5f, Vec2(150 - rand() % 300, 100 - rand() % 100), rand() % 100 + 200, 1),
        Sequence::create(DelayTime::create(0.25f), nullptr), nullptr));
    _coin->runAction(Sequence::create(
        DelayTime::create(15.f), CallFunc::create([=]() { _coin->setVisible(false); }), nullptr));

    MusicPlayer::playMusic("moneyfalls");
}
