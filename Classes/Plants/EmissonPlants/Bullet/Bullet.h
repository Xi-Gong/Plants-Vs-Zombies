/**
 *Copyright (c) 2019 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.4.20
 *Emal: 2117610943@qq.com
 */

#ifndef BULLET_H
#define BULLET_H

#include <cocos2d.h>
#include <spine/spine-cocos2dx.h>

#include "Based/Runtime.h"

using namespace spine;
using namespace cocos2d;

class Zombies;

enum class BulletType { None = 0, Pea, FirePea, Cabbage, AcidLemonBullet, CitronBullet };

enum class SoundEffectType { kernelpult = 0, plastichit, shieldhit, firepea };

class Bullet {
  public:
    Bullet();
    virtual ~Bullet() = default;

    virtual void createBullet() = 0;
    virtual void bulletAndZombiesCollisionDetect() = 0;
    virtual SkeletonAnimation* getBulletAnimation() const;
    virtual void setBulletPosition(const Vec2& position);
    virtual void setBulletName(const string& name);
    virtual void setBulletIsUsed(const bool isUsed);
    virtual void setBulletAttackPower(const float attack);
    virtual void setBulletOpacity(GLubyte opacity);
    virtual void setBulletOpacity();
    virtual bool getBulletIsUsed() const;
    virtual int getBulletAttackPower() const;
    virtual Vec2 getBulletPosition() const;
    virtual float getBulletPositionX() const;
    virtual float getBulletPositionY() const;
    virtual BulletType getBulletType() const;
    virtual bool getBulletIsSameLineWithZombie(Zombies* zombie);
    virtual bool getBulletIsEncounterWithZombie(Zombies* zombie);
    virtual string& getBulletName();
    virtual bool getBulletVisible() const;
    virtual void bulletAttackHurtZombies(Zombies* zombie);

    static void bulletDeleteUpdate(list<Bullet*>::iterator& bullet);
    static void playCollisionSoundEffect(SoundEffectType soundEffect);
    static void playCollisionSoundEffect(const std::string& MusicName);
    static void selectSoundEffect(const int body, const int head);
    static void selectSoundEffect(const int head);

  protected:
    virtual void bulletInit() = 0;
    virtual void createBulletShadow() = 0;
    virtual float getZOrder(const int& positionY) const;

  private:
    void releaseBullet() const;

  protected:
    Runtime* _runtime;  // 全局单例

    SkeletonAnimation* _bulletAnimation;  // 动画
    float _attack;                        // 攻击力
    bool _isUsed;                         // 是否使用
    Node* _node;                          // 父节点
    Vec2 _position;                       // 位置
    string _bulletName;                   // 豌豆名字
    BulletType _bulletType;               // 子弹类型
};

#endif  // BULLET_H
