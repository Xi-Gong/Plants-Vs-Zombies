/**
 *Copyright (c) 2023 Xi-Gong.All Right Reserved
 *Author : Xi-Gong
 *Date: 2023.02.05
 *Email: xi_gong@foxmail.com
 */

#ifndef RESOURCEPATH_H
#define RESOURCEPATH_H

#include <map>
#include <string>

using std::map;
using std::string;

class ResourcePath {
  public:
    ResourcePath();
    ~ResourcePath() = default;

    map<string, string>& getTextPath();
    map<string, string>& getImagePath();
    map<string, string>& getMusicPath();
    map<string, string>& getAnimationPath();

  private:
    map<string, string> extractResourcePathFromXML(const string& xmlPath);

  private:
    map<string, string> _textPath;
    map<string, string> _imagePath;
    map<string, string> _musicPath;
    map<string, string> _animationPath;
};

#endif  // RESOURCEPATH_H
