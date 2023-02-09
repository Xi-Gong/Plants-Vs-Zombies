# Plants-Vs-Zombies
## 前言 <br>
这个植物大战僵尸项目是基于cocos2dx的，最初由LZ开发并[发布在Github](https://github.com/ErLinErYi/PlantsVsZombies)。该项目是目前我所看到的开源的，效果最好的，功能最全的植物大战僵尸项目。由于有在Ubuntu平台下写C++练手项目的需求，因此基于该项目进行了一些改进和调整，并重新发布。

## 项目简介 <br>
我学习了该项目，发现了以下需要改进的要点:
- LZ项目在Windows下使用Visual Studio 2017上搭建，其中通过.vcxproj管理项目文件。然而，由于Visual Studio并非免费开源的软件，而且手动配置比较繁琐，并不利于该项目的推广。
- 项目的C++代码约有18000行左右，功能非常齐全，但是有些过于庞大了，不利于初学者学习。
- 项目的部分资源文件通过代码进行了加密，不利于项目的理解。
- 采用的C++11标准已经开始过时了。

针对以上需要改进的要点，我做了如下变动:
- 由于cocos2dx原生支持CMake配置，因此使用CMake 3.6配置该项目。
- 使用开源的QtCreator 5.12开发，安装方便，配置迅速。
- 删减了一些次要的游戏效果和功能，将项目规模缩小到8000行C++代码，便于初学者学习。
- 项目的资源文件全部进行了解密，并且以明文存储和读写。
- 对cocos2dx库和项目代码应用C++17标准。

最后基于我对C++的理解，对本项目的基础类重新进行了设计，包括类与类之间的解耦，语义的明确和C++17语法的应用。

## 项目类图
这里由于我对基础类进行了一些修改，并绘制了相应的UML图。完整的UML图请参见LZ的项目。
![ClassDiagram](https://github.com/Xi-Gong/Plants-Vs-Zombies/blob/main/pvzBasicClassUML.png?raw=true)

## 运行示例
![Image(图片)](https://img-blog.csdnimg.cn/20200405101902466.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQwNjMwMjQ2,size_16,color_FFFFFF,t_70)


## 运行要求
* Ubuntu 20.04或者更新版本。
* [QtCreator 5.12](https://www.qt.io/offline-installers)或其他支持CMake的IDE。<br>

## 安装依赖
编译项目前需要安装必要的依赖。

安装编译cocos2dx需要的依赖。如果想了解更多，可以参考cocos2dx项目中的install-deps-linux.sh文件。
```shell
sudo apt install libxmu-dev libglu1-mesa-dev libgl2ps-dev libxi-dev libzip-dev libpng-dev libcurl4-gnutls-dev libfontconfig1-dev libsqlite3-dev libglew-dev libssl-dev libgtk-3-dev binutils xorg-dev
```

安装pulse audio用于播放音频。
```shell
sudo apt install pulseaudio
```

## 游戏素材
运行本项目的游戏素材文件暂未上传，如有需要请先点亮星星，联系我时截图证明。另外如有侵权，请联系我。

***注意！！！游戏素材文件仅用于学习，切勿用于商业用途***

## 完整文档
docs文件夹下包含所有的文档，便于快速了解该项目。

### Lyx
docs/output下有lyx格式的文档，需要使用[Lyx软件](https://www.lyx.org/)打开它。为了方便预览，我导出了pdf格式的文档，如果需要更好的浏览体验，请下载Lyx。

### Star UML
docs/pvzUML.mdj是项目中重要基础类的UML图，需要使用staruml软件打开。

## 联系方式
**Author: Xi-Gong** <br>
**QQ: 1712475147** <br>
**Email: xi_gong@foxmail.com** <br>