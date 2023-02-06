/**
 *Copyright (c) 2023 Xi-Gong.All Right Reserved
 *Author : Xi-Gong
 *Date: 2023.02.05
 *Email: xi_gong@foxmail.com
 */

#ifndef LEVELDATAHANDLER_H
#define LEVELDATAHANDLER_H

#include <CCFileUtils.h>
#include <json/document.h>

#include <map>
#include <memory>
#include <string>

#include "GameData.h"
#include "LevelData.h"

using namespace rapidjson;
using cocos2d::FileUtils;
using std::map;
using std::string;

class LevelDataHandler {
  public:
    static LevelDataHandler* getInstance();
    static void destroyInstance();

    bool openLevelData(const string& path);

    // create specified level data
    void createLevelData(const int level, const char* levelName);

    // read specified level data
    LevelData* readLevelData(const int level);

    int getLevelNumber() const;
    void setLevelNumber(int newLevelNumber);

  private:
    LevelDataHandler();
    ~LevelDataHandler() = default;

    // low level functions
    void documentInit();
    bool createLevelDataFromDocument(LevelData* levelData, const char* levelName);

  private:
    static LevelDataHandler* _instance;

    FileUtils* _fileUtils;
    std::shared_ptr<GameData> _gameData;

    std::unique_ptr<Document> _levelDataDocument;
    int _levelNumber;
};

#endif  // LEVELDATAHANDLER_H
