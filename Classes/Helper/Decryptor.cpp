/**
 *Copyright (c) 2023 Xi-Gong.All Right Reserved
 *Author : Xi-Gong
 *Date: 2023.02.05
 *Email: xi_gong@foxmail.com
 */

#include "Decryptor.h"

void Decryptor::decrypt(string& cSrc, char* cDest) {
    int i, h, l, m, n, j = 0;
    for (i = 0; i < static_cast<int>(cSrc.size()); i = i + 2) {
        h = (cSrc[i] - 'x');
        l = (cSrc[i + 1] - 'z');
        m = (h << 4);
        n = (l & 0xf);
        cDest[j] = m + n;
        j++;
    }
    cDest[j] = '\0';
}

const char* Decryptor::decryptXMLFile(std::string& filePath) {
    string cSrc = FileUtils::getInstance()->getStringFromFile(filePath);
    char* cDest = (char*)malloc(sizeof(char) * cSrc.size());
    decrypt(cSrc, cDest);
    //        cocos2d::log("cDest: \n%s", cDest);
    return cDest;
}
