/**
 *Copyright (c) 2019 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.4.20
 *Emal: 2117610943@qq.com
 */

#ifndef PEASHOOTER_H
#define PEASHOOTER_H

#include "EmissionPlants.h"

class Zombies;
enum class SoundEffectType;

class PeaShooter : public EmissionPlants {
  public:
    PeaShooter(Node* node = nullptr);
    ~PeaShooter() = default;

    static PeaShooter* create(Node* node = nullptr);
    virtual Sprite* createPlantImage() override;
    virtual void createPlantAnimation() override;
    virtual void determineRelativePositionPlantsAndZombies() override;

  protected:
    virtual void createPea();
    virtual void plantAttack(Zombies* zombie) override;
    virtual void plantEmission(const string& plantAnimation);
    virtual void plantRecovery(const string& plantAnimation);

  protected:
    bool _isCreatePea;
};

#endif  // PEASHOOTER_H
