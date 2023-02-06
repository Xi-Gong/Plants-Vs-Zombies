/**
 *Copyright (c) 2019 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.4.20
 *Emal: 2117610943@qq.com
 */

#ifndef SUNFLOWER_H
#define SUNFLOWER_H

#include "Plants/Plants.h"
#include "Sun.h"

class SunFlower : public Plants {
  public:
    SunFlower(Node* node = nullptr, Node* sunLayer = nullptr);
    ~SunFlower() = default;

    static SunFlower* create(Node* node = nullptr);
    static void stopSun();
    void createRandomSuns();
    void setSunShowTime(const Vec2 time);
    Vec2 getSunShowTime() const;
    virtual Sprite* createPlantImage() override;
    virtual void createPlantAnimation() override;

  private:
    static void sunRecovery(Sun* sun);
    void goodsRecovery();
    void createSuns();
    void createListener();
    void playAnimation();
    void calculateSunShowTime();

  private:
    static int _sunTag;
    Sun* _sun;
    Node* _sunLayer;
    Vec2 _sunShowTime;
    Vec2 _sunShowTime1;
};

#endif  // SUNFLOWER_H
