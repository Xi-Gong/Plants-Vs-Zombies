/**
 *Copyright (c) 2023 Xi-Gong.All Right Reserved
 *Author : Xi-Gong
 *Date: 2023.02.05
 *Email: xi_gong@foxmail.com
 */

#include "LevelDataHandler.h"

#include <CCPlatformMacros.h>

#include "Based/Runtime.h"

LevelDataHandler* LevelDataHandler::_instance = nullptr;

LevelDataHandler* LevelDataHandler::getInstance() {
    if (_instance == nullptr) {
        _instance = new (std::nothrow) LevelDataHandler;
    }
    return _instance;
}

void LevelDataHandler::destroyInstance() { CC_SAFE_DELETE(_instance); }

bool LevelDataHandler::openLevelData(const std::string& path) {
    string str = _fileUtils->getStringFromFile(path);
    this->documentInit();
    _levelDataDocument->Parse<rapidjson::kParseDefaultFlags>(str.c_str());
    if (_levelDataDocument->HasParseError()) {
        return false;
    }

    return true;
}

void LevelDataHandler::createLevelData(const int level, const char* levelName) {
    // if no level data in map
    if (!_gameData->_levelData.count(level)) {
        LevelData* levelData = new LevelData;
        if (createLevelDataFromDocument(levelData, levelName)) {
            _gameData->_levelData.insert(std::pair<int, LevelData*>(level, levelData));
        } else {
            delete levelData;
            _gameData->_levelData.insert(std::pair<int, LevelData*>(level, nullptr));
        }
    }
}

LevelData* LevelDataHandler::readLevelData(const int level) {
    auto data = _gameData->_levelData.find(level);
    if (data != _gameData->_levelData.end()) {
        return data->second;
    }
    return nullptr;
}

LevelDataHandler::LevelDataHandler() :
    _levelDataDocument(new Document), _levelNumber(-1), _gameData(Runtime::getInstance()->gameData),
    _fileUtils(FileUtils::getInstance()) {}

int LevelDataHandler::getLevelNumber() const { return _levelNumber; }

void LevelDataHandler::setLevelNumber(int newLevelNumber) { _levelNumber = newLevelNumber; }

void LevelDataHandler::documentInit() {
    for (auto data : _gameData->_levelData) {
        delete data.second;
        data.second = nullptr;
    }
    _gameData->_levelData.clear();
}

bool LevelDataHandler::createLevelDataFromDocument(LevelData* levelData, const char* levelName) {
    if (_levelDataDocument->HasMember(levelName)) {
        int rewardCoinNumbers = (*_levelDataDocument)[levelName]["CoinNumbers"].GetInt();
        levelData->rewardCoinNumbers = rewardCoinNumbers;

        int zombiesFrequency = (*_levelDataDocument)[levelName]["Frequency"].GetInt();
        levelData->zombiesFrequency = zombiesFrequency;

        int firstFrequencyTime = (*_levelDataDocument)[levelName]["FirstFrequencyTime"].GetInt();
        levelData->firstFrequencyTime = firstFrequencyTime;

        vector<int> zombiesType;
        for (unsigned int i = 0; i < (*_levelDataDocument)[levelName]["ZombiesType"].Size(); i++) {
            zombiesType.push_back((*_levelDataDocument)[levelName]["ZombiesType"][i].GetInt());
        }
        levelData->zombiesType = std::move(zombiesType);

        vector<int> zombiesNumbers;
        for (unsigned int i = 0; i < (*_levelDataDocument)[levelName]["ZombiesNumbers"].Size();
             i++) {
            zombiesNumbers.push_back(
                (*_levelDataDocument)[levelName]["ZombiesNumbers"][i].GetInt());
        }
        levelData->zombiesNumbers = std::move(zombiesNumbers);

        vector<int> munchZombiesFrequency;
        for (unsigned int i = 0;
             i < (*_levelDataDocument)[levelName]["MunchZombiesFrequency"].Size(); i++) {
            munchZombiesFrequency.push_back(
                (*_levelDataDocument)[levelName]["MunchZombiesFrequency"][i].GetInt());
        }
        levelData->munchZombiesFrequency = std::move(munchZombiesFrequency);

        vector<vector<int>> zombiesTypeProbabilityFrequency;
        vector<int> v;
        for (unsigned int i = 0;
             i < (*_levelDataDocument)[levelName]["ZombiesTypeProbability"].Size(); i++) {
            v.clear();
            for (unsigned int j = 0;
                 j < (*_levelDataDocument)[levelName]["ZombiesTypeProbability"][i].Size(); j++) {
                v.push_back(
                    (*_levelDataDocument)[levelName]["ZombiesTypeProbability"][i][j].GetInt());
            }
            zombiesTypeProbabilityFrequency.push_back(v);
        }
        levelData->zombiesTypeProbabilityFrequency = std::move(zombiesTypeProbabilityFrequency);

        return true;
    }

    return false;
}
