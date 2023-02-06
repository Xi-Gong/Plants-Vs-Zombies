/**
 *Copyright (c) 2019 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.4.20
 *Emal: 2117610943@qq.com
 */

#ifndef WALLNUT_H
#define WALLNUT_H

#include "Plants/Plants.h"

class WallNut : public Plants {
  public:
    WallNut(Node* node = nullptr);
    ~WallNut() = default;

    static WallNut* create(Node* node = nullptr);
    virtual Sprite* createPlantImage() override;
    virtual void createPlantAnimation() override;

  private:
    virtual void checkPlantHealthPoint() override;

  private:
    int _skinId;
};

#endif  // WALLNUT_H
