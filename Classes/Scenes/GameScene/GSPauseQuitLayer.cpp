/**
 *Copyright (c) 2019 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.4.20
 *Emal: 2117610943@qq.com
 */

#include "GSPauseQuitLayer.h"

#include <spine/spine-cocos2dx.h>

#include "Based/MusicPlayer.h"
#include "Scenes/SelectPlantsScene/SelectPlantsScene.h"
#include "Scenes/WorldScene/ModernWorld.h"

using namespace spine;

string GSPauseQuitLayer::_layerName[] = {"backgroundLayer", "buttonLayer",      "animationLayer",
                                         "controlLayer",    "informationLayer", "sunLayer"};

int GSPauseQuitLayer::_pauseNumbers = 0;

GSPauseQuitLayer::GSPauseQuitLayer() :
    _userDataHandler(UserDataHandler::getInstance()), _promptLayer(nullptr) {}

GSPauseQuitLayer::~GSPauseQuitLayer() { _pauseNumbers = 0; }

Layer* GSPauseQuitLayer::addLayer() { return GSPauseQuitLayer::create(); }

void GSPauseQuitLayer::pauseLayer() {
    auto director = Director::getInstance()->getRunningScene();
    for (auto name : _layerName) {
        if (director->getChildByName(name))
            director->getChildByName(name)->onExit();
        else
            return;
    }
    MusicPlayer::stopMusic();
    ++_pauseNumbers;
}

void GSPauseQuitLayer::resumeLayer() {
    if (!--_pauseNumbers) {
        auto director = Director::getInstance()->getRunningScene();
        for (auto name : _layerName) {
            if (director->getChildByName(name))
                director->getChildByName(name)->onEnter();
            else
                return;
        }
        MusicPlayer::resumeMusic();
    }
}

int GSPauseQuitLayer::getPauseNumbers() { return _pauseNumbers; }

bool GSPauseQuitLayer::init() {
    if (!LayerColor::initWithColor(Color4B(0, 0, 0, 180))) {
        return false;
    }

    createDialog();

    return true;
}

void GSPauseQuitLayer::createDialog() {
    _option = Sprite::createWithSpriteFrameName("LevelObjiectivesBg.png");
    _option->setPosition(_director->getWinSize() / 2);
    _option->setScale(0.9f);
    this->addChild(_option);

    auto PauseAnimation = SkeletonAnimation::createWithData(
        _runtime->gameData->getAnimationData().find("PauseAnimation")->second);
    PauseAnimation->setAnimation(0, "animation", true);
    PauseAnimation->setPosition(Vec2(530, 650));
    _option->addChild(PauseAnimation);

    /* 触摸移动监听 */
    _touchListener = createTouchListener(_option);

    auto gameText = _runtime->gameData->getGameText();
    /* 创建滑动条 */
    auto musicslider =
        createSlider(Vec2(600, 520), Vec2(150, 520), gameText.find("音乐")->second,
                     OptionScene_Slider::Music, Sprite::createWithSpriteFrameName("bgFile.png"),
                     Sprite::createWithSpriteFrameName("progressFile.png"),
                     Sprite::createWithSpriteFrameName("thumbFile.png"), nullptr, true);
    auto SoundEffectslider = createSlider(
        Vec2(600, 450), Vec2(150, 450), gameText.find("音效")->second,
        OptionScene_Slider::SoundEffect, Sprite::createWithSpriteFrameName("bgFile.png"),
        Sprite::createWithSpriteFrameName("progressFile.png"),
        Sprite::createWithSpriteFrameName("thumbFile.png"), nullptr, true);

    musicslider->setScale(1.2f);
    SoundEffectslider->setScale(1.2f);

    /* 创建复选框 */
    auto check = createCheckBox(Vec2(350, 380), Vec2(150, 380), gameText.find("信息")->second,
                                OptionScene_CheckBox::ShowFPS, "CheckBox2", "CheckBox", true);
    auto check1 = createCheckBox(Vec2(800, 380), Vec2(600, 380), gameText.find("全屏")->second,
                                 OptionScene_CheckBox::FullScreen, "CheckBox2", "CheckBox", true);
    auto check2 = createCheckBox(Vec2(350, 310), Vec2(150, 310), gameText.find("高帧率")->second,
                                 OptionScene_CheckBox::HighFPS, "CheckBox2", "CheckBox", true);
    auto check3 = createCheckBox(Vec2(800, 310), Vec2(600, 310), gameText.find("鼠标显示")->second,
                                 OptionScene_CheckBox::CursorHide, "CheckBox2", "CheckBox", true);
    auto check4 = createCheckBox(Vec2(350, 240), Vec2(150, 240), gameText.find("拉伸显示")->second,
                                 OptionScene_CheckBox::StretchShow, "CheckBox2", "CheckBox", true);
    auto check5 = createCheckBox(Vec2(800, 240), Vec2(600, 240), gameText.find("垂直同步")->second,
                                 OptionScene_CheckBox::VerticalSynchronization, "CheckBox2",
                                 "CheckBox", true);

    check->setScale(0.6f);
    check1->setScale(0.6f);
    check2->setScale(0.6f);
    check3->setScale(0.6f);
    check4->setScale(0.6f);
    check5->setScale(0.6f);

    /* 创建按钮 */
    createButton(Vec2(210, 170), gameText.find("查看图鉴")->second,
                 PauseQuitLayer_Button::ViewHandbook);
    createButton(Vec2(520, 170), gameText.find("重新开始")->second, PauseQuitLayer_Button::Restart);
    createButton(Vec2(830, 170), gameText.find("返回游戏")->second,
                 PauseQuitLayer_Button::ReturnGame);
    createButton(Vec2(365, 70), gameText.find("按键说明")->second,
                 PauseQuitLayer_Button::KeyDescription);
    createButton(Vec2(665, 70), gameText.find("退出游戏")->second, PauseQuitLayer_Button::QuitGame);
}

void GSPauseQuitLayer::createButton(const Vec2& vec2, const std::string name,
                                    PauseQuitLayer_Button button_type) {
    /* 创建返回主菜单按钮 */
    auto button = ui::Button::create("ButtonNew2.png", "ButtonNew.png", "", TextureResType::PLIST);
    auto label = Label::createWithTTF(name, GAME_FONT_NAME_1, 35);
    label->enableShadow(Color4B(0, 0, 0, 200));  // 设置阴影
    label->setScale(2.0f);
    button->setTitleLabel(label);
    button->setTitleColor(Color3B::WHITE);
    button->setPosition(vec2);
    button->setScale(0.5f);
    _option->addChild(button);

    button->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type) {
            case ui::Widget::TouchEventType::BEGAN: MusicPlayer::playMusic("gravebutton"); break;
            case ui::Widget::TouchEventType::ENDED:
                switch (button_type) {
                    case PauseQuitLayer_Button::ViewHandbook: openHandbook(); break;
                    case PauseQuitLayer_Button::Restart: setRestart(); break;
                    case PauseQuitLayer_Button::QuitGame: setQuitGame(); break;
                    case PauseQuitLayer_Button::KeyDescription: keyDescription(); break;
                    case PauseQuitLayer_Button::ReturnGame: returnGame(); break;
                    default: break;
                }
            default: break;
        }
    });
}

void GSPauseQuitLayer::showPrompt() {
    _promptLayer = LayerColor::create(Color4B(0, 0, 0, 180));
    createShieldLayer(_promptLayer);
    this->addChild(_promptLayer);

    auto prompt = Sprite::createWithSpriteFrameName("Prompt.png");
    prompt->setPosition(_director->getWinSize() / 2.0f);
    prompt->setOpacity(200);
    _promptLayer->addChild(prompt);

    auto Close = ui::Button::create("CloseDown.png", "Close.png", "", TextureResType::PLIST);
    Close->setPosition(Vec2(1510, 422));
    Close->setScale(0.6f);
    Close->setScaleY(0.58f);
    prompt->addChild(Close);

    Close->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type) {
            case ui::Widget::TouchEventType::BEGAN: MusicPlayer::playMusic("tap"); break;
            case ui::Widget::TouchEventType::ENDED: _promptLayer->removeFromParent(); break;
            default: break;
        }
    });
}

void GSPauseQuitLayer::openHandbook() {
    Application::getInstance()->openURL("https://lzpvz.rthe.net");
}

void GSPauseQuitLayer::setRestart() {
    _director->getScheduler()->setTimeScale(1.0f);
    _director->replaceScene(TransitionFade::create(1.0f, SelectPlantsScene::create()));
}

void GSPauseQuitLayer::setQuitGame() {
    _director->getScheduler()->setTimeScale(1.0f);

    popSceneAnimation();
}

void GSPauseQuitLayer::keyDescription() { showPrompt(); }

void GSPauseQuitLayer::returnGame() {
    resumeLayer();
    this->removeFromParent();
}

void GSPauseQuitLayer::popSceneAnimation() {
    auto layer = LayerColor::create(Color4B(0, 0, 0, 0));
    this->addChild(layer);
    layer->runAction(Sequence::create(FadeIn::create(0.5f), CallFunc::create([=]() {
                                          ModernWorld::setPopEnter(true);
                                          layer->removeFromParent();
                                          _director->popScene();
                                      }),
                                      nullptr));
}
