/**
 *Copyright (c) 2019 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.4.20
 *Emal: 2117610943@qq.com
 */

#ifndef GSDATA_H
#define GSDATA_H

#include <list>
#include <map>
#include <vector>

using namespace std;

class GSBackgroundLayer;
class GSInformationLayer;
class GSButtonLayer;
class GSControlLayer;
class GSAnimationLayer;

class Plants;
class Zombies;
class Bullet;
class Sun;
class Coin;
class Car;

extern GSBackgroundLayer* backgroundLayerInformation;    // 背景层实例化
extern GSInformationLayer* informationLayerInformation;  // 信息层实例化
extern GSButtonLayer* buttonLayerInformation;            // 按钮层实例化
extern GSControlLayer* controlLayerInformation;          // 控制层实例化
extern GSAnimationLayer* animationLayerInformation;      // 动画层示例化

/**使用multimap：使用随机查找删除
 *存储所有植物的集合
 */
extern multimap<int, Plants*> PlantsGroup;

/**使用list：遍历满条件即删除
 *存储所有僵尸的集合
 */
extern list<Zombies*> ZombiesGroup;

/**使用list：遍历满足条件删除
 *存储所有植物发出的子弹的集合
 */
extern list<Bullet*> BulletGroup;

/**使用list：遍历满足条件删除
 *存储阳光的集合
 */
extern list<Sun*> SunsGroup;

/**使用list：遍历满足条件删除
 *存储汽车的集合
 */
extern list<Car*> CarsGroup;

/**使用list：遍历满足条件删除
 *存储金币的集合
 */
extern list<Coin*> CoinsGroup;

#endif  // GSDATA_H
