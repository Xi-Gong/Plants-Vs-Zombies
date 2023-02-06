/**
 *Copyright (c) 2019 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.4.20
 *Emal: 2117610943@qq.com
 */

#include "SelectPlantsScene.h"

#include "Based/GameData/LevelDataHandler.h"
#include "Based/MusicPlayer.h"
#include "SPSBackgroundLayer.h"
#include "Scenes/GameScene/GameScene.h"

SelectPlantsScene::SelectPlantsScene() :
    _controlLayer(nullptr), _scrollLayer(nullptr), _spriteLayer(nullptr), _scrollView(nullptr),
    _director(Director::getInstance()), _runtime(Runtime::getInstance()) {
    MusicPlayer::changeBackgroundMusic("mainmusic.mo3.1", true);
}

bool SelectPlantsScene::init() {
    if (!Scene::init()) {
        return false;
    }

    createBackgroundLayer();
    createControlLayer();
    // 触发0.25秒计时器
    schedule(schedule_selector(SelectPlantsScene::eventUpdate), 0.25f);
    schedule([this](float) { _runtime->checkAnimationInterval(); }, 1.f, "FPS");

    return true;
}

void SelectPlantsScene::createReadyText(const std::string& name, const int& id) {
    static float time[] = {0, 0.2f, 0.2f, 1.5f};
    auto text = Sprite::createWithSpriteFrameName(name + ".png");
    text->setScale(15.0f);
    text->setName(name);
    text->setPosition(Director::getInstance()->getWinSize() / 2.0f);
    text->runAction(Sequence::create(
        ScaleTo::create(0.3f, 2.0f), DelayTime::create(time[id]),
        CallFuncN::create(CC_CALLBACK_1(SelectPlantsScene::readyTextCallBack, this, name, id)),
        nullptr));
    this->addChild(text);
}

void SelectPlantsScene::readyTextCallBack(Node* node, const std::string& name, const int& id) {
    this->removeChildByName(name);
    switch (id) {
        case 1: createReadyText("StartSet", 2); break;
        case 2: createReadyText("StartPlant", 3); break;
        default:
            _scrollLayer->removeChildByName("previewBackgroundImage");
            replaceScene();
            break;
    }
}

void SelectPlantsScene::replaceScene() {
    auto& userWorldData = _runtime->userData->getUserWorldData();
    userWorldData.userSelectCard = _spriteLayer->seedBankButton;

    auto& userSetting = _runtime->userData->getUserSetting();
    if (userSetting.easeAnimation == ui::CheckBox::EventType::SELECTED) {
        Director::getInstance()->replaceScene(TransitionFade::create(1.f, GameScene::create()));
    } else {
        Director::getInstance()->replaceScene(GameScene::create());
    }
}

void SelectPlantsScene::createBackgroundLayer() {
    /* 设置容器大小 */
    _scrollLayer = Layer::create();
    _scrollLayer->setContentSize(Size(2930, 1080));

    /* 创建容器中的东西（精灵）*/
    _scrollLayer->addChild(SPSBackgroundLayer::create());

    // 创建滚动视图
    _scrollView = extension::ScrollView::create();
    _scrollView = extension::ScrollView::create(_director->getWinSize(), _scrollLayer);
    _scrollView->setPosition(Vec2(0, 0));
    _scrollView->setDirection(extension::ScrollView::Direction::HORIZONTAL);  // 设置只能纵向滚动
    _scrollView->setTouchEnabled(false);                                      // 关闭触碰事件
    _scrollView->runAction(
        Sequence::create(DelayTime::create(1.0f), CallFuncN::create([&](Node* node) {
                             _scrollView->setContentOffsetInDuration(Vec2(-1010, 0), 2.5f);
                         }),
                         nullptr));
    this->addChild(_scrollView);
}

void SelectPlantsScene::createControlLayer() {
    _controlLayer = SPSControlLayer::create();
    this->addChild(_controlLayer, 1);
}

void SelectPlantsScene::eventUpdate(float Time) {
    //    cocos2d::log("Time: %f", Time);
    if (Time == 0.22f && _spriteLayer->_selectFinished) {
        unschedule(schedule_selector(SelectPlantsScene::eventUpdate));
        // 选择植物后，向左滚动回对战的草坪
        selectPlantsCallBack();
    } else if (Time == 0.25f) {
        if (_scrollView->getContentOffset().x <= SCROLLRIGHTFINISHED) {
            /* 取消定时函数 */
            unschedule(schedule_selector(SelectPlantsScene::eventUpdate));

            // 创建选择植物对话框
            runAction(Sequence::create(DelayTime::create(1.0f),
                                       CallFunc::create([&]() { createSelectPlantsDialog(); }),
                                       nullptr));
        }
    } else if (Time == 0.3f) {
        if (_scrollView->getContentOffset().x >= SCROLLLEFTFINISHED) {
            /* 播放音乐 */
            MusicPlayer::playMusic("readysetplant");
            /* 取消定时函数 */
            this->unschedule(schedule_selector(SelectPlantsScene::eventUpdate));

            // 准备！安放！植物！（等等游戏开始提醒文字）
            createReadyText("StartReady", 1);
        }
    }
}

void SelectPlantsScene::createSelectPlantsDialog() {
    /* 删除名字 */
    _controlLayer->removeChildByName("username");

    _spriteLayer = SPSSpriteLayer::create();
    this->addChild(_spriteLayer);

    schedule(schedule_selector(SelectPlantsScene::eventUpdate), 0.22f);
}

void SelectPlantsScene::selectPlantsCallBack() {
    _scrollView->setContentOffsetInDuration(Vec2(-220, 0), 2.0f);  // 设置滚动方向与时间
    this->schedule(schedule_selector(SelectPlantsScene::eventUpdate), 0.3f);
}
