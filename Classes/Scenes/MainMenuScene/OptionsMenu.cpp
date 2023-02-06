/**
 *Copyright (c) 2019 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.4.20
 *Emal: 2117610943@qq.com
 */

#include "OptionsMenu.h"

#include <AudioEngine.h>

#include "Based/MusicPlayer.h"

OptionsMenu::OptionsMenu() :
    _userDefault(UserDefault::getInstance()), _director(Director::getInstance()),
    _userDataHandler(UserDataHandler::getInstance()), _gameData(_runtime->gameData),
    _userData(_runtime->userData) {}

bool OptionsMenu::init() {
    if (!LayerColor::initWithColor(Color4B(0, 0, 0, 180))) {
        return false;
    }

    createShieldLayer(this);

    this->createDialog();

    return true;
}

void OptionsMenu::createDialog() {
    _option = Sprite::createWithSpriteFrameName("options_menuback.png");
    _option->setPosition(_director->getWinSize() / 2);
    _option->setScale(1.7f);
    _option->setName("_option");
    this->addChild(_option);

    createTouchListener(_option);

    this->createSlider(Vec2(250, 350), Vec2(140, 350),
                       _gameData->getGameText().find("音乐")->second, OptionScene_Slider::Music,
                       Sprite::createWithSpriteFrameName("options_sliderslot.png"),
                       Sprite::createWithSpriteFrameName("options_sliderslot.png"),
                       Sprite::createWithSpriteFrameName("options_sliderknob2.png"),
                       Sprite::createWithSpriteFrameName("options_sliderknob2.png"));
    this->createSlider(Vec2(250, 310), Vec2(140, 310),
                       _gameData->getGameText().find("音效")->second,
                       OptionScene_Slider::SoundEffect,
                       Sprite::createWithSpriteFrameName("options_sliderslot.png"),
                       Sprite::createWithSpriteFrameName("options_sliderslot.png"),
                       Sprite::createWithSpriteFrameName("options_sliderknob2.png"),
                       Sprite::createWithSpriteFrameName("options_sliderknob2.png"));

    this->createCheckBox(Vec2(300, 280), Vec2(140, 280),
                         _gameData->getGameText().find("信息")->second,
                         OptionScene_CheckBox::ShowFPS, "options_checkbox0", "options_checkbox1");
    this->createCheckBox(
        Vec2(300, 245), Vec2(140, 245), _gameData->getGameText().find("全屏")->second,
        OptionScene_CheckBox::FullScreen, "options_checkbox0", "options_checkbox1");
    this->createCheckBox(Vec2(300, 210), Vec2(140, 210),
                         _gameData->getGameText().find("高帧率")->second,
                         OptionScene_CheckBox::HighFPS, "options_checkbox0", "options_checkbox1");
    this->createCheckBox(
        Vec2(300, 175), Vec2(140, 175), _gameData->getGameText().find("拉伸显示")->second,
        OptionScene_CheckBox::StretchShow, "options_checkbox0", "options_checkbox1");

    this->createButton();
}

CheckBox* OptionsMenu::createCheckBox(const Vec2& vec2, const Vec2& vec2_, const std::string& Label,
                                      OptionScene_CheckBox button_type, const std::string NotSelect,
                                      const std::string Select, const bool IsNew) {
    auto checkbox = CheckBox::create();
    checkbox->loadTextureBackGround(NotSelect + ".png", TextureResType::PLIST);
    checkbox->loadTextureFrontCross(Select + ".png", TextureResType::PLIST);
    checkbox->setPosition(vec2);
    _option->addChild(checkbox);

    UserSetting* userSetting = &(_userData->getUserSetting());

    switch (button_type) {
        case OptionScene_CheckBox::ShowFPS: {
            bool flag = userSetting->showFPS == CheckBox::EventType::SELECTED ? true : false;
            checkbox->setSelected(flag);
            break;
        }

        case OptionScene_CheckBox::FullScreen: {
            bool flag = userSetting->fullScreen == CheckBox::EventType::SELECTED ? true : false;
            checkbox->setSelected(flag);
            break;
        }

        case OptionScene_CheckBox::HighFPS: {
            bool flag = userSetting->highFPS == CheckBox::EventType::SELECTED ? true : false;
            checkbox->setSelected(flag);
            break;
        }

        case OptionScene_CheckBox::CursorHide: {
            bool flag = userSetting->cursorNotHide == CheckBox::EventType::SELECTED ? true : false;
            checkbox->setSelected(flag);
            break;
        }

        case OptionScene_CheckBox::StretchShow: {
            bool flag = userSetting->stretchingShow == CheckBox::EventType::SELECTED ? true : false;
            checkbox->setSelected(flag);
            break;
        }

        case OptionScene_CheckBox::EaseAnimation: {
            bool flag = userSetting->easeAnimation == CheckBox::EventType::SELECTED ? true : false;
            checkbox->setSelected(flag);
            break;
        }

        case OptionScene_CheckBox::VerticalSynchronization: {
            bool flag = userSetting->verticalSynchronization == CheckBox::EventType::SELECTED ?
                            true :
                            false;
            checkbox->setSelected(flag);
            break;
        }

        default: break;
    }

    checkbox->addEventListener([=](Ref* sender, CheckBox::EventType type) {
        switch (type) {
            case CheckBox::EventType::SELECTED:
                switch (button_type) {
                    case OptionScene_CheckBox::ShowFPS:
                        _userDefault->setBoolForKey("SHOWINFORMATION", true);
                        userSetting->showFPS = CheckBox::EventType::SELECTED;  // update
                        _director->setDisplayStats(true);
                        break;
                    case OptionScene_CheckBox::FullScreen:
                        _userDefault->setBoolForKey("SHOWFULLSCREEN", true);
                        userSetting->fullScreen = CheckBox::EventType::SELECTED;
                        ((GLViewImpl*)_director->getOpenGLView())->setFullscreen();
                        break;
                    case OptionScene_CheckBox::HighFPS:
                        _userDefault->setBoolForKey("SHOWHIGHFPS", true);
                        userSetting->highFPS = CheckBox::EventType::SELECTED;
                        _director->setAnimationInterval(1.0f /
                                                        GameData::getScreenDisplayFrequency());
                        break;
                    case OptionScene_CheckBox::CursorHide:
                        _userDataHandler->caveUserData<bool>("CURSORHIDE", true);
                        userSetting->cursorNotHide = CheckBox::EventType::SELECTED;
                        break;
                    case OptionScene_CheckBox::StretchShow:
                        _userDefault->setBoolForKey("STRETCHINGSHOW", true);
                        _director->getOpenGLView()->setDesignResolutionSize(
                            _director->getWinSize().width, _director->getWinSize().height,
                            ResolutionPolicy::EXACT_FIT);
                        userSetting->stretchingShow = CheckBox::EventType::SELECTED;
                        break;
                    case OptionScene_CheckBox::EaseAnimation:
                        _userDataHandler->caveUserData<bool>("EASEANIMATION", true);
                        userSetting->easeAnimation = CheckBox::EventType::SELECTED;
                        break;
                    case OptionScene_CheckBox::VerticalSynchronization:
                        _userDefault->setBoolForKey("VERTICALSYNCHRONIZATION", true);
#if CC_TARGET_PLATFORM == CC_PLATFORM_LINUX
                        glfwSwapInterval(1);
#elif CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
                        wglSwapIntervalEXT(1);
#else
                        cocos2d::log("current platform not support vertical syncronization yet");
#endif
                        userSetting->verticalSynchronization = CheckBox::EventType::SELECTED;
                        break;
                    default: break;
                }
                break;

            case CheckBox::EventType::UNSELECTED:
                switch (button_type) {
                    case OptionScene_CheckBox::ShowFPS:
                        _userDefault->setBoolForKey("SHOWINFORMATION", false);
                        userSetting->showFPS = CheckBox::EventType::UNSELECTED;  // update
                        _director->setDisplayStats(false);
                        break;
                    case OptionScene_CheckBox::FullScreen:
                        _userDefault->setBoolForKey("SHOWFULLSCREEN", false);
                        userSetting->fullScreen = CheckBox::EventType::UNSELECTED;
                        ((GLViewImpl*)_director->getOpenGLView())->setWindowed(1280, 720);
                        break;
                    case OptionScene_CheckBox::HighFPS:
                        _userDefault->setBoolForKey("SHOWHIGHFPS", false);
                        userSetting->highFPS = CheckBox::EventType::UNSELECTED;
                        _director->setAnimationInterval(1.0f / 30);
                        break;
                    case OptionScene_CheckBox::CursorHide:
                        _userDataHandler->caveUserData<bool>("CURSORHIDE", false);
                        userSetting->cursorNotHide = CheckBox::EventType::UNSELECTED;
                        break;
                    case OptionScene_CheckBox::StretchShow:
                        _userDefault->setBoolForKey("STRETCHINGSHOW", false);
                        _director->getOpenGLView()->setDesignResolutionSize(
                            _director->getWinSize().width, _director->getWinSize().height,
                            ResolutionPolicy::SHOW_ALL);
                        userSetting->stretchingShow = CheckBox::EventType::UNSELECTED;
                        break;
                    case OptionScene_CheckBox::EaseAnimation:
                        _userDataHandler->caveUserData<bool>("EASEANIMATION", false);
                        userSetting->easeAnimation = CheckBox::EventType::UNSELECTED;
                        break;
                    case OptionScene_CheckBox::VerticalSynchronization:
                        _userDefault->setBoolForKey("VERTICALSYNCHRONIZATION", false);
#if CC_TARGET_PLATFORM == CC_PLATFORM_LINUX
                        glfwSwapInterval(0);
#elif CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
                        wglSwapIntervalEXT(0);
#else
                        cocos2d::log("current platform not support vertical syncronization yet");
#endif
                        userSetting->verticalSynchronization = CheckBox::EventType::UNSELECTED;
                        break;
                    default: break;
                }
                break;
            default: break;
        }
    });

    if (IsNew) {
        _option->addChild(label(Label, 30, vec2_, 0, Color3B::WHITE));
    } else {
        _option->addChild(label(Label, 20, vec2_, 0, Color3B::GRAY));
    }

    return checkbox;
}

ControlSlider* OptionsMenu::createSlider(const Vec2& vec2, const Vec2& vec2_,
                                         const std::string& Label, OptionScene_Slider slider_type,
                                         Sprite* BgFile, Sprite* progressFile, Sprite* thumbFile,
                                         Sprite* selectThumbFile, const bool IsNew) {
    ControlSlider* slider;
    selectThumbFile ? selectThumbFile->setColor(Color3B::GRAY),
        slider = ControlSlider::create(BgFile, progressFile, thumbFile, selectThumbFile) :
                      slider = ControlSlider::create(BgFile, progressFile, thumbFile);

    slider->setMinimumValue(0);
    slider->setMaximumValue(100);
    slider->setPosition(vec2);
    _option->addChild(slider);

    auto& userSetting = _userData->getUserSetting();
    switch (slider_type) {
        case OptionScene_Slider::Music:
            slider->setValue(userSetting.backgroundMusicVolume * 100);
            slider->addTargetWithActionForControlEvents(
                this, cccontrol_selector(OptionsMenu::backgroundMusicVolumeChangeCallBack),
                Control::EventType::VALUE_CHANGED);
            break;
        case OptionScene_Slider::SoundEffect:
            slider->setValue(userSetting.soundEffectVolume * 100);
            slider->addTargetWithActionForControlEvents(
                this, cccontrol_selector(OptionsMenu::soundEffectMusicVolumeChangeCallBack),
                Control::EventType::VALUE_CHANGED);
            break;
    }

    // create label
    if (IsNew) {
        _option->addChild(label(Label, 30, vec2_, 0, Color3B::WHITE));
    } else {
        _option->addChild(label(Label, 20, vec2_, 0, Color3B::GRAY));
    }

    return slider;
}

void OptionsMenu::deleteDialog() {
    setMouseListenerEnable();
    this->removeFromParent();
}

void OptionsMenu::createButton() {
    auto button = Button::create("options_backtogamebutton0.png", "options_backtogamebutton2.png",
                                 "", TextureResType::PLIST);
    button->setTitleLabel(label(_gameData->getGameText().find("返回")->second, 30));
    button->setPosition(Vec2(210, 55));
    _option->addChild(button);
    button->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type) {
        switch (type) {
            case Widget::TouchEventType::BEGAN: MusicPlayer::playMusic("gravebutton"); break;
            case Widget::TouchEventType::ENDED: deleteDialog(); break;
            default:
                cocos2d::log("Enumeration values 'MOVED' and 'CANCELED' not handled in switch");
                break;
        }
    });
}

void OptionsMenu::backgroundMusicVolumeChangeCallBack(Ref* sender, Control::EventType type) {
    auto slider = (ControlSlider*)sender;

    auto& userSetting = _userData->getUserSetting();
    userSetting.backgroundMusicVolume = slider->getValue() / 100.0f;
    _userDefault->setFloatForKey("GLOBALMUSIC", userSetting.backgroundMusicVolume);

    for (auto sp : userSetting.backgroundMusic) {
        AudioEngine::setVolume(sp, slider->getValue() / 100.0f);
    }

    if (slider->getSelectedThumbSprite()->getContentSize().height > 30) {
        // rotate animation
        slider->getThumbSprite()->setRotation(slider->getValue() * 10);
        slider->getSelectedThumbSprite()->setRotation(slider->getValue() * 10);
    }
}

void OptionsMenu::soundEffectMusicVolumeChangeCallBack(Ref* sender, Control::EventType type) {
    auto slider = (ControlSlider*)sender;

    auto& userSetting = _userData->getUserSetting();
    userSetting.soundEffectVolume = slider->getValue() / 100.0f;
    _userDefault->setFloatForKey("SOUNDEFFECT", userSetting.soundEffectVolume);

    if (slider->getSelectedThumbSprite()->getContentSize().height > 30) {
        // rotate animation
        slider->getThumbSprite()->setRotation(slider->getValue() * 10);
        slider->getSelectedThumbSprite()->setRotation(slider->getValue() * 10);
    }
}
