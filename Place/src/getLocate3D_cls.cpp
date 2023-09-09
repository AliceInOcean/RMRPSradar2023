//
// Created by plusseven on 23-7-15.
//

#include "../include/Place.h"



int initornot(std::array<cv::Point2f,10> predict2d ,cv::Point xy){
    Eigen::Vector3d p1,p2;
    Eigen::Vector3d x1,x2;

    for(int i=0;i<10;i++){
        if(predict2d[i+1]==cv::Point2f(0,0)){
            p1 = p2;
            x1 = x2;
            p2 << (predict2d[0].x-xy.x),(predict2d[0].y-xy.y),0;
            x2 = p1.cross(p2);
        }
        else if(i==0){
            p1 << (predict2d[0].x-xy.x),(predict2d[0].y-xy.y),0;
            p2 << (predict2d[1].x-xy.x),(predict2d[1].y-xy.y),0;
            x2 = p1.cross(p2);
            continue;
        }
        else{
            p1 = p2;
            x1 = x2;
            p2 << (predict2d[i+1].x-xy.x),(predict2d[i+1].y-xy.y),0;
            x2 = p1.cross(p2);
        }
        if(x2.z()*x1.z()<0) return -1;
    }

    return 1;
}



void solve_reality_3d(Place &place,Car &car){
    double a = place.count.R.at<double>(0,0);
    double b = place.count.R.at<double>(0,1);
    double c = place.count.R.at<double>(0,2);

    double d = place.count.R.at<double>(1,0);
    double e = place.count.R.at<double>(1,1);
    double f = place.count.R.at<double>(1,2);

    double g = place.count.R.at<double>(2,0);
    double h = place.count.R.at<double>(2,1);
    double i = place.count.R.at<double>(2,2);

    double tx = place.count.t.at<double>(0,0);
    double ty = place.count.t.at<double>(1,0);
    double tz = place.count.t.at<double>(2,0);

    double Hight = 0;

    double A;
    double B;

    int in_where;

    double Z;

    Eigen::Matrix<double,2,1> matrix_2d_xy;
    Eigen::Matrix<double,2,1> matrix_2d_getxy;

    double X,Y;

    ////TODO:maybe is useless
    for(int m=0;m < place.all_point_3d_number.size();m++){
//        std::cout << place.all_point_predict_2d[4].at(2).x << std::endl;
        in_where = initornot( place.all_point_predict_2d[m], car.Locate2D) ; //cv::pointPolygonTest 点xy 是否在 xxx中

        if(in_where!=-1){
            if(m==place.redfly[0] || m==place.redfly[1] ||  m==place.redfly[2]) place.redfly[4] = 1;
            else place.redfly[4] = -1;
            if(m==place.bluefly[0] || m==place.bluefly[1] ||  m==place.bluefly[2]) place.bluefly[4] = 1;
            else place.bluefly[4] = -1;

            if(place.all_point_predict_2d[m].size() == 3){
                Hight = 0.2;
                break;
            }
            matrix_2d_xy << (car.Locate2D.x - place.all_point_predict_2d[m].at(1).x),(car.Locate2D.y- place.all_point_predict_2d[m].at(1).y);

            matrix_2d_getxy = place.matrix_change2[m].inverse() * matrix_2d_xy;
            matrix_2d_getxy = place.matrix_change3[m] * matrix_2d_getxy + place.matrix_2d[m];

            X = matrix_2d_getxy.x();
            Y = matrix_2d_getxy.y();
//            return {int(X),int(Y)};
            Hight = place.getH_abc_3d[m].at(0) * X + place.getH_abc_3d[m].at(1) * Y + place.getH_abc_3d[m].at(2);
//            std::cout << "m=" << m << std::endl;
            break;
        }

    }

//    std::cout << "Hight:" << Hight << std::endl;
    A = (car.Locate2D.x-place.count.cx)/place.count.fx;
    B = (car.Locate2D.y-place.count.cy)/place.count.fy;

    Z = (a-A*g)*(e-B*h)-(d-B*g)*(b-A*h);

    if(Z == 0){}
    else{
        car.Locate3D.x = (((A*i-c)*Hight+(A*tz-tx))*(e-B*h)-((B*i-f)*Hight+(B*tz-ty))*(b-A*h))/Z;
        car.Locate3D.y = ((a-A*g)*((B*i-f)*Hight+(B*tz-ty))-(d-B*g)*((A*i-c)*Hight+(A*tz-tx)))/Z;
//            std::cout << configByself.x_world << "," << configByself.y_world << std::endl;
//
    }

//    return cv::Point2d (configByself.x_world,configByself.y_world);
}

int get_cls(Car &car,std::vector<Armor> &armors){
    //这里将数组大小定义成10是为了方便调用函数initornot， 实际上大小定义成4就足够了
    std::array<cv::Point2f,10> car_4angle ;
    car_4angle[0] = cv::Point2f (float (car.x1),float (car.y1));
    car_4angle[1] = cv::Point2f (float (car.x2),float (car.y1));
    car_4angle[2] = cv::Point2f (float (car.x2),float (car.y2));
    car_4angle[3] = cv::Point2f (float (car.x1),float (car.y2));
//    std::cout << armors[0].x1;
    int state;float temp_conf = 0;car.cls = 12;
    for(auto &armor : armors){
        state = -1;
        state = initornot(car_4angle,cv::Point (armor.Locate2D.x,armor.Locate2D.y));
        if(state == 1 && armor.conf > temp_conf){
            temp_conf = armor.conf;
            car.cls = armor.cls;
        }
    }

//    for(int i = 0;i < armors.size();i++)
//    {
//
//        state = -1;
//        state = initornot(car_4angle,cv::Point (armors[i].Locate2D.x,armors[i].Locate2D.y));
//        if(state == 1 && armors[i].conf > temp_conf){
//            temp_conf = armors[i].conf;
//            car.cls = armors[i].cls;
//        }
//    }

}

void getLocate3D_cls(Place &place,std::vector<Car> &cars,std::vector<Armor> &armors){
    for(Car &car : cars){
        solve_reality_3d(place,car);
//        get_cls(car,armors);  若把以下内容变成方法，则会报错，不知道原因ing
        //这里将数组大小定义成10是为了方便调用函数initornot， 实际上大小定义成4就足够了
        std::array<cv::Point2f,10> car_4angle ;
        car_4angle[0] = cv::Point2f (float (car.x1),float (car.y1));
        car_4angle[1] = cv::Point2f (float (car.x2),float (car.y1));
        car_4angle[2] = cv::Point2f (float (car.x2),float (car.y2));
        car_4angle[3] = cv::Point2f (float (car.x1),float (car.y2));
        int state;float temp_conf = 0;car.cls = 12;
        for(auto &armor : armors){
            state = -1;
            state = initornot(car_4angle,cv::Point (armor.Locate2D.x,armor.Locate2D.y));
            if(state == 1 ){
                car.ArmorsInCar.push_back(armor);
                if (armor.conf > temp_conf){
                    temp_conf = armor.conf;
                    car.cls = armor.cls;
                }
            }

        }
    }
};