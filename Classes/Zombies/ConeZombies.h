/**
 *Copyright (c) 2019 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.4.20
 *Emal: 2117610943@qq.com
 */

#ifndef CONEZOMBIES_H
#define CONEZOMBIES_H

#include <cocos2d.h>

#include "Zombies.h"

using namespace cocos2d;

class ConeZombies : public Zombies {
  public:
    ConeZombies(Node* node = nullptr);
    ~ConeZombies() = default;
    static ConeZombies* create(Node* node = nullptr);
    virtual void createZombie() override;
    virtual void createPreviewZombie() override;
    virtual void playZombieSoundEffect() override;

  private:
    virtual void zombieInjuredEventUpdate() override;
    virtual void setZombieHeadShieldThirdInjure(const string& oldName,
                                                const string& newName) override;
};

#endif  // CONEZOMBIES_H
