/**
 *Copyright (c) 2019 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.4.20
 *Emal: 2117610943@qq.com
 */

#ifndef EMISSIONPLANTS_H
#define EMISSIONPLANTS_H

#include "../Plants.h"

class Zombies;
class Bullet;

class EmissionPlants : public Plants {
  public:
    EmissionPlants() : _isChanged(false), _bulletAnimation(nullptr){};
    ~EmissionPlants() = default;

  protected:
    virtual void plantAttack(Zombies* zombie) = 0;

  protected:
    bool _isChanged;           // 是否改变为攻击形态
    Bullet* _bulletAnimation;  // 子弹动画
};

#endif  // EMISSIONPLANTS_H
