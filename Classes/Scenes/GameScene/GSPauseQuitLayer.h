/**
 *Copyright (c) 2019 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.4.20
 *Emal: 2117610943@qq.com
 */

#ifndef GSPAUSEQUITLAYER_H
#define GSPAUSEQUITLAYER_H

#include <cocos2d.h>

#include "Scenes/MainMenuScene/OptionsMenu.h"

using namespace cocos2d;

enum class PauseQuitLayer_Button {
    ViewHandbook = 0,
    Restart,
    QuitGame,
    KeyDescription,
    ReturnGame
};

class GSPauseQuitLayer : public OptionsMenu {
  public:
    GSPauseQuitLayer();
    virtual ~GSPauseQuitLayer();
    virtual bool init() override;
    CREATE_FUNC(GSPauseQuitLayer);

    static Layer* addLayer();
    static void pauseLayer();
    static void resumeLayer();
    static int getPauseNumbers();

  protected:
    virtual void createButton(const Vec2& vec2, const std::string name, PauseQuitLayer_Button type);
    virtual void createDialog() override;
    virtual void popSceneAnimation();

  private:
    void showPrompt();
    void openHandbook();
    void setRestart();
    void setQuitGame();
    void keyDescription();
    void returnGame();

  protected:
    EventListenerTouchOneByOne* _touchListener;

  private:
    UserDataHandler* _userDataHandler;

    LayerColor* _promptLayer;
    static int _pauseNumbers;
    static string _layerName[6];
};

#endif  // GSPAUSEQUITLAYER_H
