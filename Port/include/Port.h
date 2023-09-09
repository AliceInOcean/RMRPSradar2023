//
// Created by plusseven on 23-7-15.
//

#ifndef RADAR2023_WITHTRT_PORT_H
#define RADAR2023_WITHTRT_PORT_H

#include  "../../general/general.h"

#include <vector>
//#include <stdio.h>      /*标准输入输出*/
//#include <stdlib.h>     /*标准函数库*/
#include <unistd.h>     /*Unix标准函数*/
#include <sys/types.h>  /*数据类型定义，比如一些XXX_t的类型*/
#include <sys/stat.h>   /*返回值结构*/
#include <fcntl.h>      /*文件控制*/
#include <termios.h>    /*PPSIX终端控制*/
//#include <errno.h>      /*错误号*/
#include <string>
#include <iostream>
#include "serialport.h"
#include "CRC_Check.h"

class Port {
public:
    bool Port_isopen;
    const char *port_path;
    SerialPort serial;

    std::string selfColor;

    uint16_t_uchar sender_ID;
    uint16_t_uchar receiver_ID;



    Port() = default;
    Port(Modes &modes){
        this->Port_isopen = modes.Port_isopen;
        this->port_path = modes.port_path;
        this->selfColor = modes.selfColor;

    //初始化串口
        if(this->selfColor == "red"){
            sender_ID = {9};
            receiver_ID = {6};
        }
        else if(this->selfColor == "blue"){
            sender_ID = {109};
            receiver_ID = {106};
        }

        if(this->Port_isopen){
            serial.baud = 115200;
            serial.fd = open(this->port_path, O_RDWR|O_NOCTTY| O_NDELAY);

            serial.initSerialPort();
            std::cout << "port is open" << std::endl;
        }
        else std::cout << "port is close" << std::endl;

    }


};



void sendtoJudge(Port &port,std::vector<Car> cars,int &fly);

//typedef __pack struct
typedef struct
{
    uint16_t target_robot_ID;
    float target_position_x;
    float target_position_y;
} ext_client_map_command_t;



#endif //RADAR2023_WITHTRT_PORT_H
