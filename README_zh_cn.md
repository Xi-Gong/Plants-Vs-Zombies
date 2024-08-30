# Plants-Vs-Zombies (LZ Linux版本)
## 前言 <br>
本项目是基于cocos2dx开发的，该项目的原型最初由LZ开发并[发布在Github](https://github.com/ErLinErYi/PlantsVsZombies)。LZ项目是目前我所看到的开源的，效果最好的，功能最全的植物大战僵尸项目。由于有在Ubuntu平台下写C++练手项目的需求，因此基于该项目进行了一些改进和调整，并重新发布。

## 项目简介 <br>
我学习了LZ项目之后，发现了以下可以改进的要点:
- LZ项目在Windows下使用Visual Studio 2017上搭建，其中通过.vcxproj管理项目文件。然而，由于Visual Studio并非免费开源的软件，而且手动配置比较繁琐，并不利于该项目的推广。
- 项目的C++代码约有18000行左右，功能非常齐全，但是有些过于庞大了，不利于初学者学习。
- 采用的C++11标准已经开始过时了。

针对以上需要改进的要点，我做了如下变动:
- 由于cocos2dx原生支持CMake配置，因此使用CMake 3.6配置该项目。
- 使用开源的QtCreator 5.12开发，安装方便，配置迅速。
- 删减了一些次要的游戏效果和功能，将项目规模缩小到8000行C++代码，便于初学者学习。
- 对cocos2dx库和项目代码应用C++17标准。

最后基于我对C++的理解，对本项目的基础类重新进行了设计，包括类与类之间的解耦，语义的明确和C++17语法的应用。

## 项目类图
这里由于我对基础类进行了一些修改，并绘制了相应的UML图。完整的UML图请参见LZ的项目。
![ClassDiagram](https://github.com/Xi-Gong/Plants-Vs-Zombies/blob/main/pvzBasicClassUML.png?raw=true)

## 运行示例
![Image(图片)](https://img-blog.csdnimg.cn/20200405101902466.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQwNjMwMjQ2,size_16,color_FFFFFF,t_70)


## 运行要求
* 目前在Ubuntu 22.04上测试通过，其他Ubuntu版本请自行测试。
* 支持CMake的IDE，如VSCode、QtCreator。<br>

## 安装依赖

1. 克隆本项目，安装cocos2dx所需的依赖。
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

2. 安装pulse audio用于播放音频。
```shell
sudo apt install pulseaudio
```

3. 修改Plants-Vs-Zombies/Resources/resources/Text/TextPath.xml，根据你克隆项目的路径更改其中的绝对路径。

4. 编译并运行项目。注意Resources目录下的内容会拷贝一份到build/bin/pvz目录下。
```shell
mkdir build && cd build
cmake ..
make
cd bin/pvz
./pvz
```

## 游戏素材
***注意！！！游戏素材文件仅用于学习，切勿用于商业用途。如有侵权请联系我***

## 完整文档
docs文件夹下包含中文文档，便于快速了解该项目。

## 部分功能仍在开发中
限于时间，游戏进度存档，关卡逐步解锁等功能尚未完成开发。另外考虑到项目的规模，今后还会进行一些调整。

## 联系方式
**QQ: 1712475147** <br>
**Email: xi_gong@foxmail.com** <br>
