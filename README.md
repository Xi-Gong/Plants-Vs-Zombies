# Plants-Vs-Zombies (LZ Linux version)

[Chinese version README click here.](README_zh_cn.md)

## Introduction <br>
This project is developed based on cocos2dx. The prototype of this project was originally developed by LZ and [released on Github](https://github.com/ErLinErYi/PlantsVsZombies). LZ's project is the best open-source Plants vs. Zombies project I've ever seen, with the best performance and the most complete functionality. Since I needed a C++ project to practice on the Ubuntu platform, I made some improvements and adjustments based on this project and re-released it.

## Overview <br>
After learning LZ's project, I discovered the following areas for improvement:
- LZ's project was set up on Windows using Visual Studio 2017, with project files managed through .vcxproj. However, since Visual Studio is not free and open-source software, and the manual configuration is relatively cumbersome, it is not conducive to promoting this project.
- The project's C++ code is approximately 18,000 lines, which is very comprehensive but somewhat overwhelming for beginners.
- The C++11 standard used in the project is becoming outdated.

To address these areas for improvement, I made the following changes:
- Since cocos2dx natively supports CMake configuration, I configured the project using CMake.
- I used the open-source VSCode for development, which is easy to install and configure quickly.
- I removed some secondary game effects and functionalities, reducing the project's size to 8,000 lines of C++ code, making it easier for beginners to learn.
- C++17 standard is applied to the cocos2dx library and project code.

Finally, based on my understanding of C++, I redesigned the basic classes of this project, including decoupling between classes, clarifying semantics, and applying C++17 syntax.

## Class Diagram
Here, I made some modifications to the basic classes and drew the corresponding UML diagrams. For the original UML diagram, please refer to LZ's project.

![ClassDiagram](https://github.com/Xi-Gong/Plants-Vs-Zombies/blob/main/pvzBasicClassUML.png?raw=true)

## Example
In the project’s root directory, there’s a video called `pvzExampleVideo.mkv` that shows the project in action. To avoid copyright issues, the game assets shared by LZ has been blurred. The unblurred gameplay is shown in the image below.

![Image(图片)](https://img-blog.csdnimg.cn/20200405101902466.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQwNjMwMjQ2,size_16,color_FFFFFF,t_70)

## Requirement
* Ubuntu 22.04 (for other Ubuntu versions, please test them on your own).
* CMake >= 3.16.

## Environment

1. Clone this project and install the dependencies required for cocos2dx. Note that cocos2dx itself is already included with the project, so there’s no need for a separate installation.
```shell
git clone --recursive https://github.com/Xi-Gong/Plants-Vs-Zombies.git
cd Plants-Vs-Zombies/cocos2d/
sudo apt install python2.7 libxmu-dev libglu1-mesa-dev \
    libgl2ps-dev libxi-dev libzip-dev libpng-dev \
    libcurl4-gnutls-dev libfontconfig1-dev libsqlite3-dev \
    libglew-dev libssl-dev libgtk-3-dev binutils xorg-dev
python2.7 download-deps.py
cd build
./install-deps-linux.sh
```

2. Install PulseAudio for audio playback. However, be aware that PulseAudio currently has a bug that may cause it to crash when too many sound effects are played simultaneously.
```shell
sudo apt install pulseaudio
```

1. Modify `Plants-Vs-Zombies/Resources/resources/Text/TextPath.xml`, changing the absolute paths according to your cloned project.

2. Compile and run the project. Note that a copy of the game assets from the `Resources` directory will be placed in the build/bin/pvz directory.
```shell
mkdir build && cd build
cmake ..
make
cd bin/pvz
./pvz
```

## Game Asset
***Note: The game asset files are for learning purposes only. Do not use them for commercial purposes. If there is any infringement, please contact me.***

## Documentation
The `docs` folder contain the chinese documentation, making it easy to quickly understand the project. English documentation currently is unavailable.

## Development In Progress
Due to time constraints, features such as game progress saving and level unlocking are still under development. Additionally, considering the project's scale, further adjustments will be made in the future.

## Contacts
**QQ: 1712475147** <br>
**Email: xi_gong@foxmail.com** <br>
