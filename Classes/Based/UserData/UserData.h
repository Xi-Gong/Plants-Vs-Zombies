/**
 *Copyright (c) 2023 Xi-Gong.All Right Reserved
 *Author : Xi-Gong
 *Date: 2023.02.05
 *Email: xi_gong@foxmail.com
 */

#ifndef USERDATA_H
#define USERDATA_H

#include <string>
#include <vector>

#include "CaveFile.h"
#include "UserSelectCard.h"
#include "UserSetting.h"
#include "UserWorldData.h"

using std::string;
using std::vector;

class UserDataHandler;

class UserData {
    friend UserDataHandler;

  public:
    UserData();
    ~UserData() = default;

    UserSetting& getUserSetting();

    CaveFile& getCaveFile();

    UserWorldData& getUserWorldData();

    const char* getCurrentCaveFileLevelWorldName();

    string getUserName() const;
    void setUserName(const string& newUserName);

    bool getIsUpdate() const;
    void setIsUpdate(bool newIsUpdate);

    bool getIsReadFileLevelData() const;
    void setIsReadFileLevelData(bool newIsReadFileLevelData);

  private:
    UserSetting _userSetting;
    CaveFile _caveFile;
    UserWorldData _userWorldData;

    string _userName;
    bool _isUpdate;  // 用户名是否更新
    bool _isReadFileLevelData;
};

#endif  // USERDATA_H
