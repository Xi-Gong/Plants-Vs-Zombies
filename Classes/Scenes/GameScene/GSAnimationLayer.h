/**
 *Copyright (c) 2019 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.4.20
 *Emal: 2117610943@qq.com
 */

#ifndef GSANIMATIONLAYER_H
#define GSANIMATIONLAYER_H

#include <cocos2d.h>

#include "Based/GameData/LevelDataHandler.h"
#include "Based/Runtime.h"

using namespace cocos2d;

using std::default_random_engine;
using std::random_device;

class Plants;
class SunFlower;
class Zombies;
enum class PlantsType;
enum class ZombiesType;

class GSAnimationLayer : public Layer {
  public:
    GSAnimationLayer(Node* node = nullptr);
    ~GSAnimationLayer();
    virtual bool init() override;
    CREATE_FUNC(GSAnimationLayer);

    static GSAnimationLayer* create(Node* node);
    Plants* createDifferentPlants(PlantsType plantsType);
    Zombies* createDifferentZombies(ZombiesType zombiesType);
    void stopRandomSun();
    void addLayer(Node* node, const int order, const string& name) {
        node->addChild(this, order, name);
    }
    void plantPlants();
    void deletePlants();
    void createZombies();
    void createZombiesOnSurvival();
    Layer* getSunLayer() const;
    GSAnimationLayer* getAnimationLayer();

  private:
    void createSunLayer();
    void createRandomSuns();
    void showCars();
    void gameMainLoop(float delta);
    void zombiesEventUpdate(float delta);
    void plantsEventUpdate();
    void plantsDeleteUpdate(map<int, Plants*>::iterator& plant);
    void bulletEventUpdate();
    void sunsDeleteUpdate();
    void coinDeleteUpdate();
    void carsEventUpdate();

  private:
    Runtime* _runtime;
    LevelDataHandler* _levelDataHandler;

    Node* _gameScene;
    Layer* _sunLayer;
    SunFlower* _randomSuns;
    default_random_engine _random;
    random_device _device;
};

#endif  // GSANIMATIONLAYER_H
