#ifndef CAR_H
#define CAR_H

#include <cocos2d.h>
#include <spine/spine-cocos2dx.h>

/**
 *Copyright (c) 2019 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.4.20
 *Emal: 2117610943@qq.com
 */

#include "Based/Runtime.h"

using namespace spine;
using namespace cocos2d;

class Zombies;

class Car : public Node {
  public:
    Car(Node* node = nullptr);
    ~Car() = default;

    static Car* create(Node* node = nullptr);
    static void deleteCar(list<Car*>::iterator& car);
    void showCar();
    void setPosition(const Vec2& position);
    void setCarTag(const int tag);
    void setParent(Node* node);
    void setScale(const float& scale);
    void setLive(bool isLive);
    bool getLive() const;
    int getCarTag() const;
    Sprite* getCar() const;
    void createCarListener();
    void carStartUp();

  private:
    void createCarShadow();
    void createAppearSpecialEffect();
    bool getZombieIsSameLineWithCar(Zombies* zombie) const;
    bool getzombieIsEncounterCar(Zombies* zombie) const;
    int getZOrder(const float& pos_y) const;

  private:
    Runtime* _runtime;

    Sprite* _carImage;  // 小车图片
    Vec2 _position;     // 位置
    bool _isLive;       // 是否激活
    int _tag;           // 标记
    int _carState;      // 小车状态
    float _scale;       // 大小
    Node* _node;        // 父节点
};

#endif  // CAR_H
