/**
 *Copyright (c) 2019 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.4.20
 *Emal: 2117610943@qq.com
 */

#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <memory>
#include <string>

using std::string;

class MusicPlayer {
  public:
    static void playMusic(const string& musicName, const bool isControlVolume = true);
    static int playMusic(const string& musicName, const int);
    static int changeBackgroundMusic(const string& musicName, bool loop);
    static void setMusicVolume(const int audioId);
    static void stopMusic();
    static void resumeMusic();
};

#endif  // MUSICPLAYER_H
