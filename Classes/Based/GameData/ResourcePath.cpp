/**
 *Copyright (c) 2023 Xi-Gong.All Right Reserved
 *Author : Xi-Gong
 *Date: 2023.02.05
 *Email: xi_gong@foxmail.com
 */

#include "ResourcePath.h"

#include <CCFileUtils.h>
#include <tinyxml2.h>

ResourcePath::ResourcePath() {
    _textPath = extractResourcePathFromXML("resources/Text/TextPath.xml");
    _imagePath = extractResourcePathFromXML("resources/Text/ImagePath.xml");
    _musicPath = extractResourcePathFromXML("resources/Text/MusicPath.xml");
    _animationPath = extractResourcePathFromXML("resources/Text/AnimationPath.xml");

    //    for (auto& path : _musicPath) {
    //        cocos2d::log("Name = %s, Value = %s", path.first.c_str(), path.second.c_str());
    //    }
}

map<string, string>& ResourcePath::getTextPath() { return _textPath; }

map<string, string>& ResourcePath::getImagePath() { return _imagePath; }

map<string, string>& ResourcePath::getMusicPath() { return _musicPath; }

map<string, string>& ResourcePath::getAnimationPath() { return _animationPath; }

map<string, string> ResourcePath::extractResourcePathFromXML(const std::string& xmlPath) {
    tinyxml2::XMLDocument* doc = new tinyxml2::XMLDocument();
    doc->Parse(cocos2d::FileUtils::getInstance()->getStringFromFile(xmlPath).c_str());

    map<string, string> resPath;
    auto root = doc->RootElement();
    for (auto e = root->FirstChildElement(); e != nullptr; e = e->NextSiblingElement()) {
        for (auto attr = e->FirstAttribute(); attr != nullptr; attr = attr->Next()) {
            resPath.insert(std::pair<string, string>(attr->Name(), attr->Value()));
        }
    }

    delete doc;
    return resPath;
}
