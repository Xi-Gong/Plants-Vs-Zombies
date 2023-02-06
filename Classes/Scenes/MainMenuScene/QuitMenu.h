/**
 *Copyright (c) 2019 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.4.20
 *Emal: 2117610943@qq.com
 */

#ifndef QUITMENU_H
#define QUITMENU_H

#include "Based/Dialog.h"

class QuitMenu : public Dialog {
  public:
    QuitMenu() : _quitDialog(nullptr){};
    ~QuitMenu() = default;

    CREATE_FUNC(QuitMenu);
    virtual bool init() override;

    static int getSumRunTime();

  private:
    void createDialog();
    void createButtons(const std::string& Label, const Vec2& vec2, const int ID);
    void caveTime(const int time);

    virtual void deleteDialog() override;

  private:
    Sprite* _quitDialog;
};

#endif  // QUITMENU_H
