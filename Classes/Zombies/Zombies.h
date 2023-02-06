/**
 *Copyright (c) 2019 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.4.20
 *Emal: 2117610943@qq.com
 */

#ifndef ZOMBIES_H
#define ZOMBIES_H

#include <cocos2d.h>
#include <spine/spine-cocos2dx.h>
#include <spine/spine.h>

#include <random>

#include "Based/GameData/LevelData.h"
#include "Based/Runtime.h"

using namespace spine;
using namespace cocos2d;
using namespace cocos2d::experimental;

using std::default_random_engine;
using std::random_device;

class Plants;
class GSGameResultJudgement;
class GSGameEndLayer;

/* 僵尸类型 */
enum class ZombiesType { None = 0, CommonZombies, ConeZombies, BucketZombies, CommonFlagZombies };

enum class ShieldType { none = 0, IronHeadShield, IronBodyShield, PlasticsHeadShield };

class Zombies : public Node {
  public:
    Zombies();
    virtual ~Zombies() = default;

    static string getZombieAniamtionName(ZombiesType zombiestype);
    static void zombiesDeleteUpdate(list<Zombies*>::iterator& zombie);
    static unsigned int getZombiesNumbers();
    static void setZombiesNumbers(const unsigned int numbers);

    // 僵尸数量自增/自减一，“++”代表自增1，“--”代表自减1
    static void zombiesNumbersChange(const string&);

    static void judgeZombieWin(list<Zombies*>::iterator zombie);
    static void zombiesWinOrLoseInit();
    static GLProgram* getHighlight();
    static void rewardCoin(SkeletonAnimation* zombies);

    virtual void createZombie() = 0;
    virtual void createPreviewZombie() = 0;
    virtual void zombieInjuredEventUpdate() = 0;

    virtual void createZombieShadow();
    virtual void setZombieScale(const Size& scale = Size(40, 40)) const;
    virtual void setZombieScale(const int& scale) const;

    // 设置动画播放速度
    virtual void setZombieTimeScale(const float& timeScale) const;

    // 设置僵尸动画编号
    virtual void setZombieAnimationInformation(const int tag, const bool isLoop = true) const;

    virtual void setZombieAnimationName(const string& name, bool isLoop = true) const;

    // 设置是否显示僵尸掉落肢体动画
    virtual void setZombieIsShowLoseLimbsAnimation(const bool isShow);

    virtual void setZombieEatPlantNumber(const int& number);
    virtual void setZombieMove(const float delta);
    virtual void setZombieOpacity(GLubyte opacity);
    virtual void setZombiePosition(const Vec2& position);
    virtual void setZombieName(const string& name);
    virtual void setZombieTag(const int& tag);
    virtual void setZombieCurrentSpeed(const int currentSpeed);
    virtual void setZombieStop();
    virtual void setZombieIsShow(const bool isShow);

    // 设置僵尸是否吃植物
    virtual void setZombieIsEat(const bool isEat);

    virtual void setZombieDeath(const bool death);
    virtual void setZombieVisible(const bool isVisible);
    virtual void setZombieCurrentBodyShieldVolume(const float currentBodyShieldVolume);
    virtual void setZombieCurrentHeadShieldVolume(const float currentHeadShieldVolume);
    virtual void setZombieCurrentBloodVolume(const float currentBloodVolume);
    virtual void setZombieIsStrikeFly(const bool isStrikeFly);
    virtual void setZombieHurtBlink();
    virtual void setZombieScale();
    virtual SkeletonAnimation* getZombieAnimation() const;
    virtual bool getZombieIsSurvive() const;
    virtual bool getZombieIsVisible() const;
    virtual string getZombieName() const;

    /* 僵尸类型 */
    // 获取僵尸编号
    virtual int getZombieTag() const;

    virtual int getZombieEatPlantNumber() const;
    virtual bool getZombieIsPlayDieAnimation() const;
    virtual Vec2 getZombiePosition() const;
    virtual float getZombiePositionX() const;
    virtual float getZombiePositionY() const;
    virtual bool getZombieIsEnterMap() const;
    virtual float getZombieCurrentBodyShieldVolume() const;
    virtual float getZombieCurrentHeadShieldVolume() const;
    virtual float getZombieCurrentBloodVolume() const;
    virtual bool getZombieIsEat() const;
    virtual bool getZombieIsStop() const;
    virtual float getZombieCurrentSpeed() const;

    // 获取僵尸原本速度
    virtual float getZombieSpeed() const;

    virtual bool getZombieIsShow() const;
    virtual ZombiesType getZombieType() const;
    virtual int getZombieHeadAttackSoundEffect() const;
    virtual int getZombieBodyAttackSoundEffect() const;
    virtual bool* getIsCanDelete();
    virtual bool getZombieIsHaveShield() const;
    virtual bool getZombieIsStrikeFly() const;
    ShieldType getZombieBodyShieldType() const;
    ShieldType getZombieHeadShieldType() const;
    virtual void playZombiesDieAnimation();
    virtual void playZombieSoundEffect();

  protected:
    virtual void zombieInit(const string& animation_name = "Zombies");

    // 获取僵尸绘制图层
    virtual float getZombieLocalZOrder(const int& positiionY) const;

    virtual void setNode(Node* node) { _node = node; }

    // 设置僵尸一级损伤
    virtual void setZombiePrimaryInjure();

    // 设置僵尸二级损伤
    virtual void setZombieSecondaryInjure();

    virtual void zombieLoseArmAnimation(const std::string& name);
    virtual void zombieLoseHeadAnimation(const std::string& name);
    virtual void zombieLoseShieldAnimation(const std::string& name);

    virtual void zombieFadeOutAnimation();
    virtual void playZombieSoundEffect(const string& name);

    // 显示僵尸肢体与护盾影子
    virtual void showZombieShadow(Node* node, const int posy);

    virtual void setZombieHeadShieldPrimaryInjure(const string& oldName, const string& newName);
    virtual void setZombieHeadShieldSecondaryInjure(const string& oldName, const string& newName);
    virtual void setZombieHeadShieldThirdInjure(const string& oldName, const string& newName);

    virtual void setZombieBodyShieldPrimaryInjure(const string& oldName, const string& newName);
    virtual void setZombieBodyShieldSecondaryInjure(const string& oldName, const string& newName);
    virtual void setZombieBodyShieldThirdInjure(const string& oldName, const string& newName);

  private:
    void setSmallZombieAttribute();
    void setBigZombieAttribute();
    void setOpacityZombieAttribute();
    void setZombieGLProgram();
    bool getZombieWarning();
    string& createZombieName();

  protected:
    Runtime* _runtime;  // 全局变量

    int _attackHeadSoundEffectType;        // 攻击头部音效
    int _attackBodySoundEffectType;        // 攻击身体音效
    int _bodyAnimationId;                  // 身体动画编号
    int _bodyShieldAnimationId;            // 身体护盾动画编号
    int _headShieldAnimationId;            // 头部护盾动画编号
    int _zombieTag;                        // 僵尸编号(暂未使用)
    float _bloodVolume;                    // 血量
    float _headShieldVolume;               // 护盾血量
    float _bodyShieldVolume;               // 护盾1血量
    float _currentBloodVolume;             // 当前血量
    float _currentHeadShieldVolume;        // 当前护盾血量
    float _currentBodyShieldVolume;        // 当前护盾1血量
    float _speed;                          // 存储移动速度
    float _currentSpeed;                   // 移动速度
    bool _isHaveShield;                    // 是否有护盾
    bool _isUseForGameType;                // 是否被使用在游戏类型
    bool _isEat;                           // 是否在吃植物
    bool _isEatGarlic;                     // 是否吃大蒜
    bool _isShow;                          // 是否显示
    bool _isPreview;                       // 是否是预览模式
    bool _isShowLoseLimbsAnimation;        // 是否显示僵尸掉落肢体动画
    bool _isCanDelete[2];                  // 是否可以删除
    bool _isStrikeFly;                     // 是否击飞
    string _zombieName;                    // 僵尸名字
    Vec2 _position;                        // 位置
    Node* _node;                           // 节点
    SkeletonAnimation* _zombiesAnimation;  // 僵尸动画
    ShieldType _headShieldType;            // 头部护盾类型
    ShieldType _bodyShieldType;            // 身体护盾类型
    ZombiesType _zombiesType;              // 僵尸类型
    string _animationName[7];              // 动画名称
    default_random_engine _random;         // 随机数引擎
    random_device _device;
    static unsigned int _zombiesNumbers;  // 僵尸数量

  private:
    LevelDataHandler* _levelDataHandler;

    int _zombieEatPlantNumber;
    int _zombieHowlNumbers;
    GLProgramState* _highLightGLProgramState;
    float _highLightIntensity;
    bool _highLightFinished;
    bool _redWarning;

    static bool _zombieIsWin;
    static int _zombiesNewDieNumbers;
    static GLProgram* _normalGLProgram;
    static GLProgram* _highLightGLProgram;
    static GSGameEndLayer* _gameEndLayer;
    static GSGameResultJudgement* _gameResultJudgement;
};

#endif  // ZOMBIES_H
