/**
 *Copyright (c) 2023 Xi-Gong.All Right Reserved
 *Author : Xi-Gong
 *Date: 2023.02.05
 *Email: xi_gong@foxmail.com
 */

#include "UserData.h"

UserData::UserData() : _userName("未命名存档"), _isUpdate(false), _isReadFileLevelData(false) {}

UserSetting& UserData::getUserSetting() { return _userSetting; }

CaveFile& UserData::getCaveFile() { return _caveFile; }

UserWorldData& UserData::getUserWorldData() { return _userWorldData; }

const char* UserData::getCurrentCaveFileLevelWorldName() {
    string name = "LevelData_ModernWorld_" + std::to_string(_userWorldData.currentLevel) + "\0";
    char* str = new char[name.size()];
    strcpy(str, name.c_str());
    return str;
}

string UserData::getUserName() const { return _userName; }

void UserData::setUserName(const string& newUserName) { _userName = newUserName; }

bool UserData::getIsUpdate() const { return _isUpdate; }

void UserData::setIsUpdate(bool newIsUpdate) { _isUpdate = newIsUpdate; }

bool UserData::getIsReadFileLevelData() const { return _isReadFileLevelData; }

void UserData::setIsReadFileLevelData(bool newIsReadFileLevelData) {
    _isReadFileLevelData = newIsReadFileLevelData;
}
