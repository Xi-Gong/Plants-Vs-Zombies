/**
 *Copyright (c) 2019 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.4.20
 *Emal: 2117610943@qq.com
 */

#ifndef OPTIONSMENU_H
#define OPTIONSMENU_H

#include <cocos-ext.h>
#include <cocos2d.h>
#include <ui/CocosGUI.h>

#include "Based/Dialog.h"
#include "Based/UserData/UserDataHandler.h"

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace cocos2d::extension;

enum class OptionScene_CheckBox {
    ShowFPS = 1,
    FullScreen,
    HighFPS,
    CursorHide,
    StretchShow,
    EaseAnimation,
    VerticalSynchronization
};

enum class OptionScene_Slider { Music = 1, SoundEffect };

class OptionsMenu : public Dialog {
  public:
    OptionsMenu();
    virtual ~OptionsMenu() = default;
    CREATE_FUNC(OptionsMenu);
    virtual bool init() override;

  protected:
    virtual void createDialog();
    virtual CheckBox* createCheckBox(const Vec2& vec2, const Vec2& vec2_, const std::string& Label,
                                     OptionScene_CheckBox button_type, const std::string NotSelect,
                                     const std::string Select, const bool IsNew = false);
    virtual ControlSlider* createSlider(const Vec2& vec2, const Vec2& vec2_,
                                        const std::string& Label, OptionScene_Slider slider_type,
                                        Sprite* BgFile, Sprite* progressFile, Sprite* thumbFile,
                                        Sprite* selectThumbFile = nullptr,
                                        const bool IsNew = false);
    virtual void deleteDialog() override;

  private:
    void createButton();
    void backgroundMusicVolumeChangeCallBack(Ref* sender, Control::EventType type);
    void soundEffectMusicVolumeChangeCallBack(Ref* sender, Control::EventType type);

  protected:
    Sprite* _option;
    Director* _director;

  private:
    UserDefault* _userDefault;
    UserDataHandler* _userDataHandler;

    std::shared_ptr<GameData> _gameData;
    std::shared_ptr<UserData> _userData;
};

#endif  // OPTIONSMENU_H
