/**
 *Copyright (c) 2023 Xi-Gong.All Right Reserved
 *Author : Xi-Gong
 *Date: 2023.02.05
 *Email: xi_gong@foxmail.com
 */

#ifndef USERDATAHANDLER_H
#define USERDATAHANDLER_H

#include <cocos2d.h>
#include <json/document.h>
#include <ui/CocosGUI.h>

#include <list>
#include <memory>
#include <string>

#include "UserData.h"

using namespace rapidjson;
using namespace cocos2d;
using namespace cocos2d::ui;

using std::list;
using std::string;

enum class openUserDataReturnType { FileExistError = 1, FileExistCorrect, FileNotExist };

enum class DataType { UserData = 1, LevelData, SurvivalData };

class UserDataHandler {
  public:
    static UserDataHandler* getInstance();
    static void destroyInstance();

    void createNewUserDataDocument();
    void createNewLevelDataDocument();

    void flushData(DataType dataType);

    // ValueType only accept double, bool, char*, int and float type
    template <typename ValueType>
    void caveUserData(const char* key, ValueType value) {
        switch (openUserData()) {
            case openUserDataReturnType::FileExistCorrect: {
                if (isHaveMember(key)) {
                    if constexpr (std::is_same<ValueType, double>::value) {
                        (*_userDataDocument)["UserData"][key].SetDouble(value);
                    } else if constexpr (std::is_same<ValueType, bool>::value) {
                        (*_userDataDocument)["UserData"][key].SetBool(value);
                    } else if constexpr (std::is_same<ValueType, char*>::value) {
                        (*_userDataDocument)["UserData"][key].SetString(
                            rapidjson::StringRef(value));
                    } else if constexpr (std::is_same<ValueType, int>::value) {
                        (*_userDataDocument)["UserData"][key].SetInt(value);
                    } else if constexpr (std::is_same<ValueType, float>::value) {
                        (*_userDataDocument)["UserData"][key].SetFloat(value);
                    } else {
                        throw std::runtime_error(
                            "ValueType only accept double, bool, char*, int and float type");
                    }
                } else {
                    (*_userDataDocument)["UserData"].AddMember(rapidjson::StringRef(key), value,
                                                               _userDataDocument->GetAllocator());
                }
                break;
            }

            case openUserDataReturnType::FileNotExist:
                (*_userDataDocument)["UserData"].AddMember(rapidjson::StringRef(key), value,
                                                           _userDataDocument->GetAllocator());
                break;

            case openUserDataReturnType::FileExistError:
                remove(getUserDataFileName().c_str());
                break;
        }

        flushData(DataType::UserData);
    }

    // ValueType only accept double, bool, char*, int and float type
    template <typename ValueType>
    ValueType openUserData(const char* key) {
        ValueType result = ValueType();
        switch (openUserData()) {
            case openUserDataReturnType::FileExistCorrect: {
                if (isHaveMember(key)) {
                    if constexpr (std::is_same<ValueType, double>::value) {
                        result = (*_userDataDocument)["UserData"][key].GetDouble();
                    } else if constexpr (std::is_same<ValueType, bool>::value) {
                        result = (*_userDataDocument)["UserData"][key].GetBool();
                    } else if constexpr (std::is_same<ValueType, char*>::value) {
                        result = (*_userDataDocument)["UserData"][key].GetString();
                    } else if constexpr (std::is_same<ValueType, int>::value) {
                        result = (*_userDataDocument)["UserData"][key].GetInt();
                    } else if constexpr (std::is_same<ValueType, float>::value) {
                        result = (*_userDataDocument)["UserData"][key].GetFloat();
                    } else {
                        throw std::runtime_error(
                            "ValueType only accept double, bool, char*, int and float type");
                    }
                }
                break;
            }

            case openUserDataReturnType::FileExistError:
                remove(this->getUserDataFileName().c_str());
                break;

            case openUserDataReturnType::FileNotExist:
                cocos2d::log("openUserDataReturnType::FileNotExist");
                break;
        }

        //        cocos2d::log("openUserData return undefined value");
        return result;
    }

    //    void openLevelData(const char* key);
    //    bool readLevelData();
    //    void caveLevelData(const char* key);
    void removeLevelData(const char* key);

  private:
    UserDataHandler();
    ~UserDataHandler();

    // low level functions
    openUserDataReturnType openUserData();
    openUserDataReturnType openLevelData();
    string getUserDataFileName();
    string getLevelDataFileName();
    bool isHaveMember(const char* key);

  private:
    static UserDataHandler* _instance;

    std::shared_ptr<UserData> _userData;
    FileUtils* _fileUtils;

    std::unique_ptr<Document> _userDataDocument;
    string _userDataString;
    bool _isAnewReadData;

    // user level progress document
    std::unique_ptr<Document> _levelDataDocument;
    string _levelDataString;
};

#endif  // USERDATAHANDLER_H
