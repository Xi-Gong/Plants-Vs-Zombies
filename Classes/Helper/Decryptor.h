/**
 *Copyright (c) 2023 Xi-Gong.All Right Reserved
 *Author : Xi-Gong
 *Date: 2023.02.05
 *Email: xi_gong@foxmail.com
 */

#ifndef DECRYPTOR_H
#define DECRYPTOR_H

#include <CCFileUtils.h>

#include <string>

using cocos2d::FileUtils;
using std::string;

// migrate history project needs
class Decryptor {
  public:
    static void decrypt(string& cSrc, char* cDest);
    static const char* decryptXMLFile(string& filePath);
};

#endif  // DECRYPTOR_H
