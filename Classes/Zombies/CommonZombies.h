/**
 *Copyright (c) 2019 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.4.20
 *Emal: 2117610943@qq.com
 */

#ifndef COMMONZOMBIES_H
#define COMMONZOMBIES_H

#include <cocos2d.h>

#include "Zombies.h"

using namespace cocos2d;

class CommonZombies : public Zombies {
  public:
    CommonZombies(Node* node = nullptr);
    ~CommonZombies() = default;
    static CommonZombies* create(Node* node = nullptr);
    virtual void createZombie() override;
    virtual void createPreviewZombie() override;
    virtual void playZombieSoundEffect() override;

  private:
    virtual void zombieInjuredEventUpdate() override;
};

#endif  // COMMONZOMBIES_H
