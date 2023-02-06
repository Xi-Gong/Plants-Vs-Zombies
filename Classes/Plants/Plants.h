/**
 *Copyright (c) 2019 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.4.20
 *Emal: 2117610943@qq.com
 */

#ifndef PLANTS_H
#define PLANTS_H

#include <cocos2d.h>
#include <spine/spine-cocos2dx.h>
#include <spine/spine.h>

#include "Based/Runtime.h"
#include "Zombies/Zombies.h"

#define INIT Vec2(-1000, -1000)
#define NOINITIALIZATION -1

using namespace spine;
using namespace cocos2d;
using namespace cocos2d::experimental;

enum class PlantsType {
    None = -1,
    SunFlower,  /* 向日葵 */
    PeaShooter, /* 豌豆射手 */
    WallNut,    /* 坚果墙 */
};

class Plants : public Node {
  public:
    Plants(Node* node = nullptr, const Vec2& position = Vec2::ZERO);
    virtual ~Plants() = default;

    static void stopPlantsAllAction();
    virtual Sprite* createPlantImage() = 0;
    virtual void createPlantAnimation() = 0;

    // 判断僵尸与植物之间的相对位置
    virtual void determineRelativePositionPlantsAndZombies();

    virtual void checkPlantHealthPoint() {}
    virtual void setPlantNode(Node* node) { _node = node; }
    virtual void setPlantPosition(const Vec2& position) { _position = position; }
    virtual void setPlantLocalZOrder(const int& order) { _zOrder = order; }

    // 设置植物所在行列
    virtual void setPlantRowAndColumn(const Vec2& rowAndColumn) { _rowAndColumn = rowAndColumn; }

    virtual void setPlantVisible(const bool visible);
    PlantsType getPlantType() const { return _plantsType; }

    virtual void setPlantTag(const int& tag) { _plantTag = tag; }
    virtual void setPlantHealthPoint(int healthPoint) { _healthPoint = healthPoint; }
    virtual void setPlantScale();
    virtual int getPlantTag() const { return _plantTag; }
    SkeletonAnimation* getPlantAnimation() { return _plantAnimation; }
    virtual bool getPlantIsSurvive() const;
    virtual float getPlantHealthPoint() const { return _healthPoint; }

    // 获取植物所在行列
    virtual Vec2 getPlantRowAndColumn() const { return _rowAndColumn; }

    virtual int getPlantRow() const { return _rowAndColumn.x; }
    virtual int getPlantColumn() const { return _rowAndColumn.y; }
    virtual bool getPlantVisible();
    virtual bool* getPlantIsCanDelete();

  protected:
    // 种植植物
    virtual SkeletonAnimation* plantInit(const std::string& plantname,
                                         const std::string& animaionname);
    // 创建植物图片
    virtual void imageInit(const std::string& name, const Vec2& position);

    virtual void reducePlantHealthPoint(int number) { _healthPoint -= number; }
    virtual void setPlantSoilSplashAnimation(const float& scale);
    virtual void setPlantShadow(const float& scale);
    virtual void setPlantHurtBlink();
    virtual void setPlantHurtBlink(PlantsType type) const;
    virtual bool getZombieIsTheFrontOfPlant(Zombies* zombie) const;
    virtual bool getZombieIsSameLineWithPlant(Zombies* zombie) const;
    virtual bool getzombieIsEncounterPlant(Zombies* zombie) const;
    virtual void zombieEatPlant(Zombies* zombie);

    // 僵尸从吃植物中恢复
    virtual void zombieRecoveryMove(Zombies* zombie);

  private:
    void setPlantGLProgram();

  protected:
    int _sunNeed;                             // 阳光需求
    int _costGold;                            // 花费金币
    int _costMasonry;                         // 花费砖石
    int _combatEffecttiveness;                // 战斗力
    int _plantTag;                            // 植物标签
    int _zOrder;                              // 绘制顺序
    int _plantNumber;                         // 存储植物编号（唯一性 ）
    bool _isLoop;                             // 是否循环
    bool _isCanDelete[2];                     // 是否可以删除
    float _coolDownTime;                      // 冷却时间
    float _healthPoint;                       // 生命值
    float _totalHealthPoint;                  // 生命总值
    Vec2 _position;                           // 位置
    Vec2 _rowAndColumn;                       // 详细地址,所在行列
    SkeletonAnimation* _plantAnimation;       // 植物动画
    Node* _node;                              // 节点
    Runtime* _runtime;                        // 全局变量
    Sprite* _plantImage;                      // 植物图片
    Sprite* _plantShadow;                     // 植物影子
    PlantsType _plantsType;                   // 植物类型
    SkeletonAnimation* _soilSplashAnimation;  // 泥土飞溅动画
    static int plantNumber;                   // 植物编号（唯一性）

  private:
    static GLProgram* _normalGLProgram;
    static GLProgram* _highLightGLProgram;
    GLProgramState* _highLightGLProgramState;
    float _highLightIntensity;
};

#endif  // PLANTS_H
