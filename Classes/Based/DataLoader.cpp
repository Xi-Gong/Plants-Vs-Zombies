/**
 *Copyright (c) 2023 Xi-Gong.All Right Reserved
 *Author : Xi-Gong
 *Date: 2023.02.05
 *Email: xi_gong@foxmail.com
 */

#include "DataLoader.h"

#include <AudioEngine.h>
#include <cocos2d.h>
#include <spine/spine-cocos2dx.h>
#include <tinyxml2.h>

#include "Helper/Decryptor.h"
#include "Runtime.h"

using namespace cocos2d;

// const string operator"" _s(const char* arg) { return string(arg); }

DataLoader::DataLoader() :
    _gameData(Runtime::getInstance()->gameData), _userData(Runtime::getInstance()->userData),
    _userDataHandler(UserDataHandler::getInstance()), _director(Director::getInstance()),
    _userDefault(UserDefault::getInstance()), _fileUtils(FileUtils::getInstance()) {
    loadAll();
}

DataLoader::~DataLoader() {}

void DataLoader::loadAll() {
    loadResource();
    loadSettings();
}

void DataLoader::loadResource() {
    loadText();
    loadImage();
    loadMusic();
    loadAnimation();
}

void DataLoader::loadSettings() {
    loadSystemSettings();

    auto& caveFile = _userData->getCaveFile();

    // read user cave file name
    for (int i = 0; i < 8; i++) {
        const char* key = caveFile.userCaveFileNameKey[i].c_str();
        string str = _userDefault->getStringForKey(key);

        if (!str.empty()) {
            caveFile.userCaveFileName[i] = str;
        } else {
            caveFile.userCaveFileName[i] = "未命名存档";
        }
    }

    _userDataHandler->createNewUserDataDocument();

    loadUserFileData();
    loadUserSettings();
}

void DataLoader::loadSystemSettings() {
    _director->getOpenGLView()->setCursor("resources/images/System/cursor.png",
                                          cocos2d::Point::ANCHOR_TOP_LEFT);
    _director->getOpenGLView()->setIcon("resources/images/System/PlantsVsZombies.png");
}

// static method
void DataLoader::loadUserFileData() {
    auto userDefault = UserDefault::getInstance();
    auto userData = Runtime::getInstance()->userData;
    auto gameData = Runtime::getInstance()->gameData;
    auto dataHandler = UserDataHandler::getInstance();

    if (!userDefault->getBoolForKey("RUNGAMEBEFORE")) {
        userDefault->setFloatForKey("SOUNDEFFECT", 0.5f);
        userDefault->setFloatForKey("GLOBALMUSIC", 0.2f);
        userDefault->setBoolForKey("SHOWFULLSCREEN", false);
        userDefault->setBoolForKey("SHOWHIGHFPS", false);
        userDefault->setBoolForKey("SHOWINFORMATION", true);
        userDefault->setBoolForKey("RUNGAMEBEFORE", true);
    }

    auto& caveFile = userData->getCaveFile();
    caveFile.userCaveFileNumber = userDefault->getIntegerForKey("USERDATANUMBER");

    auto& userSetting = userData->getUserSetting();
    userSetting.soundEffectVolume = userDefault->getFloatForKey("SOUNDEFFECT");
    userSetting.backgroundMusicVolume = userDefault->getFloatForKey("GLOBALMUSIC");

    auto& userWorldData = userData->getUserWorldData();
    int killZombiesNumbers = dataHandler->openUserData<int>("KILLALLZOMBIES");
    userWorldData.killZombiesNumbers = killZombiesNumbers;

    int coinNumbers = dataHandler->openUserData<int>("COINNUMBERS");
    userWorldData.coinNumbers = coinNumbers;
}

// static method
void DataLoader::caveUserFileData() {
    auto userData = Runtime::getInstance()->userData;
    auto& userWorldData = userData->getUserWorldData();
    auto dataHandler = UserDataHandler::getInstance();

    dataHandler->caveUserData("KILLALLZOMBIES", userWorldData.killZombiesNumbers);
    dataHandler->caveUserData("COINNUMBERS", userWorldData.coinNumbers);
}

void DataLoader::loadUserSettings() {
    auto& caveFile = _userData->getCaveFile();
    auto& userSetting = _userData->getUserSetting();

    int id = caveFile.userCaveFileNumber;
    auto userName = caveFile.userCaveFileName[id];
    _userData->setUserName(userName);

    _userData->setIsUpdate(true);

    if (_userDefault->getBoolForKey("SHOWINFORMATION")) {
        _director->setDisplayStats(true);
        userSetting.showFPS = cocos2d::ui::CheckBox::EventType::SELECTED;
    } else {
        _director->setDisplayStats(false);
        userSetting.showFPS = cocos2d::ui::CheckBox::EventType::UNSELECTED;
    }

    if (_userDefault->getBoolForKey("SHOWHIGHFPS")) {
        _director->setAnimationInterval(1.0f / GameData::getScreenDisplayFrequency());
        userSetting.highFPS = cocos2d::ui::CheckBox::EventType::SELECTED;
    } else {
        // set FPS. the default value is 1.0/60 if you don't call this
        _director->setAnimationInterval(1.0f / 60);
        userSetting.highFPS = cocos2d::ui::CheckBox::EventType::UNSELECTED;
    }

    if (_userDefault->getBoolForKey("SHOWFULLSCREEN")) {
        ((GLViewImpl*)_director->getOpenGLView())->setFullscreen();
        userSetting.fullScreen = cocos2d::ui::CheckBox::EventType::SELECTED;
    } else {
        ((GLViewImpl*)_director->getOpenGLView())->setWindowed(1280, 720);
        userSetting.fullScreen = cocos2d::ui::CheckBox::EventType::UNSELECTED;
    }

    if (_userDefault->getBoolForKey("STRETCHINGSHOW")) {
        userSetting.stretchingShow = cocos2d::ui::CheckBox::EventType::SELECTED;
        _director->getOpenGLView()->setDesignResolutionSize(_director->getWinSize().width,
                                                            _director->getWinSize().height,
                                                            ResolutionPolicy::EXACT_FIT);
    } else {
        userSetting.stretchingShow = cocos2d::ui::CheckBox::EventType::UNSELECTED;
        _director->getOpenGLView()->setDesignResolutionSize(_director->getWinSize().width,
                                                            _director->getWinSize().height,
                                                            ResolutionPolicy::SHOW_ALL);
    }

    if (_userDefault->getBoolForKey("VERTICALSYNCHRONIZATION")) {
#if CC_TARGET_PLATFORM == CC_PLATFORM_LINUX
        glfwSwapInterval(1);
#elif CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
        wglSwapIntervalEXT(1);
#else
        cocos2d::log("current platform not support vertical syncronization yet");
#endif
        userSetting.verticalSynchronization = CheckBox::EventType::SELECTED;
    } else {
#if CC_TARGET_PLATFORM == CC_PLATFORM_LINUX
        glfwSwapInterval(0);
#elif CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
        wglSwapIntervalEXT(0);
#else
        cocos2d::log("current platform not support vertical syncronization yet");
#endif
        userSetting.verticalSynchronization = CheckBox::EventType::UNSELECTED;
    }

    bool cursorHide = _userDataHandler->openUserData<bool>("CURSORHIDE");
    userSetting.cursorNotHide = cursorHide ? cocos2d::ui::CheckBox::EventType::SELECTED :
                                             cocos2d::ui::CheckBox::EventType::UNSELECTED;

    bool easeAnimation = _userDataHandler->openUserData<bool>("EASEANIMATION");
    userSetting.easeAnimation = easeAnimation ? cocos2d::ui::CheckBox::EventType::SELECTED :
                                                cocos2d::ui::CheckBox::EventType::UNSELECTED;
}

bool DataLoader::endsWith(const std::string& str, const std::string& suffix) {
    if (str.length() < suffix.length()) {
        return false;
    }
    return str.compare(str.length() - suffix.length(), suffix.length(), suffix) == 0;
}

void DataLoader::loadText() {
    auto& resourcePath = _gameData->getResourcePath();
    auto& gameText = _gameData->getGameText();

    for (auto& i : resourcePath.getTextPath()) {
        ValueVector Text;
        if (endsWith(i.second, ".xml")) {
            Text = _fileUtils->getValueVectorFromFile(i.second);
        }

        for (auto& file : Text) {
            auto file_map = file.asValueMap();
            pair<string, string> text =
                std::make_pair(file_map.at("id").asString(), file_map.at("info").asString());
            gameText.insert(text);
        }
    }
}

void DataLoader::loadImage() {
    auto& resourcePath = _gameData->getResourcePath();

    for (auto& path : resourcePath.getImagePath()) {
        //        cocos2d::log("image Path: %s", path.second.c_str());
        //         add sprite frame in sync way
        Texture2D* texture = _director->getTextureCache()->addImage(path.second + ".pvr.ccz");
        //        cocos2d::log("%s", string(path.second + ".pvr.ccz").c_str());
        SpriteFrameCache::getInstance()->addSpriteFramesWithFile(path.second + ".plist", texture);
        //        cocos2d::log("%s", string(path.second + ".plist").c_str());

        //        Do not add sprite frame in async way!
        //        _director->getTextureCache()->addImageAsync(
        //            path.second + ".pvr.ccz", [=](Texture2D* texture) {
        //                SpriteFrameCache::getInstance()->addSpriteFramesWithFile(path.second +
        //                ".plist",
        //                                                                         texture);
        //            });
    }
}

void DataLoader::loadMusic() {
    auto& resourcePath = _gameData->getResourcePath();

    for (auto& i : resourcePath.getMusicPath()) {
        experimental::AudioEngine::preload(i.second, [=](bool isSucceed) {});
    }
}

void DataLoader::loadAnimation() {
    auto& resourcePath = _gameData->getResourcePath();
    auto& animationData = _gameData->getAnimationData();

    for (auto& i : resourcePath.getAnimationPath()) {
        // store temporary file name
        char JsonName[128], AtlasName[128];

        // convert
        snprintf(JsonName, 128, "resources/Animations/compiled/%s.compiled", (i.second).c_str());
        snprintf(AtlasName, 128, "resources/Animations/reanim/%s.reanim", (i.second).c_str());
        //        cocos2d::log("JsonName: %s", JsonName);

        // load
        spSkeletonJson* json =
            spSkeletonJson_createWithLoader((spAttachmentLoader*)Cocos2dAttachmentLoader_create(
                spAtlas_createFromFile(AtlasName, nullptr)));
        auto skeletonData = spSkeletonJson_readSkeletonDataFile(json, JsonName);
        spSkeletonJson_dispose(json);

        // insert animation data to map
        animationData.insert(pair<string, spSkeletonData*>(i.second, skeletonData));
    }
}
