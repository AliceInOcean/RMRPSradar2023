#include "../include/serialport.h"


/**
 *@brief   初始化数据
 *@param  fd       类型  int  打开的串口文件句柄
 *@param  speed    类型  int  波特率

 *@param  databits 类型  int  数据位   取值 为 7 或者8

 *@param  stopbits 类型  int  停止位   取值为 1 或者2
 *@param  parity   类型  int  效验类型 取值为N,E,O,S
 *@param  portchar 类型  char* 串口路径
 */
bool SerialPort::initSerialPort()
{

    speed = baud;//=115200
    databits = 8;
    stopbits = 1;
	parity = 'N';

    set_Brate();

	if (set_Bit() == FALSE)
	{
        printf("Set Parity Error\n");
		exit(0);
    }
    printf("Open successed\n");
    set_Bit();

    return true;
}

bool SerialPort::withoutSerialPort()
{
    return true;
}

/**
 *@brief   设置波特率
 */
void SerialPort::set_Brate()
{
    // int speed_arr[] = {B115200, B38400, B19200, B9600, B4800, B2400, B1200, B300,
	// 				   B115200, B38400, B19200, B9600, B4800, B2400, B1200, B300,
	// 				  };
    // int name_arr[] = {115200, 38400, 19200, 9600, 4800, 2400, 1200,  300,
	// 				  115200, 38400, 19200, 9600, 4800, 2400, 1200,  300,
	// 				 };
    int speed_arr[] = {B921600, B460800, B230400, B115200, B38400, B19200, B9600, B4800, B2400, B1200, B300};
    int name_arr[] = {921600, 460800, 230400,115200, 38400, 19200, 9600, 4800, 2400, 1200,  300};
    int   i;
    int   status;
    struct termios   Opt;
    tcgetattr(fd, &Opt);

	for (i = 0;  i < sizeof(speed_arr) / sizeof(int);  i++)
	{
		if (speed == name_arr[i])
		{
			tcflush(fd, TCIOFLUSH);//清空缓冲区的内容
			cfsetispeed(&Opt, speed_arr[i]);//设置接受和发送的波特率
			cfsetospeed(&Opt, speed_arr[i]);
            status = tcsetattr(fd, TCSANOW, &Opt); //使设置立即生效

			if (status != 0)
			{
                perror("tcsetattr fd1");
                return;
            }

			tcflush(fd, TCIOFLUSH);

        }
    }
}

/**
 *@brief   设置串口数据位，停止位和效验位
 */
int SerialPort::set_Bit()
{
    struct termios termios_p;

	if (tcgetattr(fd, &termios_p)  !=  0)
	{
        perror("SetupSerial 1");
		return (FALSE);
    }

    termios_p.c_cflag |= (CLOCAL | CREAD);  //接受数据
	termios_p.c_cflag &= ~CSIZE;//设置数据位数

    switch (databits)
    {
	case 7:
		termios_p.c_cflag |= CS7;
		break;

	case 8:
		termios_p.c_cflag |= CS8;
		break;

	default:
		fprintf(stderr, "Unsupported data size\n");
		return (FALSE);
    }

	//设置奇偶校验位double
    switch (parity)
    {
	case 'n':
	case 'N':
		termios_p.c_cflag &= ~PARENB;   /* Clear parity enable */
		termios_p.c_iflag &= ~INPCK;     /* Enable parity checking */
		break;

	case 'o':
	case 'O':
		termios_p.c_cflag |= (PARODD | PARENB); /* 设置为奇效验*/
		termios_p.c_iflag |= INPCK;             /* Disnable parity checking */
		break;

	case 'e':
	case 'E':
		termios_p.c_cflag |= PARENB;     /* Enable parity */
		termios_p.c_cflag &= ~PARODD;   /* 转换为偶效验*/
		termios_p.c_iflag |= INPCK;       /* Disnable parity checking */
		break;

	case 'S':
	case 's':  /*as no parity*/
		termios_p.c_cflag &= ~PARENB;
		termios_p.c_cflag &= ~CSTOPB;
		break;

	default:
		fprintf(stderr, "Unsupported parity\n");
		return (FALSE);

    }

    /* 设置停止位*/
    switch (stopbits)
    {
	case 1:
		termios_p.c_cflag &= ~CSTOPB;
		break;

	case 2:
		termios_p.c_cflag |= CSTOPB;
		break;

	default:
		fprintf(stderr, "Unsupported stop bits\n");
		return (FALSE);

    }

    /* Set input parity option */
    if (parity != 'n')
        termios_p.c_iflag |= INPCK;

	tcflush(fd, TCIFLUSH); //清除输入缓存区
    termios_p.c_cc[VTIME] = 150; /* 设置超时15 seconds*/
    termios_p.c_cc[VMIN] = 0;  //最小接收字符
    termios_p.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);  /*Input原始输入*/
	termios_p.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
    termios_p.c_iflag &= ~(ICRNL | IGNCR);
    termios_p.c_oflag &= ~OPOST;   /*Output禁用输出处理*/

	if (tcsetattr(fd, TCSANOW, &termios_p) != 0) /* Update the options and do it NOW */
    {
        perror("SetupSerial 3");
        return (FALSE);
    }

    return (TRUE);
}


/**
 *@brief   雷达站向裁判系统发数（main）
 */
void SerialPort::Radar_TransformData(const BeforeData &beforeData,const Ext_client_map_command_t &extClientMapCommand)
{
    //包头（frame_header）
    Tmap_data[0] = 0xA5;                             //数据帧起始字节，固定值为 0xA5
    Tmap_data[1] = beforeData.data_length.c[0];      //数据帧的长度
    Tmap_data[2] = beforeData.data_length.c[1];
    Tmap_data[3] = 0;                                //seq(包序号)
    Append_CRC8_Check_Sum(Tmap_data, 5);  //帧头 CRC8 校验
    bool t1 = Verify_CRC8_Check_Sum(Tmap_data,5);
    //std::cout << t1 << std::endl;

    //命令码cmd_id
    Tmap_data[5] = beforeData.cmd_id.c[0];
    Tmap_data[6] = beforeData.cmd_id.c[1];

    //数据帧
    //Ext_client_map_command_t extClientMapCommand = {target_robot_ID,x,y};
    Tmap_data[7] = extClientMapCommand.target_robot_ID.c[0];        //目标机器人的ID
    Tmap_data[8] = extClientMapCommand.target_robot_ID.c[1];

    Tmap_data[9] = extClientMapCommand.target_position_x.c[0];      //世界坐标系下的x
    Tmap_data[10] = extClientMapCommand.target_position_x.c[1];
    Tmap_data[11] = extClientMapCommand.target_position_x.c[2];
    Tmap_data[12] = extClientMapCommand.target_position_x.c[3];

    Tmap_data[13] = extClientMapCommand.target_position_y.c[0];      //世界坐标系下的y
    Tmap_data[14] = extClientMapCommand.target_position_y.c[1];
    Tmap_data[15] = extClientMapCommand.target_position_y.c[2];
    Tmap_data[16] = extClientMapCommand.target_position_y.c[3];
    //Tmap_data[17] = 0x00;
    //frame_tail (2-byte，CRC16，整包校验)
    Append_CRC16_Check_Sum(Tmap_data, 19);

    bool t2 = Verify_CRC16_Check_Sum(Tmap_data,19);
    //std::cout << "t2.." << t2 << std::endl;

}

/**
 *@brief   飞坡预警（TODO：未经过赛场测试，其效果有待商讨）
 */
void SerialPort::fly_warning(const BeforeData &beforeData,const graphic_data_struct_t &graphicDataStruct)
{
    fly_warning_data[0] = 0xA5;                             //数据帧起始字节，固定值为 0xA5
    fly_warning_data[1] = beforeData.data_length.c[0];      //数据帧的长度
    fly_warning_data[2] = beforeData.data_length.c[1];
    fly_warning_data[3] = 0;                                //seq(包序号)
    Append_CRC8_Check_Sum(fly_warning_data, 5);  //帧头 CRC8 校验？
    bool t1 = Verify_CRC8_Check_Sum(fly_warning_data,5);
    std::cout << t1 << std::endl;

    //命令码cmd_id
    fly_warning_data[5] = beforeData.cmd_id.c[0];
    fly_warning_data[6] = beforeData.cmd_id.c[1];

    //数据帧
    //unsigned char name[3] = {'f','l','y'};
    //graphic_data_struct_t graphicDataStruct;
    //= {0x0101, 9, 0x0101, name[0],name[1],name[2],1,1,1,6,0,0,9,900,500,0,100,600};
    *(graphic_data_struct_t*)(&fly_warning_data[7]) = graphicDataStruct;
    //Tmap_data[17] = 0x00;
    //frame_tail (2-byte，CRC16，整包校验)
    Append_CRC16_Check_Sum(fly_warning_data, 26);

    bool t2 = Verify_CRC16_Check_Sum(fly_warning_data,26);
    //std::cout << "t2..." << t2 << std::endl;
}

void SerialPort::sendToOther(const BeforeData &beforeData, const ext_student_interactive_header_data_t &extStudentInteractiveHeaderData) {
    //包头（frame_header）
    //BeforeData beforeData={10,0x0305};
    sendData[0] = 0xA5;                             //数据帧起始字节，固定值为 0xA5
    sendData[1] = beforeData.data_length.c[0];      //数据帧的长度
    sendData[2] = beforeData.data_length.c[1];
    sendData[3] = 0;                                //seq(包序号)
    Append_CRC8_Check_Sum(sendData, 5);  //帧头 CRC8 校验？
    bool t1 = Verify_CRC8_Check_Sum(sendData,5);
    //std::cout << "sendto" << t1 << std::endl;

    //命令码cmd_id
    sendData[5] = beforeData.cmd_id.c[0];
    sendData[6] = beforeData.cmd_id.c[1];
/////-------------------------------------------------------------------------------
    sendData[7] = extStudentInteractiveHeaderData.data_cmd_id.c[0];
    sendData[8] = extStudentInteractiveHeaderData.data_cmd_id.c[1];

    sendData[9] = extStudentInteractiveHeaderData.sender_ID.c[0];
    sendData[10] = extStudentInteractiveHeaderData.sender_ID.c[1];

    sendData[11] = extStudentInteractiveHeaderData.receiver_ID.c[0];
    sendData[12] = extStudentInteractiveHeaderData.receiver_ID.c[1];

    //经测试，只有当自定义数据长度大于一个数（不太记得了，好像是18+），才能成功的发送，故使用了多个flyyyyy
    sendData[13] = extStudentInteractiveHeaderData.flyyyy;
    sendData[14] = extStudentInteractiveHeaderData.flyyyy;
    sendData[15] = extStudentInteractiveHeaderData.flyyyy;
    sendData[16] = extStudentInteractiveHeaderData.flyyyy;

    sendData[17] = extStudentInteractiveHeaderData.flyyyy;
    sendData[18] = extStudentInteractiveHeaderData.flyyyy;
    sendData[19] = extStudentInteractiveHeaderData.flyyyy;
    sendData[20] = extStudentInteractiveHeaderData.flyyyy;

    sendData[21] = extStudentInteractiveHeaderData.flyyyy;
    sendData[22] = extStudentInteractiveHeaderData.flyyyy;
    sendData[23] = extStudentInteractiveHeaderData.flyyyy;

//    *(ext_student_interactive_header_data_t *)(&sendData[7]) = extStudentInteractiveHeaderData;
//    *(graphic_data_struct_t*)(&fly_warning_data[7]) = graphicDataStruct;
    Append_CRC16_Check_Sum(sendData, 26);

}


//发送敌人车辆坐标
void SerialPort::send_U()
{
	auto write_stauts = write(fd, Tmap_data, sizeof(Tmap_data));
//    std::cout << "port:" << write_stauts << "Tmap_data" << sizeof(Tmap_data) << endl;
}

void SerialPort::send_Y(){
//    BeforeData beforeData={21,0x0301};
    BeforeData beforeData={17,0x0301};
    unsigned char name[3] = {0,'l','y'};
//    graphic_data_struct_t graphicDataStruct = {0x0101, 109, 0x016A, name[0],name[1],name[2],1,1,1,6,0,0,9,900,500,0,1100,700};
//    graphic_data_struct_t graphicDataStruct = {0x02FF,109,106 , name[0],name[1],name[2],1,1,1,6,0,0,9,900,500,0,1100,700};
    graphic_data_struct_t graphicDataStruct = {0x02FF,9,0x0106,name[0],name[1],name[2],1,1,1,6,0,0,9,900,500};
    fly_warning(beforeData,graphicDataStruct);
//    *(graphic_data_struct_t*)(&ddata) = graphicDataStruct;
    auto write_stauts = write(fd, fly_warning_data, sizeof(fly_warning_data));
//    std::cout << write_stauts << endl;
}

//发送飞坡预警
void SerialPort::send_Z(){
//    BeforeData beforeData={7,0x0301};
//    unsigned char name[3] = {1,'l','y'};
//    sendData[0] = 0xA5;                             //数据帧起始字节，固定值为 0xA5
//    sendData[1] = beforeData.data_length.c[0];      //数据帧的长度
//    sendData[2] = beforeData.data_length.c[1];
//    sendData[3] = 0;                                //seq(包序号)
//    Append_CRC8_Check_Sum(sendData, 5);  //帧头 CRC8 校验？
//    bool t1 = Verify_CRC8_Check_Sum(sendData,5);
//    std::cout << t1 << std::endl;
//
//    //命令码cmd_id
//    sendData[5] = beforeData.cmd_id.c[0];
//    sendData[6] = beforeData.cmd_id.c[1];
//
//    //数据帧
////    unsigned char name[3] = {'f','l','y'};
//    ext_student_interactive_header_data_t extStudentInteractiveHeaderData = {0x02FF,109,106,0};
//    *(ext_student_interactive_header_data_t*)(&sendData[7]) = extStudentInteractiveHeaderData;
////    Tmap_data[17] = 0x00;
//    //frame_tail (2-byte，CRC16，整包校验)
//    Append_CRC16_Check_Sum(sendData, 16);
//
//    bool t2 = Verify_CRC16_Check_Sum(sendData,16);
//    std::cout << t2 << std::endl;
//
//    ////----------------------------------------------------------------------
////    BeforeData beforeData={7,0x0301};
////    ext_student_interactive_header_data_t extStudentInteractiveHeaderData = {0x02FF,109,106 };//blue
//    sendToOther(beforeData,extStudentInteractiveHeaderData);
////    *(graphic_data_struct_t*)(&ddata) = graphicDataStruct;


    auto write_stauts = write(fd, sendData, sizeof(sendData));


//    std::cout << "port=" << write_stauts << endl;
}

//关闭通讯协议接口
void SerialPort::closePort()
{
    close(fd);
}




//    extStudentInteractiveHeaderData = { 0x0101,  9(r)/109(b), 0x0165/0x0166,'fly'};
//    fly_warning_data[0] = extStudentInteractiveHeaderData.data_cmd_id.c[0];
//    fly_warning_data[1] = extStudentInteractiveHeaderData.data_cmd_id.c[1];
//    fly_warning_data[2] = extStudentInteractiveHeaderData.sender_ID.c[0];
//    fly_warning_data[3] = extStudentInteractiveHeaderData.sender_ID.c[1];
//    fly_warning_data[4] = extStudentInteractiveHeaderData.receiver_ID.c[0];
//    fly_warning_data[5] = extStudentInteractiveHeaderData.receiver_ID.c[1];
//
//    fly_warning_data[6] = graphicDataStruct.graphic_name1;
//    fly_warning_data[7] = graphicDataStruct.graphic_name2;
//    fly_warning_data[8] = graphicDataStruct.graphic_name3;
//
//    uint32_t data1 = {0};
//    uint32_t data2 = {0};
//    uint32_t data3 = {0};

// 数据
//（图形名）

//    graphicDataStruct.graphic_tpye <<= 3;
//    graphicDataStruct.layer <<= 3+3;
//    graphicDataStruct.color <<= 4+3+3;
//    graphicDataStruct.start_angle <<= 9+4+3+3;
//    graphicDataStruct.end_angle <<= 9+9+4+3+3;
//
//    data1 = (graphicDataStruct.end_angle|graphicDataStruct.start_angle|graphicDataStruct.color|graphicDataStruct.layer|graphicDataStruct.graphic_tpye|graphicDataStruct.operate_tpye);
//
//    graphicDataStruct.start_x <<= 10;
//    graphicDataStruct.start_y <<= 10+11;
//    data2 = (graphicDataStruct.start_y|graphicDataStruct.start_x|graphicDataStruct.width);
//
//    graphicDataStruct.end_x <<= 10;
//    graphicDataStruct.end_y <<= 10+11;
//    data3 = (graphicDataStruct.end_y|graphicDataStruct.end_x|graphicDataStruct.radius);
//
//    uint32_t4uchar d1 = {data1};
//    uint32_t4uchar d2 = {data2};
//    uint32_t4uchar d3 = {data3};
//
////    graphicDataStruct = { 1(增加),1（矩形）,1（图层数）,3(颜色)， };
//    // {1,1,1,3,0,0,9,50,50,0,100,100};
//
//
//    fly_warning_data[9]  = d1.c[0];
//    fly_warning_data[10] = d1.c[1];
//    fly_warning_data[11] = d1.c[2];
//    fly_warning_data[12] = d1.c[3];
//
//    fly_warning_data[13] = d2.c[0];
//    fly_warning_data[14] = d2.c[1];
//    fly_warning_data[15] = d2.c[2];
//    fly_warning_data[16] = d2.c[3];
//
//    fly_warning_data[17] = d3.c[0];
//    fly_warning_data[18] = d3.c[1];
//    fly_warning_data[19] = d3.c[2];
//    fly_warning_data[20] = d3.c[3];
//
//    graphicDataStruct.operate_tpye <<=  9+9+4+4+3;
//    graphicDataStruct.graphic_tpye <<= 9+9+4+4;
//    graphicDataStruct.layer <<= 9+9+4;
//    graphicDataStruct.color <<= 9+9;
//    graphicDataStruct.start_angle <<= 9;
////    graphicDataStruct.end_angle <<= 9+9+4+3+3;
//
//    data1 = (graphicDataStruct.operate_tpye|graphicDataStruct.graphic_tpye|graphicDataStruct.layer|graphicDataStruct.color|graphicDataStruct.start_angle|graphicDataStruct.end_angle);
//
//    graphicDataStruct.width <<= 11+11;
//    graphicDataStruct.start_x <<= 11;
////    graphicDataStruct.start_y <<= 10+11;
//    data2 = (graphicDataStruct.width|graphicDataStruct.start_x|graphicDataStruct.start_y);
//
//    graphicDataStruct.radius <<= 11+11;
//    graphicDataStruct.end_x <<= 11;
////    graphicDataStruct.end_y <<= 11;
//    data3 = (graphicDataStruct.radius|graphicDataStruct.end_x|graphicDataStruct.end_y);
//
//    uint32_t4uchar d1 = {data1};
//    uint32_t4uchar d2 = {data2};
//    uint32_t4uchar d3 = {data3};

//    graphicDataStruct = { 1(增加),1（矩形）,1（图层数）,3(颜色)， };
// {1,1,1,3,0,0,9,50,50,0,100,100};
//
//
//    fly_warning_data[9]  = d1.c[3];
//    fly_warning_data[10] = d1.c[2];
//    fly_warning_data[11] = d1.c[1];
//    fly_warning_data[12] = d1.c[0];
//
//    fly_warning_data[13] = d2.c[3];
//    fly_warning_data[14] = d2.c[2];
//    fly_warning_data[15] = d2.c[1];
//    fly_warning_data[16] = d2.c[0];
//
//    fly_warning_data[17] = d3.c[3];
//    fly_warning_data[18] = d3.c[2];
//    fly_warning_data[19] = d3.c[1];
//    fly_warning_data[20] = d3.c[0];

//数据帧   //    graphicDataStruct = { 0（图形名）,1(增加),1（矩形）,1（图层数）,3(颜色)， };



