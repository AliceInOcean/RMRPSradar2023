//
// Created by plusseven on 23-7-15.
//


#include "../include/Place.h"


void input_point(Place &place) {

    ////-------------正式场地---- start -------

    if(place.selfColor == "red"){
        place.pts_pnp_3d.emplace_back(cv::Point3d(9.47097-0.649, 9.06324-0.433, 0.615));
        place.pts_pnp_3d.emplace_back(cv::Point3d(9.47098-0.649, 9.72324-0.433, 0.615));
//        place.pts_pnp_3d.emplace_back(cv::Point3d(17.30477-0.649, 13.06757-0.433, 1.4724));
        place.pts_pnp_3d.emplace_back(cv::Point3d(22.13425-0.649,15.48899-0.433, 0.2));

        place.pts_pnp_3d.emplace_back(cv::Point3d(25.87255-0.649, 15.48858-0.433, 0.4));
//        place.pts_pnp_3d.emplace_back(cv::Point3d(26.67680-0.649, 7.98879-0.433, 1.02094));
        place.pts_pnp_3d.emplace_back(cv::Point3d(24.17254-0.649, 2.10967-0.433, 0.4));
        place.pts_pnp_3d.emplace_back(cv::Point3d(10.90243-0.649, 7.60410-0.433, 0.6));
    }
    else if(place.selfColor == "blue"){
        place.pts_pnp_3d.emplace_back(cv::Point3d(19.86332-0.649,6.83851 -0.433, 0.615));
        place.pts_pnp_3d.emplace_back(cv::Point3d(19.86332-0.649, 6.17851-0.433, 0.615));
//        place.pts_pnp_3d.emplace_back(cv::Point3d(11.99050-0.649,2.91068-0.433, 1.47244));
        place.pts_pnp_3d.emplace_back(cv::Point3d(7.16102-0.649,0.48926-0.433, 0.2));

        place.pts_pnp_3d.emplace_back(cv::Point3d(3.42256-0.649,0.58967-0.433, 0.4));
//        place.pts_pnp_3d.emplace_back(cv::Point3d(1.3232-0.649, 7.01121-0.433, 1.02094));////
        place.pts_pnp_3d.emplace_back(cv::Point3d(5.12274-0.649,13.86857-0.433,0.4));
        place.pts_pnp_3d.emplace_back(cv::Point3d(18.39284-0.649, 8.37415-0.433, 0.6));
    }
    else{
        std::cerr << "have error when choose place mode" << std::endl;
    }

    //pts_reality_3d
    std::array<Eigen::Matrix<double, 3, 1>,10> temp_onegroup_points;
////场地围挡在红方补给站附近的交点为坐标原点，沿场地长边向蓝方为 X 轴正方向，沿场地短边向红方停机坪为 Y 轴正方向
// 左上，顺时针


//左下
    //4.高地      1
    place.all_point_3d_number.push_back(4);
    temp_onegroup_points.at(0) = ((Eigen::Matrix<double, 3, 1>(8.36755-0.649,3.02923-0.433	,0.85)));
    temp_onegroup_points.at(1) = ((Eigen::Matrix<double, 3, 1>(9.93594-0.649,3.02921-0.433	,0.85)));
    temp_onegroup_points.at(2) = ((Eigen::Matrix<double, 3, 1>(9.93592-0.649,1.77921-0.433	,0.85)));
    temp_onegroup_points.at(3) = ((Eigen::Matrix<double, 3, 1>(8.36755-0.649,1.77923-0.433	,0.85)));
    place.all_point_reality_3d.push_back(temp_onegroup_points);

    //3.高地上坡
//    place.all_point_3d_number.push_back(4);
//    temp_onegroup_points.at(0) = ((Eigen::Matrix<double, 3, 1>(3.42256-0.649,2.11079-0.433	,0.4)));
//    temp_onegroup_points.at(1) = ((Eigen::Matrix<double, 3, 1>(5.12269-0.649,2.07211-0.433	,0.4)));
//    temp_onegroup_points.at(2) = ((Eigen::Matrix<double, 3, 1>(5.12269-0.649,4.61001-0.433	,0.4)));
//    temp_onegroup_points.at(3) = ((Eigen::Matrix<double, 3, 1>(5.30273-0.649,4.73386-0.433	,0.4)));
//    place.all_point_reality_3d.push_back(temp_onegroup_points);


    //2.平地      2
    place.all_point_3d_number.push_back(5);
//    temp_onegroup_points.at(0) = ((Eigen::Matrix<double, 3, 1>(3.42256-0.649,2.11079-0.433	,0.4)));
//    temp_onegroup_points.at(1) = ((Eigen::Matrix<double, 3, 1>(5.12269-0.649,2.07211-0.433	,0.4)));

    temp_onegroup_points.at(0) = ((Eigen::Matrix<double, 3, 1>(5.12269-0.649,3.17923-0.433	,0.4)));
    temp_onegroup_points.at(1) = ((Eigen::Matrix<double, 3, 1>(5.12269-0.649,4.61001-0.433	,0.4)));
    temp_onegroup_points.at(2) = ((Eigen::Matrix<double, 3, 1>(5.30273-0.649,4.73386-0.433	,0.4)));
    temp_onegroup_points.at(3) = ((Eigen::Matrix<double, 3, 1>(7.36948-0.649,4.77172-0.433	,0.4)));
    temp_onegroup_points.at(4) = ((Eigen::Matrix<double, 3, 1>(8.48452-0.649,3.17923-0.433	,0.4)));
//    temp_onegroup_points.at(5) = ((Eigen::Matrix<double, 3, 1>(6.43811-0.649,3.14137-0.433	,0.4)));
//    temp_onegroup_points.at(7) = ((Eigen::Matrix<double, 3, 1>(6.41834-0.649,0.48927-0.433	,0.4)));
//    temp_onegroup_points.at(8) = ((Eigen::Matrix<double, 3, 1>(3.42256-0.649,0.58967-0.433	,0.4)));
    place.all_point_reality_3d.push_back(temp_onegroup_points);

    //1.上坡      4
//    place.all_point_3d_number.push_back(4);  // 点的个数
//    temp_onegroup_points.at(0) << ((Eigen::Matrix<double, 3, 1>{3.42256-0.649,3.99189-0.433	,0   }));
//    temp_onegroup_points[1] =     ((Eigen::Matrix<double, 3, 1>(4.91978-0.649,3.99187-0.433	,0   )));
//    temp_onegroup_points.at(2) =  ((Eigen::Matrix<double, 3, 1>(4.90874-0.649,2.11001-0.433	,0.4 )));
//    temp_onegroup_points[3] <<    ((Eigen::Matrix<double, 3, 1>(3.42256-0.649,2.1101-0.433	,0.4 )));
//    place.all_point_reality_3d.push_back(temp_onegroup_points);



    //5.平地下坡    3
    place.all_point_3d_number.push_back(4);
    temp_onegroup_points.at(0) = ((Eigen::Matrix<double, 3, 1>(7.16104-0.649,1.62926-0.433	,0.2 )));
    temp_onegroup_points.at(1) = ((Eigen::Matrix<double, 3, 1>(7.16102-0.649,0.48926-0.433	,0.2 )));
    temp_onegroup_points.at(2) = ((Eigen::Matrix<double, 3, 1>(6.41834-0.649,0.48927-0.433	,0.4 )));
    temp_onegroup_points.at(3) = ((Eigen::Matrix<double, 3, 1>(6.41836-0.649,1.62927-0.433	,0.4 )));
    place.all_point_reality_3d.push_back(temp_onegroup_points);
    place.bluefly[0]= place.all_point_3d_number.size() -1;

    //6.平地平坡    4
    place.all_point_3d_number.push_back(4);
    temp_onegroup_points.at(0) = ((Eigen::Matrix<double, 3, 1>(7.16104	-0.649 ,1.62926	-0.433,0.2   )));
    temp_onegroup_points.at(1) = ((Eigen::Matrix<double, 3, 1>(12.13563 -0.649,1.48917	-0.433    ,0.2   )));
    temp_onegroup_points.at(2) = ((Eigen::Matrix<double, 3, 1>(12.13563 -0.649,0.62917	-0.433    ,0.2   )));
    temp_onegroup_points.at(3) = ((Eigen::Matrix<double, 3, 1>(7.16102	-0.649 ,0.48926	-0.433,0.2   )));
    place.all_point_reality_3d.push_back(temp_onegroup_points);
//    place.flynumber = place.all_point_3d_number.size();
    place.bluefly[1]= place.all_point_3d_number.size() -1;

    //7.飞坡上坡
    place.all_point_3d_number.push_back(4);
    temp_onegroup_points.at(0) = ((Eigen::Matrix<double, 3, 1>(13.17833-0.649,1.48917-0.433	,0.55  )));
    temp_onegroup_points.at(1) = ((Eigen::Matrix<double, 3, 1>(13.17833-0.649,0.62915-0.433	,0.55  )));
    temp_onegroup_points.at(2) = ((Eigen::Matrix<double, 3, 1>(12.13563-0.649,0.62917-0.433	,0.2   )));
    temp_onegroup_points.at(3) = ((Eigen::Matrix<double, 3, 1>(12.13563-0.649,1.48917-0.433	,0.2   )));
    place.all_point_reality_3d.push_back(temp_onegroup_points);
    place.bluefly[2]= place.all_point_3d_number.size() -1;

    //8.平地陡坡    5
    place.all_point_3d_number.push_back(4);
    temp_onegroup_points.at(0) = ((Eigen::Matrix<double, 3, 1>(7.97161-0.649,4.88812	-0.433,0   )));
    temp_onegroup_points.at(1) = ((Eigen::Matrix<double, 3, 1>(8.65988-0.649,3.90513	-0.433,0   )));
    temp_onegroup_points.at(2) = ((Eigen::Matrix<double, 3, 1>(8.48452-0.649,3.17923	-0.433,0.4 )));
    temp_onegroup_points.at(3) = ((Eigen::Matrix<double, 3, 1>(7.36948-0.649,4.77172	-0.433,0.4 )));
    place.all_point_reality_3d.push_back(temp_onegroup_points);

    //4.高地         6
    place.all_point_3d_number.push_back(4);
    temp_onegroup_points.at(0) = ((Eigen::Matrix<double, 3, 1>(20.92753	-0.649,12.94866-0.433,0.85)));
    temp_onegroup_points.at(1) = ((Eigen::Matrix<double, 3, 1>(19.35914	-0.649,12.94866-0.433,0.85)));
    temp_onegroup_points.at(2) = ((Eigen::Matrix<double, 3, 1>(19.35914	-0.649,14.19866-0.433,0.85)));
    temp_onegroup_points.at(3) = ((Eigen::Matrix<double, 3, 1>(20.92753	-0.649,14.19866-0.433,0.85)));
    place.all_point_reality_3d.push_back(temp_onegroup_points);



    //3.高地上坡      24
//    place.all_point_3d_number.push_back(4);
//    temp_onegroup_points.at(0) = ((Eigen::Matrix<double, 3, 1>(20.92753	-0.649,12.94866-0.433,0.85)));
//    temp_onegroup_points.at(1) = ((Eigen::Matrix<double, 3, 1>(20.92753	-0.649,14.19866-0.433,0.85)));
//    temp_onegroup_points.at(2) = ((Eigen::Matrix<double, 3, 1>(22.87693	-0.649,14.19899-0.433,0.4 )));
//    temp_onegroup_points.at(3) = ((Eigen::Matrix<double, 3, 1>(22.87693	-0.649,12.94899-0.433,0.4 )));
//    place.all_point_reality_3d.push_back(temp_onegroup_points);


    //2.平地         7
    place.all_point_3d_number.push_back(5);
//    temp_onegroup_points.at(0) = ((Eigen::Matrix<double, 3, 1>(25.87253	-0.649,13.86786-0.433,0.4 )));
//    temp_onegroup_points.at(1) = ((Eigen::Matrix<double, 3, 1>(24.17248	-0.649,13.86789-0.433,0.4 )));
    temp_onegroup_points.at(0) = ((Eigen::Matrix<double, 3, 1>(24.17248	-0.649,12.79867-0.433,0.4 )));
    temp_onegroup_points.at(1) = ((Eigen::Matrix<double, 3, 1>(24.17248	-0.649,11.35614-0.433,0.4 )));
    temp_onegroup_points.at(2) = ((Eigen::Matrix<double, 3, 1>(24.02248	-0.649,11.20614-0.433,0.4 )));
    temp_onegroup_points.at(3) = ((Eigen::Matrix<double, 3, 1>(21.92557	-0.649,11.20618-0.433,0.4 )));
    temp_onegroup_points.at(4) = ((Eigen::Matrix<double, 3, 1>(20.81054	-0.649,12.79867-0.433,0.4 )));
//    temp_onegroup_points.at(6) = ((Eigen::Matrix<double, 3, 1>(22.87667	-0.649,12.79863-0.433,0.4 )));
//    temp_onegroup_points.at(7) = ((Eigen::Matrix<double, 3, 1>(22.87693	-0.649,15.48898-0.433,0.4 )));
//    temp_onegroup_points.at(8) = ((Eigen::Matrix<double, 3, 1>(25.87255	-0.649,15.48858-0.433,0.4 )));
    place.all_point_reality_3d.push_back(temp_onegroup_points);

    //1.上坡         26
//    place.all_point_3d_number.push_back(4);  // 点的个数
//    temp_onegroup_points.at(0) << ((Eigen::Matrix<double, 3, 1>{25.87249-0.649	,11.98601-0.433	,0  }));
//    temp_onegroup_points[1] =     ((Eigen::Matrix<double, 3, 1>(24.57527-0.649	,11.98603-0.433	,0  )));
//    temp_onegroup_points.at(2) =  ((Eigen::Matrix<double, 3, 1>(24.38631-0.649	,13.86789-0.433	,0.4)));
//    temp_onegroup_points[3] <<    ((Eigen::Matrix<double, 3, 1>(25.87253-0.649	,13.86786-0.433	,0.4)));
//    place.all_point_reality_3d.push_back(temp_onegroup_points);



//左上

    //2.平地1        8
    place.all_point_3d_number.push_back(4);
    temp_onegroup_points.at(0) = ((Eigen::Matrix<double, 3, 1>(3.42247-0.649,15.48934 -0.433  ,0.4 )));
    temp_onegroup_points.at(1) = ((Eigen::Matrix<double, 3, 1>(9.57003-0.649,15.48921 -0.433  ,0.4 )));
    temp_onegroup_points.at(2) = ((Eigen::Matrix<double, 3, 1>(9.57003-0.649,14.34921 -0.433  ,0.4 )));
    temp_onegroup_points.at(3) = ((Eigen::Matrix<double, 3, 1>(3.42247-0.649,13.86932 -0.433  ,0.4 )));
    place.all_point_reality_3d.push_back(temp_onegroup_points);

    //2.平地2         9
    place.all_point_3d_number.push_back(5);
    temp_onegroup_points.at(0) = ((Eigen::Matrix<double, 3, 1>(9.57003-0.649,14.34921 -0.433  ,0.4 )));
    temp_onegroup_points.at(1) = ((Eigen::Matrix<double, 3, 1>(7.3696 -0.649,11.20678 -0.433  ,0.4 )));
    temp_onegroup_points.at(2) = ((Eigen::Matrix<double, 3, 1>(5.30273-0.649,11.20678 -0.433  ,0.4 )));
    temp_onegroup_points.at(3) = ((Eigen::Matrix<double, 3, 1>(5.12269-0.649,11.38686 -0.433  ,0.4 )));
    temp_onegroup_points.at(4) = ((Eigen::Matrix<double, 3, 1>(5.12274-0.649,13.86857 -0.433  ,0.4 )));
    place.all_point_reality_3d.push_back(temp_onegroup_points);

    //1.上坡
//    place.all_point_3d_number.push_back(4);
//    temp_onegroup_points.at(0) = ((Eigen::Matrix<double, 3, 1>(3.42247-0.649,13.86932 -0.433 ,0.4  )));
//    temp_onegroup_points.at(1) = ((Eigen::Matrix<double, 3, 1>(4.90896-0.649,13.86858 -0.433 ,0.4  )));
//    temp_onegroup_points.at(2) = ((Eigen::Matrix<double, 3, 1>(4.80853-0.649,11.98675 -0.433 ,0    )));
//    temp_onegroup_points.at(3) = ((Eigen::Matrix<double, 3, 1>(3.42247-0.649,11.98675 -0.433 ,0    )));
//    place.all_point_reality_3d.push_back(temp_onegroup_points);

    //3.平地下坡        10
    place.all_point_3d_number.push_back(4);
    temp_onegroup_points.at(0) = ((Eigen::Matrix<double, 3, 1>(9.9464-0.649,15.48921 -0.433 ,0.2  )));
    temp_onegroup_points.at(1) = ((Eigen::Matrix<double, 3, 1>(9.9464-0.649,14.34921 -0.433 ,0.2  )));
    temp_onegroup_points.at(2) = ((Eigen::Matrix<double, 3, 1>(9.57003-0.649,14.34921-0.433  ,0.4  )));
    temp_onegroup_points.at(3) = ((Eigen::Matrix<double, 3, 1>(9.57003-0.649,15.48921-0.433  ,0.4  )));
    place.all_point_reality_3d.push_back(temp_onegroup_points);

    //4.低地          11
    place.all_point_3d_number.push_back(4);
    temp_onegroup_points.at(0) = ((Eigen::Matrix<double, 3, 1>(9.9464	-0.649,15.48921-0.433	,0.2  )));
    temp_onegroup_points.at(1) = ((Eigen::Matrix<double, 3, 1>(15.46695	-0.649,15.48911-0.433	,0.2  )));
    temp_onegroup_points.at(2) = ((Eigen::Matrix<double, 3, 1>(15.46693	-0.649,14.34911-0.433	,0.2  )));
    temp_onegroup_points.at(3) = ((Eigen::Matrix<double, 3, 1>(9.9464	-0.649,14.34921-0.433	,0.2  )));
    place.all_point_reality_3d.push_back(temp_onegroup_points);

    //5.低地下坡        12
    place.all_point_3d_number.push_back(4);
    temp_onegroup_points.at(0) = ((Eigen::Matrix<double, 3, 1>(9.9464	-0.649	,14.34921-0.433	,0.2 )));
    temp_onegroup_points.at(1) = ((Eigen::Matrix<double, 3, 1>(12.58992	-0.649 ,14.34972-0.433	,0.2 )));
    temp_onegroup_points.at(2) = ((Eigen::Matrix<double, 3, 1>(11.83377	-0.649 ,13.10547-0.433	,0   )));
    temp_onegroup_points.at(3) = ((Eigen::Matrix<double, 3, 1>(9.19025	-0.649 ,13.10547-0.433	,0   )));
    place.all_point_reality_3d.push_back(temp_onegroup_points);

    //6.平地陡坡？       22
    place.all_point_3d_number.push_back(4);
    temp_onegroup_points.at(0) = ((Eigen::Matrix<double, 3, 1>(8.9755	-0.649	,12.52386-0.433	,0    )));
    temp_onegroup_points.at(1) = ((Eigen::Matrix<double, 3, 1>(8.28719	-0.649 ,11.54089-0.433	,0    )));
    temp_onegroup_points.at(2) = ((Eigen::Matrix<double, 3, 1>(7.82601	-0.649 ,11.86358-0.433	,0.4  )));
    temp_onegroup_points.at(3) = ((Eigen::Matrix<double, 3, 1>(8.51678	-0.649 ,12.84507-0.433	,0.4  )));
    place.all_point_reality_3d.push_back(temp_onegroup_points);



//右上

    //5.平地下坡      13
    place.all_point_3d_number.push_back(4);
    temp_onegroup_points.at(0) = ((Eigen::Matrix<double, 3, 1>(22.13423	-0.649,14.34899-0.433,0.2 )));
    temp_onegroup_points.at(1) = ((Eigen::Matrix<double, 3, 1>(22.13425	-0.649,15.48899-0.433,0.2 )));
    temp_onegroup_points.at(2) = ((Eigen::Matrix<double, 3, 1>(22.87693	-0.649,15.48898-0.433,0.4 )));
    temp_onegroup_points.at(3) = ((Eigen::Matrix<double, 3, 1>(22.87693	-0.649,14.34899-0.433,0.4 )));
    place.all_point_reality_3d.push_back(temp_onegroup_points);
    place.redfly[0]= place.all_point_3d_number.size() -1;

    //6.平地平坡      14
    place.all_point_3d_number.push_back(4);
    temp_onegroup_points.at(0) = ((Eigen::Matrix<double, 3, 1>(22.13423	-0.649,14.34899-0.433,0.2 )));
    temp_onegroup_points.at(1) = ((Eigen::Matrix<double, 3, 1>(17.28173	-0.649,14.48908-0.433,0.2 )));
    temp_onegroup_points.at(2) = ((Eigen::Matrix<double, 3, 1>(17.26175	-0.649,15.34908-0.433,0.2 )));
    temp_onegroup_points.at(3) = ((Eigen::Matrix<double, 3, 1>(22.13425	-0.649,15.48899-0.433,0.2 )));
    place.all_point_reality_3d.push_back(temp_onegroup_points);
    place.redfly[1]= place.all_point_3d_number.size() -1;
//    place.flynumber = place.all_point_3d_number.size();

    //7.飞坡上坡      27
    place.all_point_3d_number.push_back(4);
    temp_onegroup_points.at(0) = ((Eigen::Matrix<double, 3, 1>(16.11695-0.649	,14.4891-0.433	,0.55)));
    temp_onegroup_points.at(1) = ((Eigen::Matrix<double, 3, 1>(16.11695-0.649	,15.3491-0.433	,0.55)));
    temp_onegroup_points.at(2) = ((Eigen::Matrix<double, 3, 1>(17.26175-0.649	,15.34908-0.433	,0.2 )));
    temp_onegroup_points.at(3) = ((Eigen::Matrix<double, 3, 1>(17.28173-0.649	,14.48908-0.433	,0.2 )));
    place.all_point_reality_3d.push_back(temp_onegroup_points);
    place.redfly[2]= place.all_point_3d_number.size() -1;

    //8.平地陡坡      15
    place.all_point_3d_number.push_back(4);
    temp_onegroup_points.at(0) = ((Eigen::Matrix<double, 3, 1>(21.32664-0.649,11.09169-0.433,0    )));
    temp_onegroup_points.at(1) = ((Eigen::Matrix<double, 3, 1>(20.63591-0.649,12.07296-0.433,0    )));
    temp_onegroup_points.at(2) = ((Eigen::Matrix<double, 3, 1>(21.09391-0.649,12.39396-0.433,0.4  )));
    temp_onegroup_points.at(3) = ((Eigen::Matrix<double, 3, 1>(21.78464-0.649,11.41269-0.433,0.4  )));
    place.all_point_reality_3d.push_back(temp_onegroup_points);

//右下


    //2.平地 1         16
    place.all_point_3d_number.push_back(4);
    temp_onegroup_points.at(0) = ((Eigen::Matrix<double, 3, 1>(25.87277-0.649,2.10964-0.433,0.4 )));
    temp_onegroup_points.at(1) = ((Eigen::Matrix<double, 3, 1>(25.87274-0.649,0.48892-0.433,0.4 )));
    temp_onegroup_points.at(2) = ((Eigen::Matrix<double, 3, 1>(19.72524-0.649,0.48903-0.433,0.4 )));
    temp_onegroup_points.at(3) = ((Eigen::Matrix<double, 3, 1>(19.72524-0.649,1.62903-0.433,0.4 )));
    place.all_point_reality_3d.push_back(temp_onegroup_points);

    //2.平地 2        17
    place.all_point_3d_number.push_back(5);
    temp_onegroup_points.at(0) = ((Eigen::Matrix<double, 3, 1>(19.72524-0.649,1.62903-0.433,0.4 )));
    temp_onegroup_points.at(1) = ((Eigen::Matrix<double, 3, 1>(21.92567-0.649,4.77146-0.433,0.4 )));
    temp_onegroup_points.at(2) = ((Eigen::Matrix<double, 3, 1>(24.02258-0.649,4.77142-0.433,0.4 )));
    temp_onegroup_points.at(3) = ((Eigen::Matrix<double, 3, 1>(24.17258-0.649,4.62142-0.433,0.4 )));
    temp_onegroup_points.at(4) = ((Eigen::Matrix<double, 3, 1>(24.17254-0.649,2.10967-0.433,0.4 )));
    place.all_point_reality_3d.push_back(temp_onegroup_points);

    //1.上坡          32
//    place.all_point_3d_number.push_back(4);
//    temp_onegroup_points.at(0) = ((Eigen::Matrix<double, 3, 1>(25.87277	-0.649    ,2.10964 -0.433   ,0.4 )));
//    temp_onegroup_points.at(1) = ((Eigen::Matrix<double, 3, 1>(24.38632	-0.649    ,2.10967 -0.433   ,0.4 )));
//    temp_onegroup_points.at(2) = ((Eigen::Matrix<double, 3, 1>(24.547	-0.649	  ,3.9915-0.433	,0   )));
//    temp_onegroup_points.at(3) = ((Eigen::Matrix<double, 3, 1>(25.8728	-0.649    ,3.9915-0.433		,0   )));
//    place.all_point_reality_3d.push_back(temp_onegroup_points);

    //3.平地下坡       18
    place.all_point_3d_number.push_back(4);
    temp_onegroup_points.at(0) = ((Eigen::Matrix<double, 3, 1>(19.34507-0.649,0.48904-0.433,0.2 )));
    temp_onegroup_points.at(1) = ((Eigen::Matrix<double, 3, 1>(19.34507-0.649,1.62439-0.433,0.2 )));
    temp_onegroup_points.at(2) = ((Eigen::Matrix<double, 3, 1>(19.72524-0.649,1.62903-0.433,0.4 )));
    temp_onegroup_points.at(3) = ((Eigen::Matrix<double, 3, 1>(19.72524-0.649,0.48903-0.433,0.4 )));
    place.all_point_reality_3d.push_back(temp_onegroup_points);

    //4.低地           19
    place.all_point_3d_number.push_back(4);
    temp_onegroup_points.at(0) = ((Eigen::Matrix<double, 3, 1>(19.34507-0.649	,0.48904-0.433	,0.2  )));
    temp_onegroup_points.at(1) = ((Eigen::Matrix<double, 3, 1>(13.82731-0.649	,0.48914-0.433	,0.2  )));
    temp_onegroup_points.at(2) = ((Eigen::Matrix<double, 3, 1>(13.827-0.649	    ,1.62914-0.433	,0.2  )));
    temp_onegroup_points.at(3) = ((Eigen::Matrix<double, 3, 1>(19.34507-0.649	,1.62439-0.433	,0.2  )));
    place.all_point_reality_3d.push_back(temp_onegroup_points);

    //5.低地下坡         20
    place.all_point_3d_number.push_back(4);
    temp_onegroup_points.at(0) = ((Eigen::Matrix<double, 3, 1>(19.34507-0.649,1.62439-0.433	,0.2 )));
    temp_onegroup_points.at(1) = ((Eigen::Matrix<double, 3, 1>(16.8882-0.649,1.62909-0.433	,0.2 )));
    temp_onegroup_points.at(2) = ((Eigen::Matrix<double, 3, 1>(17.68912-0.649,2.77282-0.433	,0   )));
    temp_onegroup_points.at(3) = ((Eigen::Matrix<double, 3, 1>(20.04322-0.649,2.77282-0.433	,0   )));
    place.all_point_reality_3d.push_back(temp_onegroup_points);

    //6.平地陡坡？       34
    place.all_point_3d_number.push_back(4);
    temp_onegroup_points.at(0) = ((Eigen::Matrix<double, 3, 1>(20.31977	-0.649,3.45439-0.433,0   )));
    temp_onegroup_points.at(1) = ((Eigen::Matrix<double, 3, 1>(21.00808	-0.649,4.43736-0.433,0   )));
    temp_onegroup_points.at(2) = ((Eigen::Matrix<double, 3, 1>(21.4668	-0.649,4.11615-0.433,0.4 )));
    temp_onegroup_points.at(3) = ((Eigen::Matrix<double, 3, 1>(20.78095	-0.649,3.13145-0.433,0.4 )));
    place.all_point_reality_3d.push_back(temp_onegroup_points);



    //左中
    //1.低地     1
    place.all_point_3d_number.push_back(3);
    temp_onegroup_points.at(0) = ((Eigen::Matrix<double, 3, 1>(12.58992-0.649	,14.34972-0.433,0.2 )));
    temp_onegroup_points.at(1) = ((Eigen::Matrix<double, 3, 1>(14.29466-0.649	,14.34913-0.433,0.2 )));
    temp_onegroup_points.at(2) = ((Eigen::Matrix<double, 3, 1>(13.65415-0.649	,13.60405-0.433,0.2 )));
    place.all_point_reality_3d.push_back(temp_onegroup_points);
//    if(place.selfColor == "blue"){
        //2.上坡      2
        place.all_point_3d_number.push_back(4);
        temp_onegroup_points.at(0) = ((Eigen::Matrix<double, 3, 1>(12.58992-0.649,14.34972-0.433,0.2  )));
        temp_onegroup_points.at(1) = ((Eigen::Matrix<double, 3, 1>(13.65415-0.649,13.60405-0.433,0.2  )));
        temp_onegroup_points.at(2) = ((Eigen::Matrix<double, 3, 1>(12.66037-0.649,12.18481-0.433,0.6  )));
        temp_onegroup_points.at(3) = ((Eigen::Matrix<double, 3, 1>(11.59548-0.649,12.93047-0.433,0.6  )));
        place.all_point_reality_3d.push_back(temp_onegroup_points);

        //4.下坡      5
        place.all_point_3d_number.push_back(4);
        temp_onegroup_points.at(0) = ((Eigen::Matrix<double, 3, 1>(9.83752	-0.649   ,6.85846-0.433	,0.6   )));
        temp_onegroup_points.at(1) = ((Eigen::Matrix<double, 3, 1>(10.90243	-0.649   ,7.6041-0.433	,0.6   )));
        temp_onegroup_points.at(2) = ((Eigen::Matrix<double, 3, 1>(12.18677	-0.649   ,5.76981-0.433	,0     )));
        temp_onegroup_points.at(3) = ((Eigen::Matrix<double, 3, 1>(11.2186	-0.649   ,5.02417-0.433	,0     )));
        place.all_point_reality_3d.push_back(temp_onegroup_points);
//    }

    //3.高地1        8
    place.all_point_3d_number.push_back(4);
    temp_onegroup_points.at(0) = ((Eigen::Matrix<double, 3, 1>(19.69208-0.649	,5.89405-0.433 ,0.6 )));
    temp_onegroup_points.at(1) = ((Eigen::Matrix<double, 3, 1>(17.69978-0.649	,3.04775-0.433 ,0.6 )));
    temp_onegroup_points.at(2) = ((Eigen::Matrix<double, 3, 1>(16.63489-0.649	,3.79345-0.433 ,0.6 )));
    temp_onegroup_points.at(3) = ((Eigen::Matrix<double, 3, 1>(18.3928-0.649	,6.30397-0.433 ,0.6 )));
    place.all_point_reality_3d.push_back(temp_onegroup_points);
    //3.高地2        9
    place.all_point_3d_number.push_back(5);
    temp_onegroup_points.at(0) = ((Eigen::Matrix<double, 3, 1>(18.3928-0.649	,6.30397-0.433 ,0.6 )));
    temp_onegroup_points.at(1) = ((Eigen::Matrix<double, 3, 1>(18.39284-0.649	,8.37415-0.433 ,0.6 )));
    temp_onegroup_points.at(2) = ((Eigen::Matrix<double, 3, 1>(19.45775-0.649	,9.11978-0.433 ,0.6 )));
    temp_onegroup_points.at(3) = ((Eigen::Matrix<double, 3, 1>(19.69285-0.649	,8.78402-0.433 ,0.6 )));
    temp_onegroup_points.at(4) = ((Eigen::Matrix<double, 3, 1>(19.69208-0.649	,5.89405-0.433 ,0.6 )));
    place.all_point_reality_3d.push_back(temp_onegroup_points);

    //3.高地1      3
    place.all_point_3d_number.push_back(4);
    temp_onegroup_points.at(0) = ((Eigen::Matrix<double, 3, 1>(9.60247-0.649	 ,10.08419-0.433	,0.6  )));
    temp_onegroup_points.at(1) = ((Eigen::Matrix<double, 3, 1>(11.59548-0.649	 ,12.93047-0.433	,0.6  )));
    temp_onegroup_points.at(2) = ((Eigen::Matrix<double, 3, 1>(12.66037-0.649	 ,12.18481-0.433	,0.6  )));
    temp_onegroup_points.at(3) = ((Eigen::Matrix<double, 3, 1>(10.90246-0.649	 ,9.67428 -0.433	,0.6  )));
    place.all_point_reality_3d.push_back(temp_onegroup_points);

    //3.高地2      4
    place.all_point_3d_number.push_back(5);
    temp_onegroup_points.at(0) = ((Eigen::Matrix<double, 3, 1>(10.90246-0.649	 ,9.67428 -0.433	,0.6  )));
    temp_onegroup_points.at(1) = ((Eigen::Matrix<double, 3, 1>(10.90243-0.649	 ,7.6041-0.433		,0.6  )));
    temp_onegroup_points.at(2) = ((Eigen::Matrix<double, 3, 1>(9.83752-0.649	 ,6.85846-0.433	    ,0.6  )));
    temp_onegroup_points.at(3) = ((Eigen::Matrix<double, 3, 1>(9.60242-0.649	 ,7.19423-0.433	    ,0.6  )));
    temp_onegroup_points.at(4) = ((Eigen::Matrix<double, 3, 1>(9.60247-0.649	 ,10.08419-0.433	,0.6  )));
    place.all_point_reality_3d.push_back(temp_onegroup_points);



//右下，顺时针
//右中
    //1.低地        6
    place.all_point_3d_number.push_back(3);
    temp_onegroup_points.at(0) = ((Eigen::Matrix<double, 3, 1>(16.7052	-0.649,1.62909 -0.433,0.2 )));
    temp_onegroup_points.at(1) = ((Eigen::Matrix<double, 3, 1>(14.91789	-0.649,1.62914 -0.433,0.2 )));
    temp_onegroup_points.at(2) = ((Eigen::Matrix<double, 3, 1>(15.82818	-0.649,2.37419 -0.433,0.2 )));
    place.all_point_reality_3d.push_back(temp_onegroup_points);

//    if(place.selfColor == "red"){
        //2.上坡        7
        place.all_point_3d_number.push_back(4);
        temp_onegroup_points.at(0) = ((Eigen::Matrix<double, 3, 1>(16.7052-0.649	,1.62909-0.433	,0.2  )));
        temp_onegroup_points.at(1) = ((Eigen::Matrix<double, 3, 1>(15.82818-0.649	,2.37419-0.433	,0.2  )));
        temp_onegroup_points.at(2) = ((Eigen::Matrix<double, 3, 1>(16.63489-0.649	,3.79345-0.433	,0.6  )));
        temp_onegroup_points.at(3) = ((Eigen::Matrix<double, 3, 1>(17.69978-0.649	,3.04775-0.433	,0.6  )));
        place.all_point_reality_3d.push_back(temp_onegroup_points);

        //4.下坡        10
        place.all_point_3d_number.push_back(4);
        temp_onegroup_points.at(0) = ((Eigen::Matrix<double, 3, 1>(19.45776	-0.649,9.11978	-0.433,0.6  )));
        temp_onegroup_points.at(1) = ((Eigen::Matrix<double, 3, 1>(18.39284	-0.649,8.37415	-0.433,0.6  )));
        temp_onegroup_points.at(2) = ((Eigen::Matrix<double, 3, 1>(17.1085	-0.649,10.20844	-0.433,0    )));
        temp_onegroup_points.at(3) = ((Eigen::Matrix<double, 3, 1>(18.17341	-0.649,10.95407	-0.433,0    )));
        place.all_point_reality_3d.push_back(temp_onegroup_points);
//    }
}


void get_predict_2d(Mouse &mouse,Place &place){
    for (int i = 0; i < place.pts_pnp_3d.size(); i++) {
        place.pts_pnp_2d.push_back(cv::Point2d(mouse.point2d_mouse_xy[i][0], mouse.point2d_mouse_xy[i][1]));
    }

    cv::solvePnP(place.pts_pnp_3d, place.pts_pnp_2d, place.count.K,cv::Mat(), place.count.r, place.count.t, false); // 调用OpenCV 的 PnP 求解，可选择EPNP，DLS等方法
    std::cout << "pnp is ok" << std::endl;

    cv::Rodrigues(place.count.r, place.count.R); // r为旋转向量形式，用Rodrigues公式转换为矩阵

    // 转成可运算的矩阵
    cv::cv2eigen(place.count.R, place.count.R_e);
    cv::cv2eigen(place.count.t, place.count.t_e);

    Sophus::SE3d Rt(place.count.R_e, place.count.t_e);

    for (int i = 0; i < place.all_point_3d_number.size(); i++) {
        std::array<cv::Point2f,10> temp_onegroup_predict_2d;
        for(int j=0;j<place.all_point_3d_number[i];j++){
            Eigen::Vector3d pc = Rt * place.all_point_reality_3d[i][j];
            double inv_z = 1.0 / pc[2];
            double inv_z2 = 1.0 / (inv_z * inv_z);
            Eigen::Vector2d predict(place.count.fx * pc[0] / pc[2] + place.count.cx,place.count.fy * pc[1] / pc[2] + place.count.cy );
//            place.pts_predict_2d.push_back( predict );
//            if((int)predict[0] < 0){predict[0] = 0;}
//            if((int)predict[0] > 1440){predict[0] = 1440;}
//            if((int)predict[1] < 0){predict[1] = 0;}
//            if((int)predict[1] > 1080){predict[1] = 1080;}
            temp_onegroup_predict_2d.at(j) = cv::Point2d((int)predict[0],(int)predict[1]);
        }
        place.all_point_predict_2d.push_back(temp_onegroup_predict_2d);

    }
}


void get_roughH_config(Place &place){

    for(int i=0;i<place.all_point_reality_3d.size();i++){

        std::array<double,3> temp_abc_3d;

        //算出3d平面的表达 //TODO：4个点的顺序必须为 h1,h1,h2,h2
        Eigen::Vector3d p1_3d,p2_3d,p3_3d;
        p1_3d << place.all_point_reality_3d[i].at(0);
        p2_3d << place.all_point_reality_3d[i].at(1);
        p3_3d << place.all_point_reality_3d[i].at(2);
        auto n = (p3_3d-p1_3d).cross(p2_3d-p1_3d);

        Eigen::Matrix<double,2,2> temp_matrix_3d22 ,temp_matrix_2d22;
        Eigen::Matrix<double,2,1> temp_matrix_2d;


        if(n[2]==0){
            temp_matrix_2d22 << 1,0,0,1;
            temp_matrix_3d22 << 1,0,0,1;

            temp_abc_3d.at(0) = 0 ;
            temp_abc_3d.at(1) = 0 ;
            temp_abc_3d.at(2) = double (p3_3d[2]);
            break;

        }
        else{
            temp_abc_3d.at(0) = -(double (n[0]))/(double (n[2]));
            temp_abc_3d.at(1) = -(double (n[1]))/(double (n[2]));
            temp_abc_3d.at(2) = double (p3_3d[2]) - temp_abc_3d.at(0)*p3_3d[0] - temp_abc_3d.at(1)*p3_3d[1];


            //2d点的投射
            temp_matrix_3d22 << (place.all_point_reality_3d[i].at(0)[0]-place.all_point_reality_3d[i].at(1)[0]) ,(place.all_point_reality_3d[i].at(2)[0]-place.all_point_reality_3d[i].at(1)[0]),
                    (place.all_point_reality_3d[i].at(0)[1]-place.all_point_reality_3d[i].at(1)[1]) , (place.all_point_reality_3d[i].at(2)[1]-place.all_point_reality_3d[i].at(1)[1]);

            temp_matrix_2d22 << (place.all_point_predict_2d[i].at(0).x-place.all_point_predict_2d[i].at(1).x) ,(place.all_point_predict_2d[i].at(2).x-place.all_point_predict_2d[i].at(1).x),
                    (place.all_point_predict_2d[i].at(0).y-place.all_point_predict_2d[i].at(1).y) ,(place.all_point_predict_2d[i].at(2).y-place.all_point_predict_2d[i].at(1).y);

            temp_matrix_2d << place.all_point_reality_3d[i].at(1)[0],place.all_point_reality_3d[i].at(1)[1];

//            temp_matrix_2d22 = temp_matrix_3d22 * temp_matrix_2d22.inverse();
        }

        place.getH_abc_3d.push_back(temp_abc_3d);
        place.matrix_change2.push_back(temp_matrix_2d22);
        place.matrix_change3.push_back(temp_matrix_3d22);
        place.matrix_2d.push_back(temp_matrix_2d);
    }

}

void placePostConfig(Mouse &mouse,Place &place){
//    input_point(place);
    get_predict_2d(mouse,place);
    get_roughH_config(place);
}