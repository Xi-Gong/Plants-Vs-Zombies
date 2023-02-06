/**
 *Copyright (c) 2019 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.4.20
 *Emal: 2117610943@qq.com
 */

#include "Bullet.h"

#include "Based/MusicPlayer.h"
#include "Scenes/GameScene/GSData.h"
#include "Zombies/Zombies.h"

Bullet::Bullet() :
    _node(nullptr), _attack(0), _isUsed(false), _bulletType(BulletType::None),
    _position(Vec2::ZERO), _runtime(Runtime::getInstance()) {
    srand(time(nullptr));
}

void Bullet::bulletDeleteUpdate(list<Bullet*>::iterator& bullet) {
    if (!(*bullet)->getBulletVisible()) {
        (*bullet)->releaseBullet();
        delete *bullet;
        *bullet = nullptr;
        BulletGroup.erase(bullet++);
    } else {
        ++bullet;
    }
}

SkeletonAnimation* Bullet::getBulletAnimation() const { return _bulletAnimation; }

void Bullet::setBulletPosition(const Vec2& position) { _position = position; }

void Bullet::setBulletName(const string& name) { _bulletName = name; }

void Bullet::setBulletIsUsed(const bool isUsed) { _isUsed = isUsed; }

void Bullet::setBulletAttackPower(const float attack) { _attack = attack; }

void Bullet::setBulletOpacity(GLubyte opacity) {
    _bulletAnimation->setOpacity(opacity);
    _bulletAnimation->getChildByName("shadow")->setOpacity(opacity);
}

void Bullet::setBulletOpacity() {
    _bulletAnimation->setOpacity(0);
    _bulletAnimation->getChildByName("shadow")->setOpacity(0);
}

bool Bullet::getBulletIsUsed() const { return _isUsed; }

int Bullet::getBulletAttackPower() const { return _attack; }

void Bullet::bulletAttackHurtZombies(Zombies* zombie) {
    if (zombie->getZombieCurrentBodyShieldVolume() < _attack) /* 如果当前身体护盾血量小于爆炸伤害 */
    {
        if (zombie->getZombieCurrentBodyShieldVolume() +
                zombie->getZombieCurrentHeadShieldVolume() <
            _attack) /* 如果当前身体护盾加头部护盾血量小于爆炸伤害 */
        {
            if (zombie->getZombieCurrentBodyShieldVolume() +
                    zombie->getZombieCurrentHeadShieldVolume() +
                    zombie->getZombieCurrentBloodVolume() <=
                _attack) /* 如果僵尸所有血量小于爆炸伤害（僵尸死亡） */
            {
                zombie->setZombieDeath(true);
            } else {
                /* 计算僵尸本体血量 */
                zombie->setZombieCurrentBloodVolume(zombie->getZombieCurrentBodyShieldVolume() +
                                                    zombie->getZombieCurrentHeadShieldVolume() +
                                                    zombie->getZombieCurrentBloodVolume() -
                                                    _attack);
                zombie->setZombieCurrentHeadShieldVolume(0);
                zombie->setZombieCurrentBodyShieldVolume(0);
            }
        } else {
            /* 计算僵尸护盾剩于血量 */
            zombie->setZombieCurrentHeadShieldVolume(zombie->getZombieCurrentBodyShieldVolume() +
                                                     zombie->getZombieCurrentHeadShieldVolume() -
                                                     _attack);
            zombie->setZombieCurrentBodyShieldVolume(0);
        }
    } else {
        zombie->setZombieCurrentBodyShieldVolume(zombie->getZombieCurrentBodyShieldVolume() -
                                                 _attack);
    }
}

string& Bullet::getBulletName() { return _bulletName; }

float Bullet::getZOrder(const int& positionY) const {
    const int pos[5] = {675, 537, 399, 261, 123};
    for (int i = 0; i < 5; i++) {
        if (pos[i] == positionY) {
            return i * 20 + 12;
        }
    }
    return 0;
}

void Bullet::releaseBullet() const { _bulletAnimation->removeFromParent(); }

Vec2 Bullet::getBulletPosition() const { return _bulletAnimation->getPosition(); }

float Bullet::getBulletPositionX() const { return _bulletAnimation->getPositionX(); }

float Bullet::getBulletPositionY() const { return _bulletAnimation->getPositionY(); }

BulletType Bullet::getBulletType() const { return _bulletType; }

bool Bullet::getBulletIsSameLineWithZombie(Zombies* zombie) {
    return fabs(_bulletAnimation->getPositionY() - 83 - zombie->getZombiePositionY()) <= 10 ? true :
                                                                                              false;
}

bool Bullet::getBulletIsEncounterWithZombie(Zombies* zombie) {
    return fabs(_bulletAnimation->getPositionX() - zombie->getZombiePositionX()) <= 25 ? true :
                                                                                         false;
}

bool Bullet::getBulletVisible() const { return _bulletAnimation->isVisible(); }

void Bullet::selectSoundEffect(const int body, const int head) {
    if (body) {
        playCollisionSoundEffect(SoundEffectType::shieldhit);
    } else {
        selectSoundEffect(head);
    }
}

void Bullet::selectSoundEffect(const int head) {
    switch (head) {
        case 0: playCollisionSoundEffect(SoundEffectType::kernelpult); break;
        case 1: playCollisionSoundEffect(SoundEffectType::shieldhit); break;
        case 2: playCollisionSoundEffect(SoundEffectType::plastichit); break;
    }
}

void Bullet::playCollisionSoundEffect(SoundEffectType soundEffect) {
    switch (soundEffect) {
        case SoundEffectType::kernelpult:
            rand() % 2 ? playCollisionSoundEffect("kernelpult") :
                         playCollisionSoundEffect("kernelpult2");
            break;
        case SoundEffectType::shieldhit:
            rand() % 2 ? playCollisionSoundEffect("shieldhit") :
                         playCollisionSoundEffect("shieldhit2");
            break;
        case SoundEffectType::plastichit:
            rand() % 2 ? playCollisionSoundEffect("plastichit") :
                         playCollisionSoundEffect("plastichit2");
            break;
        case SoundEffectType::firepea: playCollisionSoundEffect("firepea"); break;
    }
}

void Bullet::playCollisionSoundEffect(const std::string& MusicName) {
    MusicPlayer::playMusic(MusicName);
}
