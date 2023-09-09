//
// Created by plusseven on 23-7-16.
//

#include "Mouse.h"

//----------------鼠标回调函数---------------------------------
void onMouse(int event, int x, int y, int flags, void *para){
//    mouse.image = *((cv::Mat*)para);
    Mouse &mouse = *((Mouse*)para);
//    std::cout << "in mouse" << std::endl;
//    cv::Mat &image = *(cv::Mat *)para;

    //TODO:problem,here
//    if(event==cv::EVENT_LBUTTONDOWN && flags == cv::EVENT_FLAG_CTRLKEY && flag_back>0){
//                    std::cout << point2d_mouse_xy[flag_num][0] << point2d_mouse_xy[flag_num][1] << std::endl;
//        point2d_mouse_xy[flag_num][0]=0;
//        point2d_mouse_xy[flag_num][1]=0;
//                    std::cout << point2d_mouse_xy[flag_num][0] << point2d_mouse_xy[flag_num][1] << std::endl;
//        flag_back = 0;
//        flag_num = flag_num - 1;
//        cv::imshow("window_radar", temp_image);
//    }
    if(event==cv::EVENT_LBUTTONDOWN) {   //左键按下
//        setPoint2d_mouse_xy(x, y);
        if(mouse.flag_num<mouse.pointNumber){                       //确定pose
            mouse.temp_image = mouse.image.clone();
            mouse.point2d_mouse_xy[mouse.flag_num][0] = x;
            (mouse.point2d_mouse_xy)[mouse.flag_num][1] = y;

            cv::circle(mouse.image, cv::Point(x, y),
                       1, cv::Scalar(0, 255, 250), 1);
                        std::cout << x << y << std::endl;
//            std::cout << mouse.point2d_mouse_xy[mouse.flag_num][0] << mouse.point2d_mouse_xy[mouse.flag_num][1]
//                      << std::endl;

            cv::putText(mouse.image, (std::to_string(x) + "," + std::to_string(y)),
                        cv::Point(x + 10, y + 10), cv::FONT_HERSHEY_PLAIN, 0.7, cv::Scalar(0, 255, 250), 1);
            cv::imshow(mouse.camera_winname, mouse.image);
            mouse.flag_num = mouse.flag_num + 1;
            mouse.flag_back = 1;
            std::cout << mouse.flag_num << std::endl;
        }
//        else{                                       ////目标点
//            mouse.goal_point = cv::Point(x,y);
//            cv::circle(mouse.image,mouse.goal_point,1, cv::Scalar(0, 255, 0), 3);
//            cv::putText(mouse.image, (std::to_string(x) + "," + std::to_string(y)),
//                    cv::Point(x + 10, y + 10), cv::FONT_HERSHEY_PLAIN, 0.7, cv::Scalar(0, 255, 250), 1);
//            cv::imshow(winname, mouse.image);
//        }

    }
}


//也许可以用来调试的 main 函数
//    int main()
//    {
//        Mouse *mouse = new Mouse();
//        cv::namedWindow("window_radar");
//        image = cv::imread("/home/pulssven/桌面/radar/something/dog_cat.jpg");
//        cv::setMouseCallback("window_radar", onMouse, &(mouse));
//        cv::imshow("window_radar", image);
//        cv::waitKey(0);
//
//        return 0;
//    }