/**
 *Copyright (c) 2023 Xi-Gong.All Right Reserved
 *Author : Xi-Gong
 *Date: 2023.02.05
 *Email: xi_gong@foxmail.com
 */

#ifndef DATALOADER_H
#define DATALOADER_H

#include <CCUserDefault.h>

#include <map>
#include <memory>
#include <string>
#include <utility>

#include "GameData/GameData.h"
#include "UserData/UserData.h"
#include "UserData/UserDataHandler.h"

using std::map;
using std::pair;
using std::string;

class DataLoader {
  public:
    DataLoader();
    ~DataLoader();

    static void loadUserFileData();
    static void caveUserFileData();

  private:
    // high level functions
    void loadAll();

    // low level functions
    void loadResource();
    void loadSettings();

    // load resource from resource path
    void loadText();
    void loadImage();
    void loadMusic();
    void loadAnimation();

    // load user file and configure settings
    void loadSystemSettings();
    void loadUserSettings();

    // check whether str ends with suffix
    bool endsWith(const string& str, const string& suffix);

  private:
    Director* _director;
    UserDefault* _userDefault;
    FileUtils* _fileUtils;
    UserDataHandler* _userDataHandler;

    std::shared_ptr<GameData> _gameData;
    std::shared_ptr<UserData> _userData;
};

#endif  // DATALOADER_H
