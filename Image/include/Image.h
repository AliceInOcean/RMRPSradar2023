//
// Created by plusseven on 23-7-15.
//

#ifndef RADAR2023_WITHTRT_IMAGE_H
#define RADAR2023_WITHTRT_IMAGE_H

#include  "../../general/general.h"
#include  "../../Place/include/Place.h"

class Image {
public:
    cv::Mat radar_img;
    cv::Mat map_img;
    cv::Mat radar_cloneing;
    cv::Mat radar_draw;
    cv::Mat map_cloneing;
    cv::Mat map_draw;
    cv::VideoCapture cap;
//// from Mode
    Cameras useCamera;
    bool Cam_isOpen = false;

    int input_w,input_h;

    bool Image_issave;
    std::string Image_savepath;

    std::string image_dir;
    std::string image_path;
    std::string video_path;
    std::string camera_winname;

    std::string mapImage_path;
    std::string mapImage_winname;

//// method
    Image() = default;
    Image(Modes &modes){
        this->useCamera  = modes.useCamera;
        this->Cam_isOpen = modes.Cam_isOpen;
        this->image_dir  = modes.image_dir;
        this->image_path = modes.image_path;
        this->video_path = modes.video_path;
        this->camera_winname   = modes.camera_winname;
        this->mapImage_path    = modes.mapImage_path;
        this->mapImage_winname = modes.mapImage_winname;
        this->Image_savepath   = modes.Image_savepath;
        this->Image_issave     = modes.Image_issave;
        this->input_w = modes.input_w;
        this->input_h = modes.input_h;
        if(useCamera == Hikang30 || useCamera == Hikang31)  useCamera = Hikang;
        //窗口配置
        cv::namedWindow(this->camera_winname,0);
        cv::resizeWindow(this->camera_winname,input_w,input_h);
        //小地图相关配置
        cv::namedWindow(this->mapImage_winname,0);
        cv::resizeWindow(this->mapImage_winname,840,450);  ////TODO:
        map_img = cv::imread(this->mapImage_path);
        map_cloneing = map_img.clone();
    }


};

void draw_line(Place &place,cv::Mat &radar_cloneimg);
void draw_rusult(std::vector<Car> &cars,std::vector<Armor> &armors,Image &image,std::map<int,std::string> cls_to_string);
#endif //RADAR2023_WITHTRT_IMAGE_H
