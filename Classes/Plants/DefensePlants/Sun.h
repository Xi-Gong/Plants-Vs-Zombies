/**
 *Copyright (c) 2019 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.4.20
 *Emal: 2117610943@qq.com
 */

#ifndef SUN_H
#define SUN_H

#include <cocos2d.h>
#include <spine/spine-cocos2dx.h>
#include <spine/spine.h>

#include <list>

#include "Based/Runtime.h"

using namespace cocos2d;
using namespace spine;

using std::list;

class Sun {
  public:
    Sun(Node* node = nullptr);
    ~Sun() = default;

    void createSuns();
    void setSunTag(const int& sunTag);
    void setPosition(const Vec2& position);
    void setEnable(bool isUsed);
    int getSunTag() const;
    bool getEnable() const;
    void releaseSun() const;
    SkeletonAnimation* getSun();
    static void deleteSun(list<Sun*>::iterator& sun);

  private:
    Runtime* _runtime;

    int _sunTag;
    bool _isEnable;
    bool _canDelete;
    Vec2 _position;
    SkeletonAnimation* _sun;
    Node* _node;
};

#endif  // SUN_H
