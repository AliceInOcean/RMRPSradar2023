//
// Created by plusseven on 23-7-15.
//

#include "main.h"

static bool pose = false;           // 姿态估计（p）
static bool start_vedio = false;    // 雷达开始检测(r)

std::string makedir(Image &image);
void getRadar_img(Modes &modes,Image &image);
void recordVedio1(string outPath_half, int pictureName,cv::Mat image);
void recordVedio2(string outPath_half, int pictureName,cv::Mat image);

int main(){
    //当picture_dir会用到
    int start_picture = 1300;

    int after_picture = 0;
    int iiiii = 0;
    double interval_time; double last_time;
    string dynamic_image_path;
    std::string outPath_half;
    std::future<void> future1;    std::future<void> future2;
    std::vector<std::vector<TRTInferV1::DetectionObj>> DetectionObjss;
    std::vector<Car> cars;std::vector<Armor> armors;
//初始化参数
    Modes modes;
//初始化 Place,Net,Image,Port
    Place place(modes);Mouse mouse;
    Net net(modes);
    Image image(modes);
    Port port(modes);
//如果不使用大恒相机，请取消该注释
    //GalaxyCameraReader cameraReader;
//Hikcamera - config
    Camera::HikCamera camera;
    camera.open();
    camera.setExposureTime(10000);
    camera.setGain(1);
// postprepare
    if(modes.pictureSource==video ) image.cap = cv::VideoCapture(image.video_path);

//建一个文件夹
    if(image.Image_issave){
        outPath_half = makedir(image);
        //std::string test_path =   outPath_half+"test/";
        //mkdir((test_path).c_str(), S_IRWXU);
    }
////将地形信息载入
    input_point(place);
// the point of number which need to pnp

    while(true) {

        char ch = cv::waitKey(1);
        auto begin = std::chrono::high_resolution_clock::now();
    //刷新图片map
        cv::imshow(image.mapImage_winname,image.map_img);
    //get new picture
        if(modes.pictureSource==picture_dir)
            dynamic_image_path = image.image_dir + std::to_string(start_picture + after_picture) +".jpg";
    // get picture
        switch (modes.pictureSource) {
                case video:
                    (image.cap).read(image.radar_img);
                    //change image
//                image.image = image.image(cv::Range(476,1500),cv::Range(120,1400));
                    break;
                case camera_:
                    if (image.useCamera == Cameras::Dahang) std::cout << "Maybe Have Error!!!";//  image.radar_img = cameraReader.getframe();
                    else if (image.useCamera == Cameras::Hikang) image.radar_img = camera.getImage();           /////////
                    else std::cout << "Maybe Have Error!!!";
                    break;
                case single_picture:
                    image.radar_img = cv::imread(image.image_path);
                    break;
                case picture_dir:
                    image.radar_img = cv::imread(dynamic_image_path);
                    break;
                default:
                    std::cerr << "no picture" << std::endl;
                    break;
            }
        image.radar_cloneing = image.radar_img.clone();
        image.radar_draw     = image.radar_img.clone();
        image.map_cloneing   = image.map_img.clone();
        image.map_draw       = image.map_img.clone();
        //刷新图片img
        cv::imshow(image.camera_winname, image.radar_draw);
        cv::imshow(image.mapImage_winname,image.map_draw);
    // forward/backward picture
        if(ch == 'x'){after_picture++;}
        else if(ch == 'z'){after_picture--;}
    //save picture
        if(pose &&  image.Image_issave){
            future1 = std::async(std::launch::async,recordVedio1,outPath_half,iiiii,image.radar_cloneing);iiiii++;

//            interval_time = interval_time + last_time; iiiii++;
//            future2 = std::async(std::launch::async,recordVedio2,outPath_half,interval_time,iiiii,image.radar_cloneing);
        }
    //when pose is ok
        if(!image.radar_draw.empty()) {
            if (pose) {
                //"pose is ok"
                putText(image.radar_draw, "pose is ok", cv::Point2d(1, 40), 2, 1.5, cv::Scalar(0, 255, 250));
                //画出绘制所算出的2d场地
                draw_line(place, image.radar_draw);
                //神经网络 4
                NetWork(net,image.radar_cloneing,DetectionObjss);
                //get cars and armors
                Car_Armor(net,DetectionObjss,cars,armors);
                //get cars' Locate3D and cars' cls
                getLocate3D_cls(place,cars,armors);
                // draw result
                draw_rusult(cars,armors,image,modes.cls_to_string);

                if(modes.selfColor == "red" && port.Port_isopen) sendtoJudge(port,cars,place.redfly[4]);
                else if(modes.selfColor == "blue" && port.Port_isopen) sendtoJudge(port,cars,place.bluefly[4]);
            }

            if(ch =='r') {start_vedio = true;}
            //
            if((ch=='p' || (modes.pictureSource==PictureSource::picture_dir || modes.pictureSource==PictureSource::single_picture) ) && !pose){
                mouse.image = image.radar_draw;
                mouse.pointNumber = place.pts_pnp_3d.size();
                mouse.camera_winname = image.camera_winname;
                cv::setMouseCallback(image.camera_winname, onMouse, &mouse);
                cv::waitKey(0);
                pose=true;
                //场地信息载入，计算；准备好用于粗略计算的参数
                placePostConfig(mouse,place);
            }
            if(modes.pictureSource == PictureSource::single_picture){
                draw_line(place,image.radar_draw);
                putText(image.radar_draw, "pose is ok", cv::Point2d( 1,40 ), 2, 1.5, cv::Scalar(0, 255, 250));
                cv::imshow(image.camera_winname, image.radar_draw);
//            cv::waitKey(100);
            }

            if(ch=='q') {
            cv::destroyAllWindows();
                if(modes.pictureSource == PictureSource::camera_){
                    camera.close();
                }

                break;
            }

        }

        else{
            std::cout<<"Empty   "<<camera.getFPS()<<' '<<camera.mCount<<std::endl;         ////
            Camera::HikCamera camera;
            camera.close();////
            camera.open();                                                                 ////
            camera.setExposureTime(10000);                                    ////
            camera.setGain(12);                                                      ////
        }

        cars.clear();
        armors.clear();
        DetectionObjss.clear();


        auto end = std::chrono::high_resolution_clock::now();
        last_time = 1000 / (std::chrono::duration<double, std::milli>(end - begin).count()) ;
        std::cout << last_time << std::endl;
    }
    return 0;
}



//// 以时间为名字的文件夹
std::string makedir(Image &image){
    char now[64];
    std::time_t tt;
    struct tm *ttime;
    tt = time(nullptr);
    ttime = localtime(&tt);
    strftime(now, 64, "%Y-%m-%d_%H_%M_%S", ttime);
    std::string now_string(now);
    int flag = mkdir((image.Image_savepath+"/"+now).c_str(), S_IRWXU);
    std::cout << "mkdir is ok" << std::endl;
    return (image.Image_savepath + "/"+ now + "/");
}

void recordVedio1(string outPath_half,int pictureName,cv::Mat image){
    if(pictureName%10==0)
    cv::imwrite((outPath_half +std::to_string(pictureName/10)+ ".jpg"),image);
}

void recordVedio2(string outPath_half,double interval_time,int pictureName,cv::Mat image){
    if(interval_time > 0.5)
        cv::imwrite((outPath_half +std::to_string(pictureName)+ ".jpg"),image);
}