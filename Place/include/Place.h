//
// Created by plusseven on 23-7-15.
//

#ifndef RADAR2023_WITHTRT_PLACE_H
#define RADAR2023_WITHTRT_PLACE_H

#include  "../../general/general.h"
#include "../Mouse/Mouse.h"
#include <sophus/se3.hpp>


class Count{
public:
    double fx,fy,cx,cy;
    cv::Mat K ;
    cv::Mat dist;
//when get2D
    cv::Mat r, t;
    cv::Mat R;
    Eigen::Matrix<double, 3, 3> R_e ;
    Eigen::Matrix<double, 3, 1> t_e ;

    Count() = default;
    void config(cv::Mat K){
        this->K = K;
        fx = K.at<double>(0, 0);
        fy = K.at<double>(1, 1);
        cx = K.at<double>(0, 2);
        cy = K.at<double>(1, 2);
    }

};


class Place {
public:
//3d点
    std::vector<cv::Point2d> pts_pnp_2d;
    std::vector<cv::Point3d> pts_pnp_3d;

    std::vector<int> all_point_3d_number;
    std::vector<std::array<Eigen::Matrix<double, 3, 1>,10>> all_point_reality_3d;
    std::vector<std::array<cv::Point2f,10>> all_point_predict_2d;

    std::vector<cv::Point2f> pts_predict_2d_point;
// 用来粗率定位的参数
    std::vector<std::array<double,3>> getH_abc_3d;
    std::vector<Eigen::Matrix<double,2,2>> matrix_change2;
    std::vector<Eigen::Matrix<double,2,2>> matrix_change3;
    std::vector<Eigen::Matrix<double,2,1>> matrix_2d;

//
    Count count;

//
    int redfly[5];
    int bluefly[5];

////from mode
    std::string selfColor;
    Place() = default;
    Place(Modes &modes) {
        this->selfColor = modes.selfColor;
        count.config(modes.K);
        //TODO: add dist

    }

};


//post
void placePostConfig(Mouse &mouse,Place &place);
        void input_point(Place &place);
        //void get_predict_2d(Mouse &mouse,Place &place);
        //void get_roughH_config(Place &place);

//every obj
void getLocate3D_cls(Place &place,std::vector<Car> &cars,std::vector<Armor> &armors);
        //int initornot(std::array<cv::Point2f,10> predict2d ,cv::Point xy);
        //void solve_reality_3d(Place &place,Car &car);

#endif //RADAR2023_WITHTRT_PLACE_H
