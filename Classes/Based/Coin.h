/**
 *Copyright (c) 2019 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.4.20
 *Emal: 2117610943@qq.com
 */

#ifndef COIN_H
#define COIN_H

#include <cocos2d.h>
#include <spine/spine-cocos2dx.h>

#include "Runtime.h"

using namespace cocos2d;
using namespace spine;

class Coin {
  public:
    Coin(Node* node = nullptr);
    ~Coin() = default;

    void createCoin();
    void setPosition(const Vec2& position);
    void setEnable(bool isUsed);
    void setCoinLocalZOrder(const int loaclZOrder);
    SkeletonAnimation* getCoin();
    bool getEnable() const;
    void releaseCoin() const;
    static void coinRecoveryAction(Coin* coin);
    static void deleteCoin(list<Coin*>::iterator& coin);

  private:
    void coinInit();

  private:
    Runtime* _runtime;

    bool _isEnable;
    bool _canDelete;
    int _loaclZOrder;
    Vec2 _position;
    SkeletonAnimation* _coin;
    Node* _node;
};

#endif  // COIN_H
