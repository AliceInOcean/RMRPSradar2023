//
// Created by plusseven on 23-7-15.
//
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/Core>

#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/eigen.hpp>

#include <vector>
#include <sstream>
#include <opencv2/imgproc.hpp>
#include <opencv2/dnn.hpp>
#include <fstream>
#include <sstream>
#include <opencv2/imgproc.hpp>
#include <opencv2/dnn.hpp>



#ifndef RADAR2023_WITHTRT_GENERAL_H
#define RADAR2023_WITHTRT_GENERAL_H

enum TF {true_,false_};
enum PictureSource {picture_dir,single_picture,video,camera_};
enum Cameras       {DahangHikang,Dahang,Hikang,Hikang30,Hikang31};
enum OurPattern    {red,blue};
enum UsePort       {USB0,USB1};
enum SaveImagePath {disk02,ssdgaoyuan};



class Modes {
public:
//-------------------------------------------------------------------------------------------------------//
//                                              可改参数‘s name                                           //
//------------------------------------------------------------------------------------------------------//
PictureSource pictureSource;        //图片来源
//Cameras useCamera;  //相机的开启与否，所使用的相机
OurPattern ourPattern;              //己方颜色
TF Port_isOpen;UsePort usePort;     //串口的开启与否，所使用的串口
TF Image_isSave;SaveImagePath saveImagePath;   //是否保存图片，保存路径

std::map<int,std::string> cls_to_string;

//// Camera_
    Cameras useCamera;  //所使用的相机
    bool Cam_isOpen = false;

////net
//    std::string model_path;
    std::string trt_path ;
    std::string onnx_path ;
    float obj_thres ;
    float conf_thres; //置信度阀值
    float nms_thres ; //非极大值抑制阀值
    int batch_size  ;
    int num_class   ;

//// place
    std::string selfColor;
// 相机参数,but用于场地各种计算
    cv::Mat K ;
    cv::Mat dist;

//// Port
    bool Port_isopen;
    const char *port_path;


//// Image
    int input_w,input_h;////必须与神经网络的输入一致！！！！！！

    bool Image_issave;
    std::string Image_savepath;

    std::string image_dir;
    std::string image_path;
    std::string video_path;
    std::string camera_winname;

    std::string mapImage_path;
    std::string mapImage_winname;

    int start_picture;

    Modes();

};




class Armor{
public:
    //param
    float conf,x1,y1,x2,y2;
    cv::Point2d Locate2D;
    cv::Rect rect;
    int cls;

    Armor(float conf,float x1,float y1,float x2,float y2,int cls){
        this->conf = conf;
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2 ;
        this->y2 = y2 ;
        rect = cv::Rect(cv::Point2d(x1,y1),cv::Point2d(x2,y2) );
        this->cls = cls;
        Locate2D =  cv::Point2f ((x1+x2)/2,(y1+y2)/2);
    }
    Armor() = default;

};


class Car{
public:
    //param
    float conf,x1,y1,x2,y2;
    cv::Point2d Locate2D;
    cv::Point2d Locate3D;
    cv::Rect rect;

    std::vector<Armor> ArmorsInCar;
    int cls;
    //make class
    Car(float conf,float x1,float y1,float x2,float y2){
        this->conf = conf;
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2 ;
        this->y2 = y2 ;
        rect = cv::Rect(cv::Point2d(x1,y1),cv::Point2d(x2,y2) );
        Locate2D = cv::Point2d ((x1+x2)/2,y2 -(y2-y1)/9);
    }
    Car() = default;

};


#endif //RADAR2023_WITHTRT_GENERAL_H
