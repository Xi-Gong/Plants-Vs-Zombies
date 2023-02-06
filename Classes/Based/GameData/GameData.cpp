/**
 *Copyright (c) 2023 Xi-Gong.All Right Reserved
 *Author : Xi-Gong
 *Date: 2023.02.05
 *Email: xi_gong@foxmail.com
 */

#include "GameData.h"

unsigned long GameData::_screenDisplayFrequency = 60;

ResourcePath& GameData::getResourcePath() { return _resourcePath; }

map<string, spSkeletonData*>& GameData::getAnimationData() { return _animationData; }

map<string, string>& GameData::getGameText() { return _gameText; }

unsigned long GameData::getScreenDisplayFrequency() { return _screenDisplayFrequency; }

void GameData::setScreenDisplayFrequency(unsigned long newScreenDisplayFrequency) {
    _screenDisplayFrequency = newScreenDisplayFrequency;
}
