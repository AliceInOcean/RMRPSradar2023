# RM_Radar2023

中国石油大学（华东）RPS战队2023赛季雷达程序

## 0.前言

**特别感谢沈阳航空航天大学TUP机器人实验室提供的开源程序对本项目的帮助。**

本人c++练习时长不足1年，代码主打一个能跑就行，写的不是很优美，还请多多见谅

## 1.简介

本程序适用采用**单工业相机**方案的雷达站。所用海康MV-CA016-10UC工业相机。

功能：提供场上车辆的定位，飞坡预警？(赛场上未能验证到飞坡预警，但在家测试成功)

## 2.环境配置

* Ubuntu 20.04 LTS
* GCC 9.4.0
* CUDA 11.4
* cudnn 8.6.0
* Tensorrt 8.5.1.7
* OpenCV4.8.0
* Sophus
* fmt
* Eigen3
* yaml-cpp
* 海康相机驱动

运算平台 ：

* Intel Core i5-11400 CPU
* GeForce RTX 3050 Laptop GPU [4GB]

## 3.文件结构

* RPSradar2023
  * Camera 相机
  * docs 中README.md的插图
  * generl    一些通用的类，以及绝大多数参数的初始化
  * Image    主要是用来显示推理结果
  * **Net**
    * sample [ignore]
    * TRTInfer[ignore]
    * Net.cpp
    * Net.h
  * Place     与像素坐标系，世界坐标系有关的一些东东西西，其中Mouse为鼠标事件
  * Port      串口相关
  * something    程序所需的一些东西（eg. 测试图片，onnx...）
  * CMakeLists.txt
  * main.cpp 程序主文件
  * main.h
  * README.md

> - ***sample [ignore]，TRTInfer[ignore]均来源于沈航yolov5开源代码*** [tup-robomaster/TRTInferenceForYolo at yolov5 (github.com)](https://github.com/tup-robomaster/TRTInferenceForYolo/tree/yolov5)
> 
> Tips:在Net\TRTInfer\src\Inference.cpp中需手动添加以下代码(第133行左右)
> 
> ```c++
>     TRTInfer::TRTInfer(){
>     }
> 
>     void TRTInfer::getDevice(const int device) {
>         cudaSetDevice(device);
>     }
> ```

## 4.使用

### 使用前准备

* 环境配置完成后，需根据运算平台及环境修改src下CMakeLists.txt
  
  * 应根据设备显卡型号及其算力修改第20行 CUDA_GEN_CODE 例：RTX 3050 ： -gencode=arch=compute_86, code=sm_86 ; RTX 3070 : -gencode=arch=compute_86, code=sm_86 ; 
  * 具体设备显卡型号对应其算力可参照 [[学习笔记：[Nvidia显卡GPU算力] - 知乎 (zhihu.com)](https://zhuanlan.zhihu.com/p/353518340)] （此处为引用，侵删）

* 

* 修改 general/general.cpp 中提示处的参数
  
  * 共有四种运行模式，分别为{*picture_dir*,*single_picture*,*video*,*camera_*},在general\general.cpp 中的`pictureSource = PictureSource:: ;`修改
  
  * 若使用串口，则必须手动给串口权限，且将general/general.cpp中17行设置为    `Port_isOpen   = TF::false_;`
  
  * 其他参数按照注释以及需求进行更改

* 修改config.yaml中的路径及相关配置
  
  * 本项目只提供了单张图片（*single_picture*）模式下的测试图片,对于其他模式（*picture_dir*, *video*）需自行准备其相对应的文件夹/文件，并修改config.yaml中所对应路径
  
  * 若模式为*picture_dir*，则该路径下的图片名称必须为n.jpg(其中n为自然数且连续)，picture_dir_start为开始图片的序号，若n=1200,则打开图片1200.jpg

* 准备模型，现版本可用模型为yolov5 v6.0，所用部署代码来源于沈阳航空航天大学TUP机器人实验室提供的开源程序（再次感谢沈阳航空航天大学ing）

* class ["RG","R1","R2",“R3”,"R4",“R5”,"BG","B1","B2",“B3”,"B4",“B5”,"car"] (与general/general.cpp 中 cls_to_string 相对应) 

### 运行

运行main.cpp

### 使用

1.若第一次运行，程序会针对运行设备进行Onnx生成Engine的过程，根据设备算力，时间在1～10分钟不等。

2.初始化完成后，进入六点标注界面，按照图片完成标注点选取，成功选取6点后按任意键结束标注，程序开始正常工作。

PS:如果标错了就只能重新开启程序（撤回功能之前没来得及写，之后应该会加上）

Tips: 在Place\src\place_post_cfg.cpp中修改相关3D参数

标注如下图所示：

<img src="docs\标定.png" title="" alt="标定.png" width="361">

运行效果图如图所示：        



<img title="" src="docs\效果图.png" alt="效果图.png" width="362" data-align="left">

4.按’q‘退出程序

> 若模式为*picture_dir*，按’z‘看查看上一张图片，按’x‘可查看下一张图片

5.【不稳定功能未在此列出】



## 5. 赛场效果图

Tips:右下角小地图可看见高亮（黄色小框是自己加的）

（云台手视角不小心丢失了，现在只有工程视角QAQ能够看到其赛场效果）

<img src="docs\赛场高亮.png" title="" alt="赛场高亮.png" width="269">



## 6.其他

在此再次感谢沈阳航空航天大学TUP机器人实验室提供的帮助

感谢视觉组各位学长在我疯狂error时的鼎力相助，以及在我提出各种奇奇怪怪的问题时的耐心解答

感谢王学长提供的地图参数

感谢川哥的对雷达站机械搭建方面的帮助（但是雷达站真的好重啊QAQ）

感谢cmake的不杀之恩（虽然但是半条命已经没了QAQ*2）

*如果觉得有用的话，请点一下右上角的小星星，谢谢*
