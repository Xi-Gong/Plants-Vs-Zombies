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
这里由于我对基础类进行了一些修改，因此类图将略有变化，后续将进行更新。
![ClassDiagram](https://gitee.com/GITLZ/PlantsVsZombies/raw/master/ClassDiagram.png)

## 运行示例
![Image(图片)](https://gitee.com/GITLZ/PlantsVsZombies/raw/master/example.png)
![Image(图片)](https://img-blog.csdnimg.cn/20200405101902466.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQwNjMwMjQ2,size_16,color_FFFFFF,t_70)

## 运行要求
* Ubuntu 20.04或者更新版本（本项目在Ubuntu 22.10上搭建，其他版本应该也没有问题）<br>
* QtCreator 5.12（其他版本的QtCreator暂未测试，应该也没有问题），[下载地址](https://www.qt.io/offline-installers)<br>

***注意！！！该项目不能直接运行，因为缺少游戏所需要的资源文件。资源文件后续将发布在谷歌云盘上，仅供学习 ***

## 联系方式
**Author: Xi-Gong** <br>
**QQ: 1712475147** <br>
**Email: xi_gong@foxmail.com** <br>