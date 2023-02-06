/**
 *Copyright (c) 2019 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.4.20
 *Emal: 2117610943@qq.com
 */

#ifndef COMMONFLAGZOMBIES_H
#define COMMONFLAGZOMBIES_H

#include "CommonZombies.h"

class CommonFlagZombies : public CommonZombies {
  public:
    CommonFlagZombies(Node* node = nullptr);
    ~CommonFlagZombies() = default;
    static CommonFlagZombies* create(Node* node = nullptr);
    virtual void createZombie() override;
    virtual void createPreviewZombie() override;
    virtual void playZombieSoundEffect() override;
};

#endif  // COMMONFLAGZOMBIES_H
