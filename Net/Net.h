//
// Created by plusseven on 23-7-15.
//

#ifndef RADAR2023_WITHTRT_NET_H
#define RADAR2023_WITHTRT_NET_H

#include  "../general/general.h"
#include "sample/include/main.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"

class Net {
public:
    std::string onnx_path;
    std::string trt_path;

    TRTInferV1::TRTInfer myInfer;

    float obj_thres;
    float conf_thres;//置信度阀值
    float nms_thres; //非极大值抑制阀值
    int batch_size;
    int num_class;

    int input_h;
    int input_w;

    Net() = default;
    Net(Modes &modes) {
        this->onnx_path = modes.onnx_path;
        this->trt_path  = modes.trt_path;
        this->obj_thres = modes.obj_thres;
        this->conf_thres = modes.conf_thres;
        this->nms_thres  = modes.nms_thres;
        this->batch_size = modes.batch_size;
        this->num_class  = modes.num_class;
        this->input_h = modes.input_h;
        this->input_w = modes.input_w;


    //神经网络初始化
        myInfer.getDevice(0);
        const char* temp_trtpath = modes.trt_path.c_str();
        if(access(temp_trtpath, F_OK) != 0){
             nvinfer1::IHostMemory *data = myInfer.createEngine(this->onnx_path, this->batch_size, this->input_h, this->input_w);
             myInfer.saveEngineFile(data, this->trt_path);
        }
        myInfer.initModule(this->trt_path, this->batch_size, this->num_class);
    }

};
void NetWork(Net &net,cv::Mat src2,std::vector<std::vector<TRTInferV1::DetectionObj>> &DetectionObjs);
void Car_Armor(Net &net,std::vector<std::vector<TRTInferV1::DetectionObj>> &DetectionObjs,std::vector<Car> &cars,std::vector<Armor> &armors);

#endif //RADAR2023_WITHTRT_NET_H
