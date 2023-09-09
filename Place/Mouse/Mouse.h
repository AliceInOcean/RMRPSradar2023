//
// Created by plusseven on 23-7-16.
//

#ifndef RADAR_GIT_NEW_MOUSE_H
#define RADAR_GIT_NEW_MOUSE_H

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class Mouse {
public:
    ~Mouse(){};
    Mouse (){};
    int flag_num = 0;
    int flag_back = 0;
    int point2d_mouse_xy[10][2];
    cv::Mat image;
    cv::Mat temp_image;
    cv::VideoCapture cap;
    std::string camera_winname;

    int pointNumber;
};

void onMouse(int event, int x, int y, int flags, void *para);

#endif //RADAR_GIT_NEW_MOUSE_H
