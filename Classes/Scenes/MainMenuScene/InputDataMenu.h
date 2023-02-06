/**
 *Copyright (c) 2019 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.4.20
 *Emal: 2117610943@qq.com
 */

#ifndef INPUTDATAMENU_H
#define INPUTDATAMENU_H

#include <ui/CocosGUI.h>

#include <map>
#include <string>

#include "Based/Dialog.h"

using namespace cocos2d::ui;
using std::map;
using std::string;

class InputDataMenu : public Dialog {
  public:
    InputDataMenu();
    ~InputDataMenu() = default;
    CREATE_FUNC(InputDataMenu);
    virtual bool init() override;

  protected:
    virtual void deleteDialog() override;

  private:
    // create dialogs
    void createDialog();
    void CreateInputDialog();

    // create buttons
    void createButtons(Sprite* sprite, const std::string& Label, const Vec2& vec2,
                       const float scale, const int ID);
    void createDataButton(const std::string& Labels, const Vec2& vec2, const float scale,
                          const int ID);

    // button settings
    void setButtonColor(Button* button);
    void setButtonText(Button* button, const string& text, const float scale);

    void createShieldLayer();
    void updateButtonText();
    Label* onTextFieldInsertText();
    Label* onTextFieldDeleteBackward();

    void inputNewFileDataName();
    void caveData();

  private:
    UserDefault* _userDefault;

    LayerColor* _shieldDialogLayer;
    Sprite* _caveFileDialog;
    Sprite* _inputCursor;
    Sprite* _inputDataDialog;
    EditBox* _editbox;
    TextField* _textField;
    Vec2 _beginPosition;
    string _inputString, _newInputstring, _lastString;
    int _caveFileNumber;
    map<int, Button*> _dataButton;
    EventListenerTouchOneByOne* _shieldListener;
};

#endif  // INPUTDATAMENU_H
