//
// Created by plusseven on 23-7-15.
//

#include "Net.h"


void NetWork(Net &net,cv::Mat img ,std::vector<std::vector<TRTInferV1::DetectionObj>> &DetectionObjs )
{                         //radar_cloneimg

    std::vector<cv::Mat> frames;
    frames.push_back(img);
    DetectionObjs = net.myInfer.doInference(frames, net.obj_thres, net.conf_thres, net.nms_thres);
}

void Car_Armor(Net &net,std::vector<std::vector<TRTInferV1::DetectionObj>> &DetectionObjs,std::vector<Car> &cars,std::vector<Armor> &armors){
    for(int i = 0;i < net.batch_size;i++)
        for(int j = 0;j < DetectionObjs[i].size();j++)
        {
            if(DetectionObjs[i][j].classId == 12){
                Car car(DetectionObjs[i][j].confidence,DetectionObjs[i][j].x1,DetectionObjs[i][j].y1,DetectionObjs[i][j].x2,DetectionObjs[i][j].y2);
                cars.push_back(car);
            }

            else{
                Armor armor(DetectionObjs[i][j].confidence,DetectionObjs[i][j].x1,DetectionObjs[i][j].y1,DetectionObjs[i][j].x2,DetectionObjs[i][j].y2,DetectionObjs[i][j].classId);
                armors.push_back(armor);
            }

        }
}