/**
 *Copyright (c) 2023 Xi-Gong.All Right Reserved
 *Author : Xi-Gong
 *Date: 2023.02.05
 *Email: xi_gong@foxmail.com
 */

#ifndef CAVEFILE_H
#define CAVEFILE_H

#include <string>

using std::string;

struct CaveFile {
    CaveFile() : userCaveFileNumber(0) {
        string keyName[] = {"USERNAMEDATA",   "USERNAMEDATA_2", "USERNAMEDATA_3", "USERNAMEDATA_4",
                            "USERNAMEDATA_5", "USERNAMEDATA_6", "USERNAMEDATA_7", "USERNAMEDATA_8"};
        string fileName[] = {"WORLD_%d_LEVELS",   "WORLD_%d_LEVELS_2", "WORLD_%d_LEVELS_3",
                             "WORLD_%d_LEVELS_4", "WORLD_%d_LEVELS_5", "WORLD_%d_LEVELS_6",
                             "WORLD_%d_LEVELS_7", "WORLD_%d_LEVELS_8"};

        for (int i = 0; i < 8; ++i) {
            userCaveFileNameKey[i] = keyName[i];
            systemCaveFileName[i] = fileName[i];
        }
    }
    ~CaveFile() = default;

    // i.e. user cave file id
    int userCaveFileNumber;

    string userCaveFileName[8];
    string userCaveFileNameKey[8];

    // hold default values in order to prevent user undefined error
    string systemCaveFileName[8];
};

#endif  // CAVEFILE_H
