/**
 *Copyright (c) 2023 Xi-Gong.All Right Reserved
 *Author : Xi-Gong
 *Date: 2023.02.05
 *Email: xi_gong@foxmail.com
 */

#include "UserDataHandler.h"

#include <json/stringbuffer.h>
#include <json/writer.h>

#include "Based/Runtime.h"

UserDataHandler* UserDataHandler::_instance = nullptr;

UserDataHandler* UserDataHandler::getInstance() {
    if (_instance == nullptr) {
        _instance = new (std::nothrow) UserDataHandler;
    }

    return _instance;
}

void UserDataHandler::destroyInstance() { CC_SAFE_DELETE(_instance); }

void UserDataHandler::createNewUserDataDocument() {
    //    cocos2d::log("enter createNewUserDataDocument");
    _userDataDocument.reset(new Document());
    _userDataString.clear();
    _isAnewReadData = false;
}

void UserDataHandler::createNewLevelDataDocument() {
    _levelDataDocument.reset(new Document());
    _levelDataString.clear();
}

string UserDataHandler::getUserDataFileName() {
    string userDataFilePath = _fileUtils->getWritablePath() + "UserDataFile_" +
                              std::to_string(_userData->_caveFile.userCaveFileNumber) + ".dat";
    //    cocos2d::log("userDataFilePath: %s", userDataFilePath.c_str());
    return userDataFilePath;
}

string UserDataHandler::getLevelDataFileName() {
    return _fileUtils->getWritablePath() + "UserDataFile_" +
           std::to_string(_userData->_caveFile.userCaveFileNumber) + ".sav";
}

void UserDataHandler::flushData(DataType dataType) {
    StringBuffer buffer;
    rapidjson::Writer<StringBuffer> Writer(buffer);

    switch (dataType) {
        case DataType::UserData: {
            _userDataDocument->Accept(Writer);
            string str = string(buffer.GetString());
            _fileUtils->writeStringToFile(str, getUserDataFileName());
            _isAnewReadData = false;  // if flush must anew read data
            break;
        }

        case DataType::LevelData: {
            _levelDataDocument->Accept(Writer);
            string str = string(buffer.GetString());
            _fileUtils->writeStringToFile(str, getLevelDataFileName());
            break;
        }
        default: cocos2d::log("LevelData and SurvivalData not handle yet"); break;
    }
}

void UserDataHandler::removeLevelData(const char* key) {
    switch (openLevelData()) {
        case openUserDataReturnType::FileExistCorrect:
            if ((*_levelDataDocument).HasMember(key))
                (*_levelDataDocument).RemoveMember(key);
            break;
        default: return; break;
    }
    flushData(DataType::LevelData);
}

UserDataHandler::UserDataHandler() :
    _userData(Runtime::getInstance()->userData), _fileUtils(FileUtils::getInstance()),
    _userDataDocument(nullptr), _levelDataDocument(nullptr), _isAnewReadData(false) {}

UserDataHandler::~UserDataHandler() { _isAnewReadData = false; }

openUserDataReturnType UserDataHandler::openUserData() {
    // if cavefile exist
    if (_fileUtils->isFileExist(this->getUserDataFileName())) {
        if (_userDataString.empty() || !_isAnewReadData) {
            _isAnewReadData = true;
            _userDataString = _fileUtils->getStringFromFile(this->getUserDataFileName());
            _userDataDocument->Parse<rapidjson::kParseDefaultFlags>(_userDataString.c_str());
            if (_userDataDocument->HasParseError()) {
                return openUserDataReturnType::FileExistError;
            }
        }
        return openUserDataReturnType::FileExistCorrect;
    } else {
        if (!_userDataDocument->IsObject()) {
            _userDataDocument->SetObject();
            rapidjson::Value object(rapidjson::kObjectType);
            _userDataDocument->AddMember("UserData", object, _userDataDocument->GetAllocator());
        }
        return openUserDataReturnType::FileNotExist;
    }
}

openUserDataReturnType UserDataHandler::openLevelData() {
    // 如果有这个存档
    if (_fileUtils->isFileExist(getLevelDataFileName())) {
        _levelDataString = _fileUtils->getStringFromFile(getLevelDataFileName());
        _levelDataDocument->Parse<rapidjson::kParseDefaultFlags>(_levelDataString.c_str());

        if (_levelDataDocument->HasParseError()) {
            return openUserDataReturnType::FileExistError;
        }
        return openUserDataReturnType::FileExistCorrect;
    } else {
        return openUserDataReturnType::FileNotExist;
    }
}

bool UserDataHandler::isHaveMember(const char* key) {
    if ((*_userDataDocument)["UserData"].HasMember(key)) {
        return true;
    }

    return false;
}
