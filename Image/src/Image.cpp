//
// Created by plusseven on 23-7-15.
//

#include "../include/Image.h"

void draw_line(Place &place,cv::Mat &radar_draw){

    for (int i = 0; i < place.all_point_3d_number.size(); i++) {
        for (int j = 0; j < place.all_point_3d_number[i]; j++) {
            if(j < place.all_point_3d_number[i]-1 ){
                cv::line(radar_draw,place.all_point_predict_2d[i][j],place.all_point_predict_2d[i][j+1],cv::Scalar(250-6*i,255-5*i,250-6*i));
            }
            else if(j == place.all_point_3d_number[i]-1 ){
                cv::line(radar_draw,place.all_point_predict_2d[i][j],place.all_point_predict_2d[i][0],cv::Scalar(250-6*i,255-5*i,250-6*i));
            }
            else{
                std::cout << "def draw_line may have error " << std::endl;
            }
        }
    }

}

void draw_rusult(std::vector<Car> &cars,std::vector<Armor> &armors,Image &image,std::map<int,std::string> cls_to_string){
    for(Armor armor:armors){
        cv::rectangle(image.radar_draw,armor.rect,cv::Scalar(75, 150, 225),1);
        cv::putText(image.radar_draw,cls_to_string[armor.cls],cv::Point(armor.x2+10,armor.y1-10),cv::FONT_HERSHEY_SIMPLEX, 1, {225, 150, 75});
    }
    for(Car car:cars){
        if(car.cls < 6){
            cv::rectangle(image.radar_draw,car.rect,cv::Scalar(150, 150, 250),1);
            cv::putText(image.radar_draw,cls_to_string[car.cls],cv::Point(car.x2+10,car.y1-10),cv::FONT_HERSHEY_SIMPLEX, 1, {150, 150, 250});
            circle(image.map_draw,cv::Point(car.Locate3D.x/28*840-15,450-car.Locate3D.y/15*450),0,cv::Scalar(150, 150, 250),15 );
            putText(image.map_draw,cls_to_string[car.cls],cv::Point(car.Locate3D.x/28*840-15,450-car.Locate3D.y/15*450),cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(150, 150, 250), 1);
        }
        else if(car.cls < 12){
            cv::rectangle(image.radar_draw,car.rect,cv::Scalar(255, 150, 150),1);
            cv::putText(image.radar_draw,cls_to_string[car.cls],cv::Point(car.x2+10,car.y1-10),cv::FONT_HERSHEY_SIMPLEX, 1, {255, 150, 150});
            circle(image.map_draw,cv::Point(car.Locate3D.x/28*840-15,450-car.Locate3D.y/15*450),0,cv::Scalar(255, 150, 150),15 );
            putText(image.map_draw,cls_to_string[car.cls],cv::Point(car.Locate3D.x/28*840-15,450-car.Locate3D.y/15*450),cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(255, 150, 150), 1);
        }
        else{
            circle(image.map_draw,cv::Point(car.Locate3D.x/28*840-15,450-car.Locate3D.y/15*450),0,cv::Scalar(150, 150, 150),15 );
            putText(image.map_draw,"unknown",cv::Point(car.Locate3D.x/28*840-15,450-car.Locate3D.y/15*450),cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(150, 150, 150), 1);
        }
        cv::imshow(image.mapImage_winname,image.map_draw);
        cv::imshow(image.camera_winname,image.radar_draw);
    }


}