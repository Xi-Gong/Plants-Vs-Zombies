/**
 *Copyright (c) 2019 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.4.20
 *Emal: 2117610943@qq.com
 */

#ifndef PEA_H
#define PEA_H

#include "Bullet.h"

class Pea : public Bullet {
  public:
    Pea(Node* node = nullptr);
    ~Pea() = default;

    virtual void setIsFire(const bool isFire);
    virtual void setPeaFireNumbers(const int fireNumbers);
    virtual void addPeaFireNumbers();
    virtual void setTorchwoodTag(const int torchwoodTag);
    virtual bool getIsFire() const;
    virtual int getPeaFireNumbers() const;
    virtual int getTorchwoodTag() const;

  protected:
    virtual void createBullet() override;
    virtual void bulletAndZombiesCollisionDetect() override;
    virtual void createPeaExplode();
    virtual void bulletInit() override;
    virtual void createBulletShadow() override;
    virtual void bulletAttackZombies();
    virtual void fireBulletAttackZombies();

  private:
    void attackZombies();
    float getZombieInExplodeRange(Zombies* zombie);

  protected:
    bool _isFire;              // 是否燃烧
    int _fireNumbers;          // 燃烧次数
    int _torchwoodTag;         // 火炬树桩标记
    string _peaAnimationName;  // 豌豆动画名称
};

#endif  // PEA_H
