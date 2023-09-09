//
// Created by plusseven on 23-7-15.
//

#include "../include/Port.h"


//struct termio
//{
//    tcflag_t c_iflag;    /*输入模式标志，unsigned short*/
//    tcflag_t c_oflag;    /*输出模式标志，unsigned short*/
//    tcflag_t c_cflag;    /*控制模式标志，unsigned short*/
//    tcflag_t c_lflag;    /*本地模式标志，unsigned short*/
//    cc_t  c_line;        /*线路规程，unsigned char*/
//    cc_t  c_cc[NCCS];    /*控制字符，unsigned char*/
//    speed_t c_ispeed;    /*输入波特率，unsigned int*/
//    speed_t c_ospeed;    /*输出波特率，unsigned int*/
//};



void sendtoJudge(Port &port,std::vector<Car> cars,int &fly){
    BeforeData beforeData_map = {10,0x0305};
    BeforeData beforeData={17,0x0301};
    uint16_t carNumber;

    //to judge
    for(Car car:cars){
        if(car.cls < 6 && port.selfColor == "blue"){
            carNumber = car.cls;
            if( carNumber == 0 ) carNumber = 7;
            Ext_client_map_command_t extClientMapCommand = {carNumber,{float (car.Locate3D.x)},{float (car.Locate3D.y)}};
            port.serial.Radar_TransformData(beforeData_map,extClientMapCommand);
            port.serial.send_U();
//            std::cout << "port_send:" <<  carNumber << std::endl;
            
        }
        else if( 6 <= car.cls && car.cls < 12 && port.selfColor == "red"){
            carNumber = car.cls - 6 + 100;
            if( carNumber == 100 ) carNumber = 107;
            Ext_client_map_command_t extClientMapCommand = {carNumber,{float (car.Locate3D.x)},{float (car.Locate3D.y)}};
            port.serial.Radar_TransformData(beforeData_map,extClientMapCommand);
            port.serial.send_U();
            std::cout << "port_send:" <<  carNumber << std::endl;
        }
        else{
//        std::cout << "port has error!!" <<std::endl;
        }
    }
    //to plane
        if( port.selfColor == "blue"  ){
            if( fly == 1 ){
                ext_student_interactive_header_data_t extStudentInteractiveHeaderData = {0x02FF,port.sender_ID,port.receiver_ID,1};
                port.serial.sendToOther(beforeData, extStudentInteractiveHeaderData);
            } else{
                ext_student_interactive_header_data_t extStudentInteractiveHeaderData = {0x02FF,port.sender_ID,port.receiver_ID,0};
                port.serial.sendToOther(beforeData, extStudentInteractiveHeaderData);
            }
        }

        else if( port.selfColor == "red"  ){
            if( fly == 1 ){
                ext_student_interactive_header_data_t extStudentInteractiveHeaderData = {0x02FF,port.sender_ID,106,1};
                port.serial.sendToOther(beforeData, extStudentInteractiveHeaderData);
            } else{
                ext_student_interactive_header_data_t extStudentInteractiveHeaderData = {0x02FF,port.sender_ID,106,0};
                port.serial.sendToOther(beforeData, extStudentInteractiveHeaderData);
            }
        }
        port.serial.send_Z();
        fly = 0;

}

