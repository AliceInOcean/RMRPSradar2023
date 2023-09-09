//
// Created by plusseven on 23-7-15.
//

#include "general.h"
#include <yaml-cpp/yaml.h>


Modes::Modes(){
    //choose  一些选项

/////////////////////////////////////////////////////////////////////////////////////////////////////////
////------------------------------------- 这里需要修改！！！！---------------------------------------------|
    pictureSource = PictureSource::single_picture;    //图片来源          |
    useCamera     = Cameras::Hikang;                  //所使用的相机    |
    ourPattern    = OurPattern::red;                  //己方颜色       |
    Port_isOpen   = TF::false_;                       //串口的开启与否  |
    usePort       = UsePort::USB0;                    //所使用的串口    |
    Image_isSave  = TF::false_;                       //是否保存图片    |
    saveImagePath = SaveImagePath::disk02;            //保存路径       |


    YAML::Node config = YAML::LoadFile("../config.yaml");

    // int cls to string
    {
        cls_to_string[0] = "RG";
        cls_to_string[1] = "R1";
        cls_to_string[2] = "R2";
        cls_to_string[3] = "R3";
        cls_to_string[4] = "R4";
        cls_to_string[5] = "R5";
        cls_to_string[6] = "BG";
        cls_to_string[7] = "B1";
        cls_to_string[8] = "B2";
        cls_to_string[9] = "B3";
        cls_to_string[10] = "B4";
        cls_to_string[11] = "B5";
        cls_to_string[12] = "car";
    }

    ////相机参数（K）
    {
        if(useCamera == Cameras::Hikang || useCamera == Cameras::Hikang30 ) //Hik2430
            K=(cv::Mat_<double>(3, 3)<<1703.57857839016	,0,776.621431609538,0,1698.69114037183,558.752840063006,0,0,1);
        else if(useCamera == Cameras::Hikang31)  //Hik2431
            K=(cv::Mat_<double>(3, 3)<<1743.66046621871,0,740.287308924314,0,1743.65166453626,545.002856249249,0,0,1);
        else if(useCamera == Cameras::Dahang || useCamera == Cameras::DahangHikang)
            std::cerr << "don't have DangHeng SDK";
        else{ //30
            K=(cv::Mat_<double>(3, 3)<<1703.57857839016	,0,776.621431609538,0,1698.69114037183,558.752840063006,0,0,1);
            std::cout << "not choose K,have used Hik30,please choose" << std::endl;
        }
    }

////------------------------------------------------------------------------------------------|
///////////////////////////////////////////////////////////////////////////////////////////////


    ////图片来源
    //pictureSource = PictureSource::single_picture;

    //// Camera_
    //useCamera  =  Cameras::Hikang31;
    ////net
    trt_path = config["net"]["trt_path"].as<std::string>();
    onnx_path = config["net"]["onnx_path"].as<std::string>();
    obj_thres  = config["net"]["obj_thres"].as<float>();
    conf_thres = config["net"]["conf_thres"].as<float>();
    nms_thres  = config["net"]["nms_thres"].as<float>();
    batch_size = config["net"]["batch_size"].as<int>();
    num_class  = config["net"]["num_class"].as<int>();
    //// place
    //ourPattern =  OurPattern::red;
    //// Port
    //Port_isOpen = TF::true_;
    //usePort =  UsePort::USB0;
    //// Image
    //Image_isSave = TF::true_;
    //saveImagePath = SaveImagePath::ssdgaoyuan;
    mapImage_path = config["background"]["mapPath"].as<std::string>();
    camera_winname = "radar";
    mapImage_winname = "map";

    input_w = config["input"]["picture_size"]["input_w"].as<int>();
    input_h = config["input"]["picture_size"]["input_h"].as<int>();

    start_picture = config["input"]["source_path"]["picture_dir_start"].as<int>();

    {   //pictureSource config
        if(pictureSource == PictureSource::single_picture){
        //  image_path = "/home/plusseven/桌面/radar2023_withtrt/radar_val_picture/6.jpg";
            image_path = config["input"]["source_path"]["singleImg_path"].as<std::string>();
        }
        else if(pictureSource == PictureSource::picture_dir){
        //                image_dir =  "/home/plusseven/桌面/radar2023/radar_val_picture/";
            image_dir =  config["input"]["source_path"]["picture_dir"].as<std::string>();
        }
        else if(pictureSource == PictureSource::video){
        //  video_path = "/media/plusseven/4E21-0000/2023radarData/important/adapt1.mp4";
            video_path =  config["input"]["source_path"]["video_path"].as<std::string>();
        }
        else   Cam_isOpen = true;
    }




    // config->config//can not change ecpect out
    if(ourPattern == OurPattern::red)       selfColor = "red";
    else if(ourPattern == OurPattern::blue) selfColor = "blue";
    if(Port_isOpen == TF::true_)            Port_isopen = true;
    else if(Port_isOpen == TF::false_)      Port_isopen = false;
    if(Port_isopen && usePort == UsePort::USB0)                 port_path = "/dev/ttyUSB0";
    else if(Port_isopen && usePort == UsePort::USB1)            port_path = "/dev/ttyUSB1";
    if(Image_isSave == TF::true_)            Image_issave = true;
    else if(Image_isSave == TF::false_)      Image_issave = false;
    if(saveImagePath == SaveImagePath::disk02)                  Image_savepath = config["ImageSavePath"]["disk02"].as<std::string>();
    else if(saveImagePath == SaveImagePath::ssdgaoyuan)         Image_savepath = config["ImageSavePath"]["ssdgaoyuan"].as<std::string>();




}