/**
 *Copyright (c) 2023 Xi-Gong.All Right Reserved
 *Author : Xi-Gong
 *Date: 2023.02.05
 *Email: xi_gong@foxmail.com
 */

#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <spine/spine-cocos2dx.h>
#include <ui/CocosGUI.h>

#include <list>
#include <map>
#include <string>
#include <vector>

#include "LevelData.h"
#include "ResourcePath.h"

using cocos2d::ui::CheckBox;
using std::list;
using std::map;
using std::string;
using std::vector;

class LevelDataHandler;

class GameData {
    friend LevelDataHandler;

  public:
    GameData() = default;
    ~GameData() = default;

    ResourcePath& getResourcePath();
    map<string, spSkeletonData*>& getAnimationData();
    map<string, string>& getGameText();

    static unsigned long getScreenDisplayFrequency();
    static void setScreenDisplayFrequency(unsigned long newScreenDisplayFrequency);

  private:
    ResourcePath _resourcePath;
    map<int, LevelData*> _levelData;
    map<string, string> _gameText;
    map<string, spSkeletonData*> _animationData;
    static unsigned long _screenDisplayFrequency;
};

#endif  // GAMEDATA_H
