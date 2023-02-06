/**
 *Copyright (c) 2023 Xi-Gong.All Right Reserved
 *Author : Xi-Gong
 *Date: 2023.02.05
 *Email: xi_gong@foxmail.com
 */

#include "Runtime.h"

#include <AudioEngine.h>

#include <cassert>
#include <new>

// Use (void) to silence unused warnings.
#define assertm(exp, msg) assert(((void)msg, exp))
// uncomment to disable assert()
// #define NDEBUG

Runtime* Runtime::_instance = nullptr;

Runtime::Runtime() :
    gameData(new GameData(),
             [](GameData* p) {
                 cocos2d::log("game data release!");
                 delete p;
             }),
    userData(new UserData(),
             [](UserData* p) {
                 cocos2d::log("user data release!");
                 delete p;
             }),
    prohibitId(-1), _sumAnimationInterval(0), _frequence(0) {
    assertm(_instance == nullptr, "Runtime instance can be constructed only once");
    _instance = this;
}

Runtime::~Runtime() {
    assertm(this == _instance, "There is more than one runtime instance that exists");
    _instance = nullptr;
}

Runtime* Runtime::getInstance() {
    //    cocos2d::log("Here: %i", int(_instance == nullptr));
    assertm(_instance != nullptr, "Runtime instance haven't been constructed yet");
    return _instance;
}

void Runtime::checkAnimationInterval() {
    auto director = cocos2d::Director::getInstance();

    ++_frequence;
    if (_sumAnimationInterval <= 0) {
        _sumAnimationInterval = 1.f / director->getSecondsPerFrame();
    } else {
        _sumAnimationInterval = (_sumAnimationInterval + 1.f / director->getSecondsPerFrame()) / 2;
    }

    if (_sumAnimationInterval <= 20 && _frequence > 60) {
        cocos2d::experimental::AudioEngine::stopAll();
        string message = "        很抱歉！检测到程序运行的平均帧数太低对游戏的可玩性有极大的影响。\
    所以请点击确定按钮关闭此游戏！关闭不使用的其他程序或提升电脑硬件配置等操作后再次尝试运行此游戏。";
        cocos2d::log("exit message: %s", message.c_str());
        director->end();
    }
}

void Runtime::resumeProhibit() {
    cocos2d::experimental::AudioEngine::setFinishCallback(
        prohibitId, [=](int i, string name) { prohibitId = -1; });
}
