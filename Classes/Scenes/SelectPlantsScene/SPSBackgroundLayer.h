/**
 *Copyright (c) 2019 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.4.20
 *Emal: 2117610943@qq.com
 */

#ifndef SPSBACKGROUNDLAYER_H
#define SPSBACKGROUNDLAYER_H

#include <cocos2d.h>
#include <spine/spine-cocos2dx.h>
#include <spine/spine.h>

#include "Based/GameData/LevelDataHandler.h"
#include "Based/Runtime.h"
#include "Zombies/Zombies-Files.h"

using namespace spine;
using namespace cocos2d;

using std::default_random_engine;
using std::random_device;
using std::uniform_int_distribution;
using std::vector;

using UID = uniform_int_distribution<unsigned>;

class SPSBackgroundLayer : public Layer {
  public:
    SPSBackgroundLayer();
    virtual ~SPSBackgroundLayer() = default;
    virtual bool init() override;
    CREATE_FUNC(SPSBackgroundLayer);

  protected:
    virtual void createBackGroundEffect();

  private:
    /* 预览僵尸 */
    typedef struct {
        SkeletonAnimation* animation;
        float position_y;
        float position_x;
    } PreviewZombies;

    vector<PreviewZombies> _previewZombies;

  private:
    void createMordernBackgroundImage();
    void createFireEffect(Sprite* name);
    void createPreviewZombie();
    void createMordernPreviewZombies();
    void setBackgroundImagePosition();
    void sortZombiesPosition();
    Vec2 getPreviewZombiesPosition(UID& n1, UID& n2);
    Zombies* createDifferentZombies(const int& id);
    static bool cmp(PreviewZombies& a, PreviewZombies& b);

  private:
    Runtime* _runtime;

    int _previewZombiesTag;  // 预览僵尸编号
    LevelDataHandler* _levelDataHandler;
    default_random_engine _random;
    random_device _device;
};

#endif  // SPSBACKGROUNDLAYER_H
