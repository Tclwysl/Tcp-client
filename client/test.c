#include <stdio.h>
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")

WORD sockVision = MAKEWORD(2,2);
WSADATA wsadata;
SOCKET sclient ;
struct sockaddr_in serAddr;
char senddata[1024];
char revdata[1024];
int n;
int ret = -1;

char analogdata_elevator(int n)
{
	char ELEVATOR_HEAD[1024] = "A55A";				/* 头部*/
	char *ELEVATOR_TAIL = "CC33C33C";			 /* 尾部*/
	char *ELEVATOR_COMMAND = "00";                     /* 自定义 */
	char *ELEVATOR_COMMAND_REGISTER = "01";		    /* 设备上报注册信息 */
	char *ELEVATOR_COMMAND_REGISTER_RESPONSE = "02";   /* 平台返回注册信息 */
    char *ELEVATOR_COMMAND_UPLOAD = "03";              /* 设备上报升降机信息 */
    char *ELEVATOR_COMMAND_CALIBRATE = "04";           /* 标定信息 */
    char *ELEVATOR_COMMAND_SPACING = "05";             /* 限位信息 */
    char *ELEVATOR_COMMAND_REALTIME = "10";            /* 实时工况数据 */
    char *ELEVATOR_COMMAND_WARNING = "11";             /* 报警信息 */
	char *ELEVATOR_COMMAND_AUTHENTICATE = "12";		 /* 人员身份认证信息 */
	
	//设备上报注册信息 0x01 A55A01110000011207CC33C33C
	if(n==1)
	{

		char *ELEVATOR_DATA_LENGTH = "12";					/*长度*/
		char *ELEVATOR_DATA_CHECKSUM = "07";					/*校验位*/
		char *cage = "11";/*吊笼(包含吊笼编号以及左右吊笼)*/
		char *serial_no = "000001";/*设备物理编号*/
		
		strcat(ELEVATOR_HEAD, ELEVATOR_COMMAND_REGISTER);//拼接类型
		strcat(ELEVATOR_HEAD, cage);
		strcat(ELEVATOR_HEAD, serial_no);

		strcat(ELEVATOR_HEAD, ELEVATOR_DATA_LENGTH);
		strcat(ELEVATOR_HEAD, ELEVATOR_DATA_CHECKSUM);
		strcat(ELEVATOR_HEAD, ELEVATOR_TAIL);
		
	}

	//平台返回注册信息帧  0x02  A55A02 11 000001 01 10 01 01 01 01 01 01 29 0F CC33C33C
	if(n==2)
	{
		char *ELEVATOR_DATA_LENGTH = "29";					/*长度*/
		char *ELEVATOR_DATA_CHECKSUM = "0F";					/*校验位*/
		char *cage = "11";/*吊笼(包含吊笼编号以及左右吊笼)*/
		char *serial_no = "000001";/*设备物理编号*/
		char *staTus="01";//注册结果
		char *timeInterval="100101010101";//上报数据间隔
		char *recordTIME="01";//数据解析时间


		strcat(ELEVATOR_HEAD, ELEVATOR_COMMAND_REGISTER_RESPONSE);
		strcat(ELEVATOR_HEAD, cage);
		strcat(ELEVATOR_HEAD, serial_no);
		strcat(ELEVATOR_HEAD,staTus);
		strcat(ELEVATOR_HEAD,timeInterval);
		strcat(ELEVATOR_HEAD,recordTIME);
		strcat(ELEVATOR_HEAD, ELEVATOR_DATA_LENGTH);
		strcat(ELEVATOR_HEAD, ELEVATOR_DATA_CHECKSUM);
		strcat(ELEVATOR_HEAD, ELEVATOR_TAIL);
	}
	
	//标定信息帧  0x04   A55A04 11 000001 11112222333344441111222233334444BA17CC33C33C
	if(n==4)
	{
		char *ELEVATOR_DATA_LENGTH = "BA";					/*长度*/
		char *ELEVATOR_DATA_CHECKSUM = "17";					/*校验位*/
		char *cage = "11";/*吊笼(包含吊笼编号以及左右吊笼)*/
		char *serial_no = "000001";/*设备物理编号*/
		char *weiemptyAd="1111";//重量空载AD值
		char *weiemptyActual="2222";//重量空载实际值
		char *weiloadAd="3333";//重量负载AD值
		char *weiloadActual="4444";//重量负载实际值
		char *heibotAd="1111";//高度底端AD值
		char *heibotActual="2222";//高度底端实际值
		char *heitopAd="3333";//高度顶端AD值
		char *heitopActual="4444";//高度顶端实际值

		
		strcat(ELEVATOR_HEAD, ELEVATOR_COMMAND_CALIBRATE);
		strcat(ELEVATOR_HEAD, cage);
		strcat(ELEVATOR_HEAD, serial_no);

		strcat(ELEVATOR_HEAD,weiemptyAd);
		strcat(ELEVATOR_HEAD,weiemptyActual);
		strcat(ELEVATOR_HEAD,weiloadAd);
		strcat(ELEVATOR_HEAD,weiloadActual);
		strcat(ELEVATOR_HEAD,heibotAd);
		strcat(ELEVATOR_HEAD,heibotActual);
		strcat(ELEVATOR_HEAD,heitopAd);
		strcat(ELEVATOR_HEAD,heitopActual);

		strcat(ELEVATOR_HEAD, ELEVATOR_DATA_LENGTH);
		strcat(ELEVATOR_HEAD, ELEVATOR_DATA_CHECKSUM);
		strcat(ELEVATOR_HEAD, ELEVATOR_TAIL);
	}
	
	//限位信息帧 0x05 A55A0511 000001 11112222333344445555666677778888DA17CC33C33C
	if(n==5)
	{
		char *ELEVATOR_DATA_LENGTH = "DA";					/*长度*/
		char *ELEVATOR_DATA_CHECKSUM = "17";					/*校验位*/
		char *cage = "11";/*吊笼(包含吊笼编号以及左右吊笼)*/
		char *serial_no = "000001";/*设备物理编号*/
		char *maxliftingWarning="1111";//最大起重预警
		char *maxliftingCtp="2222";//最大起重报警
		char *maxliftingHei="3333";//最大起升高度
		char *maxspeedWarning="4444";//最大速度预警
		char *maxspeedCtp="5555";//最大速度报警
		char *maxloadPeo="6666";//最大承载人数
		char *tiltWarning="7777";//倾斜预警值
		char *tiltCtp="8888";//倾斜报警值


		strcat(ELEVATOR_HEAD, ELEVATOR_COMMAND_SPACING);//拼接类型
		strcat(ELEVATOR_HEAD, cage);
		strcat(ELEVATOR_HEAD, serial_no);

		strcat(ELEVATOR_HEAD,maxliftingWarning);
		strcat(ELEVATOR_HEAD,maxliftingCtp);
		strcat(ELEVATOR_HEAD,maxliftingHei);
		strcat(ELEVATOR_HEAD,maxspeedWarning);
		strcat(ELEVATOR_HEAD,maxspeedCtp);
		strcat(ELEVATOR_HEAD,maxloadPeo);
		strcat(ELEVATOR_HEAD,tiltWarning);
		strcat(ELEVATOR_HEAD,tiltCtp);

		strcat(ELEVATOR_HEAD, ELEVATOR_DATA_LENGTH);
		strcat(ELEVATOR_HEAD, ELEVATOR_DATA_CHECKSUM);
		strcat(ELEVATOR_HEAD, ELEVATOR_TAIL);
	}
		
	
	//实时工况数据   0x10   A55A1011000001 200910010101 1010 20 17 1819 20 21 2223 24 11 11 1111 C41CCC33C33C
	if(n==10)
	{

		char *ELEVATOR_DATA_LENGTH = "C4";					/*长度*/
		char *ELEVATOR_DATA_CHECKSUM = "1C";					/*校验位*/
		char *cage = "11";/*吊笼(包含吊笼编号以及左右吊笼)*/
		char *serial_no = "000001";/*设备物理编号*/
		char *recordTIME="200910010101";//时间
		char *loAdd="1010";//本次运行载重
		char *loadPErcent="20";//本次运行最大载重百分比
		char *peoplenum="17";//实时人数
		char *startHEight="1819";//实时高度
		char *heightper="20";//高度百分比
		char *speeDddirecTion="21";//实时速度方向
		char *tilt="2223";//实时倾斜
		char *tiltper="24";//倾斜百分比
		char *deiver="11";//驾驶员认证结果
		char *lock="11";//门锁状态
		char *status="1111";//系统状态

		
		strcat(ELEVATOR_HEAD, ELEVATOR_COMMAND_REALTIME);//拼接类型
		strcat(ELEVATOR_HEAD, cage);
		strcat(ELEVATOR_HEAD, serial_no);

		strcat(ELEVATOR_HEAD, recordTIME);
		strcat(ELEVATOR_HEAD, loAdd);
		strcat(ELEVATOR_HEAD, loadPErcent);
		strcat(ELEVATOR_HEAD, peoplenum);
		strcat(ELEVATOR_HEAD, startHEight);
		strcat(ELEVATOR_HEAD, heightper);
		strcat(ELEVATOR_HEAD, speeDddirecTion);
		strcat(ELEVATOR_HEAD, tilt);
		strcat(ELEVATOR_HEAD, tiltper);
		strcat(ELEVATOR_HEAD, deiver);
		strcat(ELEVATOR_HEAD, lock);
		strcat(ELEVATOR_HEAD, status);


		strcat(ELEVATOR_HEAD, ELEVATOR_DATA_LENGTH);
		strcat(ELEVATOR_HEAD, ELEVATOR_DATA_CHECKSUM);
		strcat(ELEVATOR_HEAD, ELEVATOR_TAIL);
		
	}

	//报警信息    0x11  A55A 11 11 000001 050201050201 1111 22 33 4444 55 66 7777 88 99 11 22 33 511C CC33C33C
	if(n==11)
	{
		char *ELEVATOR_DATA_LENGTH = "51";					/*长度*/
		char *ELEVATOR_DATA_CHECKSUM = "1c";					/*校验位*/
		char *cage = "11";/*吊笼(包含吊笼编号以及左右吊笼)*/
		char *serial_no = "000001";/*设备物理编号*/
		char *recordTIME="050201050201";//时间
		char *realLifting="1111";//实时起重量
		char *weightPer="22";//重量百分比
		char *realPeoplenum="33";//实时人数
		char *realHeight="4444";//实时高度
		char *realHeightper="55";//高度百分比
		char *realSpeedtiltDirection="66";//实时速度方向
		char *realTilt="7777";//实时倾斜度
		char *tiltPer="88";//倾斜百分比
		char *driverStatus="99";//驾驶员身份认证结果
		char *lockstatus="11";//门锁状态
		char *alarmCause="22";//报警原因
		char *alarmLevel="33";//级别



		strcat(ELEVATOR_HEAD, ELEVATOR_COMMAND_WARNING);//拼接类型
		strcat(ELEVATOR_HEAD, cage);
		strcat(ELEVATOR_HEAD, serial_no);

		strcat(ELEVATOR_HEAD, recordTIME);
		strcat(ELEVATOR_HEAD, realLifting);
		strcat(ELEVATOR_HEAD, weightPer);
		strcat(ELEVATOR_HEAD, realPeoplenum);
		strcat(ELEVATOR_HEAD, realHeight);
		strcat(ELEVATOR_HEAD, realHeightper);
		strcat(ELEVATOR_HEAD, realSpeedtiltDirection);
		strcat(ELEVATOR_HEAD, realTilt);
		strcat(ELEVATOR_HEAD, tiltPer);
		strcat(ELEVATOR_HEAD, driverStatus);
		strcat(ELEVATOR_HEAD, lockstatus);
		strcat(ELEVATOR_HEAD, alarmCause);
		strcat(ELEVATOR_HEAD, alarmLevel);

		strcat(ELEVATOR_HEAD, ELEVATOR_DATA_LENGTH);
		strcat(ELEVATOR_HEAD, ELEVATOR_DATA_CHECKSUM);
		strcat(ELEVATOR_HEAD, ELEVATOR_TAIL);
	}


	//人员身份认证信息   0x12  A55A 12 11 000001 01 e4b880e4ba8ce4b889e59b9be4ba94e585ade4b883e585abe4b99de58d81 6162636465666768 99 333730383239313939393038333630323334 B341 CC33C33C
	//A55A121100000101e4b880e4ba8ce4b889e59b9be4ba94e585ade4b883e585abe4b99de58d81616263646566676899333730383239313939393038333630323334B341CC33C33C
	if(n==12)
	{
		char *ELEVATOR_DATA_LENGTH = "B3";					/*长度*/
		char *ELEVATOR_DATA_CHECKSUM = "41";					/*校验位*/
		char *cage = "11";/*吊笼(包含吊笼编号以及左右吊笼)*/
		char *serial_no = "000001";/*设备物理编号*/
		char *distStatus="01";//识别结果状态值
		char *driverName="e4b880e4ba8ce4b889e59b9be4ba94e585ade4b883e585abe4b99de58d81";//用户名
		char *userId="6162636465666768";//用户ID
		char *distNum="99";//识别分数
		char *driverId="333730383239313939393038333630323334";//身份证号码



		
		strcat(ELEVATOR_HEAD, ELEVATOR_COMMAND_AUTHENTICATE);//拼接类型
		strcat(ELEVATOR_HEAD, cage);
		strcat(ELEVATOR_HEAD, serial_no);

		strcat(ELEVATOR_HEAD, distStatus);
		strcat(ELEVATOR_HEAD, driverName);
		strcat(ELEVATOR_HEAD, userId);
		strcat(ELEVATOR_HEAD, distNum);
		strcat(ELEVATOR_HEAD, driverId);


		strcat(ELEVATOR_HEAD, ELEVATOR_DATA_LENGTH);
		strcat(ELEVATOR_HEAD, ELEVATOR_DATA_CHECKSUM);
		strcat(ELEVATOR_HEAD, ELEVATOR_TAIL);
	}






	send(sclient,ELEVATOR_HEAD,strlen(ELEVATOR_HEAD),0);
	ret = recv(sclient,revdata,1024,0);
	if(ret > 0)
	{
			
		revdata[ret] = 0x00;
		printf("\n");
		printf("发送内容：");
		printf("%s",ELEVATOR_HEAD);
		printf("\n");
		printf("服务器：");
		printf(revdata);
	}


}
char analogdata_TowerCrane(int n)
{
	//char ELEVATOR_HEAD[1024] = "A55A";				/* 头部*/
	char TOWERCRANE_HEAD[1024] = "A5AA";                      /* 头部 */
    char *TOWERCRANE_TAIL = "CCC3C33C";                  /* 尾部*/
    char *TOWERCRANE_COMMAND = "99";                     /* 自定义 */
    char *TOWERCRANE_COMMAND_REGISTER = "00";            /* 设备注册信息上传 */
    char *TOWERCRANE_COMMAND_REGISTER_DOWN = "01";       /* 后台注册信息下传 */
    char *TOWERCRANE_COMMAND_ATTRIBUTE = "02";           /* 设备属性信息上传 */
    char *TOWERCRANE_COMMAND_ANSWER_1 = "03";            /* 后台应答信息下传 */
    char *TOWERCRANE_COMMAND_HEARTBEAT = "04";           /* 设备心跳包上传 */
    char *TOWERCRANE_COMMAND_ANSWER_2 = "05";            /* 后台应答信息下传 */
    char *TOWERCRANE_COMMAND_REAL_DATA = "06";           /* 设备实时数据上传 */
    char *TOWERCRANE_COMMAND_ANSWER_3 = "07";            /* 后台应答信息下传 */
    char *TOWERCRANE_COMMAND_LOOP = "08";                /* 设备工作循环数据上传 */
    char *TOWERCRANE_COMMAND_ANSWER_4 = "09";            /* 后台应答信息下传 */

	//设备注册信息上传0x00
    //A5AA0922220011223344EECCC3C33C
	if(n==20)
	{

		char *TOWERCRANE_DATA_LENGTH = "09";  /* 长度 */
		char *TOWERCRANE_DATA_CHECKSUM = "EE"; /* 校验 */
		char *factoryNum="22";   //厂家编号
		char *proVersion="22";   // 协议版本
		char *deviceSerial="11223344";// 设备编号
		
		//帧头   帧长度   厂家编号    协议版本    帧类型   设备编号   （信息段） 校验和  帧尾
		strcat(TOWERCRANE_HEAD, TOWERCRANE_DATA_LENGTH);//帧长度
		strcat(TOWERCRANE_HEAD, factoryNum);//厂家编号
		strcat(TOWERCRANE_HEAD, proVersion);//协议版本
		strcat(TOWERCRANE_HEAD, TOWERCRANE_COMMAND_REGISTER);//帧类型
		strcat(TOWERCRANE_HEAD, deviceSerial);//设备编号
		
		//add信息段

		strcat(TOWERCRANE_HEAD, TOWERCRANE_DATA_CHECKSUM);//校验和
		strcat(TOWERCRANE_HEAD, TOWERCRANE_TAIL);//帧尾
		
		
	}

	//后台注册信息下传0x01
    //A5AA 10 22 22 01 11223344 200913010101 22 4FCCC3C33C
	if(n==21)
	{

		char *TOWERCRANE_DATA_LENGTH = "10";  /* 长度 */
		char *TOWERCRANE_DATA_CHECKSUM = "4F"; /* 校验 */
		char *factoryNum="22";   //厂家编号
		char *proVersion="22";   // 协议版本
		char *deviceSerial="11223344";// 设备编号
		char *ti_me="200913010101";//时间
		char *cycleUp="22";//上传周期
		
		//帧头   帧长度   厂家编号    协议版本    帧类型   设备编号   （信息段） 校验和  帧尾
		strcat(TOWERCRANE_HEAD, TOWERCRANE_DATA_LENGTH);//帧长度
		strcat(TOWERCRANE_HEAD, factoryNum);//厂家编号
		strcat(TOWERCRANE_HEAD, proVersion);//协议版本
		strcat(TOWERCRANE_HEAD, TOWERCRANE_COMMAND_REGISTER_DOWN);//帧类型
		strcat(TOWERCRANE_HEAD, deviceSerial);//设备编号
		
		strcat(TOWERCRANE_HEAD, ti_me);//时间
		strcat(TOWERCRANE_HEAD, cycleUp);//上传周期

		strcat(TOWERCRANE_HEAD, TOWERCRANE_DATA_CHECKSUM);//校验和
		strcat(TOWERCRANE_HEAD, TOWERCRANE_TAIL);//帧尾
		
	}

	//设备属性信息上传0x02
    //A5AA 5F 22 22 02 11223344 0102 33334444555566667777888899 111122223333444455556666777788889999 111122223333444455556666777788889999 111122223333444455556666777788889999 1111222233334444555566667777 010203 98 CCC3C33C
	if(n==22)
	{

		char *TOWERCRANE_DATA_LENGTH = "5F";  /* 长度 */
		char *TOWERCRANE_DATA_CHECKSUM = "98"; /* 校验 */
		char *factoryNum="22";   //厂家编号
		char *proVersion="22";   // 协议版本
		char *deviceSerial="11223344";// 设备编号

		char *towerNumber="01";//塔吊编号
		char *towerCurve="02";//力矩曲线
		char *towerX="3333";//坐标X
		char *towerY="4444";//坐标Y
		char *towerBoomlen="5555";//起重臂长
		char *towerBalancelen="6666";//平衡臂长
		char *towerCaphei="7777";//塔帽高
		char *towerBoomhei="8888";//起重臂高
		char *towerRope="99";//绳索倍率
		char *towerheiad1="1111";//高度标定
		char *towerHeix1="2222";//高度标定X1
		char *towerHeiad2="3333";//高度标定AD2
		char *towerHeix2="4444";//高度标定X2
		char *towerRangead1="5555";//幅度标定AD1
		char *towerRangex1="6666";//幅度标定X1
		char *towerRangead2="7777";//幅度标签AD2
		char *towerRangex2="8888";//幅度标定X2
		char *towerTurnad1="9999";//回转标定AD1
		char *towerTurnx1="1111";//回转标定X1
		char *towerTurnad2="2222";//回转标定AD2
		char *towerTurnx2="3333";//回转标定X2
		char *towerWeid1="4444";//重量标定AD1
		char *towerWeix1="5555";//重量标定X1
		char *towerWeid2="6666";//重量标定AD2
		char *towerWeix2="7777";//重量标定X2
		char *windCalibration="8888";//风速标定校准值
		char *tiltCalibration="9999";//倾斜标定校准值
		char *heightStart="1111";//高度起点限位
		char *heightEnd="2222";//高度终点限位
		char *rangeStart="3333";//幅度起点限位
		char *rangeEnd="4444";//幅度终点限位
		char *trunLf="5555";//回转左限位
		char *trunRi="6666";//回转右限位
		char *warningHor="7777";//水平报警距离
		char *warningVer="8888";//垂直报警距离
		char *warningHei="9999";//重量报警百分比
		char *warningWin="1111";//风速报警值
		char *warningTil="2222";//倾斜报警值
		char *earlywarningHor="3333";//水平预警距离
		char *earlywarningVer="4444";//垂直预警距离
		char *earlywarningHer="5555";//重量预警百分比
		char *earlywarningWin="6666";//风速预警值
		char *earlywarningTil="7777";//倾斜预警值
		char *collisionJudge="01";//碰撞制动允许
		char *idJudge="02";//身份认证是否启动
		char *gprsJudge="03";//GPRS锁车



		
		//帧头   帧长度   厂家编号    协议版本    帧类型   设备编号   （信息段） 校验和  帧尾
		strcat(TOWERCRANE_HEAD, TOWERCRANE_DATA_LENGTH);//帧长度
		strcat(TOWERCRANE_HEAD, factoryNum);//厂家编号
		strcat(TOWERCRANE_HEAD, proVersion);//协议版本
		strcat(TOWERCRANE_HEAD, TOWERCRANE_COMMAND_ATTRIBUTE);//帧类型
		strcat(TOWERCRANE_HEAD, deviceSerial);//设备编号
		
		strcat(TOWERCRANE_HEAD,towerNumber);
		strcat(TOWERCRANE_HEAD,towerCurve);
		strcat(TOWERCRANE_HEAD,towerX);
		strcat(TOWERCRANE_HEAD,towerY);
		strcat(TOWERCRANE_HEAD,towerBoomlen);
		strcat(TOWERCRANE_HEAD,towerBalancelen);
		strcat(TOWERCRANE_HEAD,towerCaphei);
		strcat(TOWERCRANE_HEAD,towerBoomhei);
		strcat(TOWERCRANE_HEAD,towerRope);
		strcat(TOWERCRANE_HEAD,towerheiad1);
		strcat(TOWERCRANE_HEAD,towerHeix1);
		strcat(TOWERCRANE_HEAD,towerHeiad2);
		strcat(TOWERCRANE_HEAD,towerHeix2);
		strcat(TOWERCRANE_HEAD,towerRangead1);
		strcat(TOWERCRANE_HEAD,towerRangex1);
		strcat(TOWERCRANE_HEAD,towerRangead2);
		strcat(TOWERCRANE_HEAD,towerRangex2);
		strcat(TOWERCRANE_HEAD,towerTurnad1);
		strcat(TOWERCRANE_HEAD,towerTurnx1);
		strcat(TOWERCRANE_HEAD,towerTurnad2);
		strcat(TOWERCRANE_HEAD,towerTurnx2);
		strcat(TOWERCRANE_HEAD,towerWeid1);
		strcat(TOWERCRANE_HEAD,towerWeix1);
		strcat(TOWERCRANE_HEAD,towerWeid2);
		strcat(TOWERCRANE_HEAD,towerWeix2);
		strcat(TOWERCRANE_HEAD,windCalibration);
		strcat(TOWERCRANE_HEAD,tiltCalibration);
		strcat(TOWERCRANE_HEAD,heightStart);
		strcat(TOWERCRANE_HEAD,heightEnd);
		strcat(TOWERCRANE_HEAD,rangeStart);
		strcat(TOWERCRANE_HEAD,rangeEnd);
		strcat(TOWERCRANE_HEAD,trunLf);
		strcat(TOWERCRANE_HEAD,trunRi);
		strcat(TOWERCRANE_HEAD,warningHor);
		strcat(TOWERCRANE_HEAD,warningVer);
		strcat(TOWERCRANE_HEAD,warningHei);
		strcat(TOWERCRANE_HEAD,warningWin);
		strcat(TOWERCRANE_HEAD,warningTil);
		strcat(TOWERCRANE_HEAD,earlywarningHor);
		strcat(TOWERCRANE_HEAD,earlywarningVer);
		strcat(TOWERCRANE_HEAD,earlywarningHer);
		strcat(TOWERCRANE_HEAD,earlywarningWin);
		strcat(TOWERCRANE_HEAD,earlywarningTil);
		strcat(TOWERCRANE_HEAD,collisionJudge);
		strcat(TOWERCRANE_HEAD,idJudge);
		strcat(TOWERCRANE_HEAD,gprsJudge);

		strcat(TOWERCRANE_HEAD, TOWERCRANE_DATA_CHECKSUM);//校验和
		strcat(TOWERCRANE_HEAD, TOWERCRANE_TAIL);//帧尾
		
	}

	//设备实时数据上传0x06
	//A5AA 2B 22220611223344 200913052013 11112222333344445555667777888899 112233445566778899110122 8E CCC3C33C
	if(n==26)
	{

		char *TOWERCRANE_DATA_LENGTH = "2B";  /* 长度 */
		char *TOWERCRANE_DATA_CHECKSUM = "8E"; /* 校验 */
		char *factoryNum="22";   //厂家编号
		char *proVersion="22";   // 协议版本
		char *deviceSerial="11223344";// 设备编号
		char *ti_me="200913052013";//时间
		char *Height="1111";//高度
		char *Range="2222";//幅度
		char *Turn="3333";//回转
		char *Load="4444";//载重
		char *loadJudge="5555";//当前允许载重
		char *loadPer="66";//载重百分比
		char *Wind="7777";//风速
		char *Tilt="8888";//倾斜
		char *heightSpa="99";//高度限位值
		char *rangeSpa="11";//幅度回转限位
		char *loadSpa="22";//载重限制值
		char *tiltwindSpa="33";//倾斜风速限制值
		char *interferenceSx="44";//干涉上下限位
		char *interferenceQh="55";//干涉前后限位
		char *interferenceZy="66";//干涉左右限位
		char *collisionSx="77";//碰撞上下限位
		char *collisionQh="88";//碰撞前后限位
		char *collisionZy="99";//碰撞左右限位
		char *relayState="11";//继电器状态
		char *workState="01";//工作状态
		char *sensorState="22";//传感器连接状态



		
		//帧头   帧长度   厂家编号    协议版本    帧类型   设备编号   （信息段） 校验和  帧尾
		strcat(TOWERCRANE_HEAD, TOWERCRANE_DATA_LENGTH);//帧长度
		strcat(TOWERCRANE_HEAD, factoryNum);//厂家编号
		strcat(TOWERCRANE_HEAD, proVersion);//协议版本
		strcat(TOWERCRANE_HEAD, TOWERCRANE_COMMAND_REAL_DATA);//帧类型
		strcat(TOWERCRANE_HEAD, deviceSerial);//设备编号
		
		strcat(TOWERCRANE_HEAD, ti_me);
		strcat(TOWERCRANE_HEAD, Height);
		strcat(TOWERCRANE_HEAD, Range);
		strcat(TOWERCRANE_HEAD, Turn);
		strcat(TOWERCRANE_HEAD, Load);
		strcat(TOWERCRANE_HEAD, loadJudge);
		strcat(TOWERCRANE_HEAD, loadPer);
		strcat(TOWERCRANE_HEAD, Wind);
		strcat(TOWERCRANE_HEAD, Tilt);
		strcat(TOWERCRANE_HEAD, heightSpa);
		strcat(TOWERCRANE_HEAD, rangeSpa);
		strcat(TOWERCRANE_HEAD, loadSpa);
		strcat(TOWERCRANE_HEAD, tiltwindSpa);
		strcat(TOWERCRANE_HEAD, interferenceSx);
		strcat(TOWERCRANE_HEAD, interferenceQh);
		strcat(TOWERCRANE_HEAD, interferenceZy);
		strcat(TOWERCRANE_HEAD, collisionSx);
		strcat(TOWERCRANE_HEAD, collisionQh);
		strcat(TOWERCRANE_HEAD, collisionZy);
		strcat(TOWERCRANE_HEAD, relayState);
		strcat(TOWERCRANE_HEAD, workState);
		strcat(TOWERCRANE_HEAD, sensorState);

		strcat(TOWERCRANE_HEAD, TOWERCRANE_DATA_CHECKSUM);//校验和
		strcat(TOWERCRANE_HEAD, TOWERCRANE_TAIL);//帧尾
		
		
	}

	//工作循环数据上传0x08
	//A5AA 2B 22220811223344 180706050201 180706050201 222233334444 180706050201222233334444 11113301 2F CCC3C33C
	if(n==28)
	{

		char *TOWERCRANE_DATA_LENGTH = "2B";  /* 长度 */
		char *TOWERCRANE_DATA_CHECKSUM = "2F"; /* 校验 */
		char *factoryNum="22";   //厂家编号
		char *proVersion="22";   // 协议版本
		char *deviceSerial="11223344";// 设备编号

		char *upload_time="180706050201";//上传时间
		char *liftingTime="180706050201";//起吊时间
		char *liftingHei="2222";//起吊点高度
		char *liftingRange="3333";//起吊点幅度
		char *liftingTurn="4444";//起吊点回转
		char *liftingTime2="180706050201";//起吊时间2
		char *liftingHei2="2222";//起吊点高度2
		char *liftingRange2="3333";//起吊点幅度2
		char *liftingTurn2="4444";//起吊点回转2
		char *liftingWei="1111";//最大吊重
		char *liftingLoad="33";//最大负荷
		char *violationReg="01";//是否违章



		
		//帧头   帧长度   厂家编号    协议版本    帧类型   设备编号   （信息段） 校验和  帧尾
		strcat(TOWERCRANE_HEAD, TOWERCRANE_DATA_LENGTH);//帧长度
		strcat(TOWERCRANE_HEAD, factoryNum);//厂家编号
		strcat(TOWERCRANE_HEAD, proVersion);//协议版本
		strcat(TOWERCRANE_HEAD, TOWERCRANE_COMMAND_LOOP);//帧类型
		strcat(TOWERCRANE_HEAD, deviceSerial);//设备编号
		strcat(TOWERCRANE_HEAD, upload_time);
		strcat(TOWERCRANE_HEAD, liftingTime);
		strcat(TOWERCRANE_HEAD, liftingHei);
		strcat(TOWERCRANE_HEAD, liftingRange);
		strcat(TOWERCRANE_HEAD, liftingTurn);
		strcat(TOWERCRANE_HEAD, liftingTime2);
		strcat(TOWERCRANE_HEAD, liftingHei2);
		strcat(TOWERCRANE_HEAD, liftingRange2);
		strcat(TOWERCRANE_HEAD, liftingTurn2);
		strcat(TOWERCRANE_HEAD, liftingWei);
		strcat(TOWERCRANE_HEAD, liftingLoad);
		strcat(TOWERCRANE_HEAD, violationReg);
		strcat(TOWERCRANE_HEAD, TOWERCRANE_DATA_CHECKSUM);//校验和
		strcat(TOWERCRANE_HEAD, TOWERCRANE_TAIL);//帧尾
		
		
	}


	send(sclient,TOWERCRANE_HEAD,strlen(TOWERCRANE_HEAD),0);
	ret = recv(sclient,revdata,1024,0);
	if(ret > 0)
	{
			
		revdata[ret] = 0x00;
		printf("\n");
		printf("发送内容：");
		printf("%s",TOWERCRANE_HEAD);
		printf("\n");
		printf("服务器：");
		printf(revdata);
		printf("\n");
	}

}
char analogdata_dust(int n)
{
	char DUST_HEAD[1024] = "#,";				/* 头部*/
	char *DUST_TAIL = "#";			 /* 尾部*/
	char *DUST_SEPARATE = ",";//每一条参数以逗号分隔

	//扬尘平台数据
	//#,11.1,22.2,33.3,44.4,55.5,66.6,77.7,88.8#
	if(n==30)
	{
		char *temperature="11.1";//温度
		char *humidity="22.2";//湿度
		char *wind_speed="33.3";//风速
		char *wind_direction="44.4";//风向
		char *atmosphere="55.5";//大气压力
		char *pm2_5="66.6";//PM2.5
		char *pm_10="77.7";//PM10
		char *noise="88.8";//噪声


		strcat(DUST_HEAD, temperature);
		strcat(DUST_HEAD, DUST_SEPARATE);
		strcat(DUST_HEAD, humidity);
		strcat(DUST_HEAD, DUST_SEPARATE);
		strcat(DUST_HEAD, wind_speed);
		strcat(DUST_HEAD, DUST_SEPARATE);
		strcat(DUST_HEAD, wind_direction);
		strcat(DUST_HEAD, DUST_SEPARATE);
		strcat(DUST_HEAD, atmosphere);
		strcat(DUST_HEAD, DUST_SEPARATE);
		strcat(DUST_HEAD, pm2_5);
		strcat(DUST_HEAD, DUST_SEPARATE);
		strcat(DUST_HEAD, pm_10);
		strcat(DUST_HEAD, DUST_SEPARATE);
		strcat(DUST_HEAD, noise);
		strcat(DUST_HEAD, DUST_TAIL);//拼接尾部

	}

	send(sclient,DUST_HEAD,strlen(DUST_HEAD),0);
	ret = recv(sclient,revdata,1024,0);
	if(ret > 0)
	{
			
		revdata[ret] = 0x00;
		printf("\n");
		printf("发送内容：");
		printf("%s",DUST_HEAD);
		printf("\n");
		printf("服务器：");
		printf(revdata);
		printf("\n");
	}
}


int main(void)
{
	if(WSAStartup(sockVision,&wsadata) != 0)
	{
		printf("WSA初始化失败\n");
		return 0;
	}

	sclient = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(sclient == INVALID_SOCKET)
	{
		printf("socket客户端创建失败\n");
		return 0;
	}
	
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(2222);
	serAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");


	


	if( connect(sclient,(SOCKADDR *)&serAddr,sizeof(serAddr)) == SOCKET_ERROR )
	{
		printf("socket客户端连接失败\n");
		return 0;
	}

	printf("socket客户端连接成功！\n");
	printf("对方IP：%s\n",inet_ntoa(serAddr.sin_addr));
	printf("监听端口：%d\n",ntohs(serAddr.sin_port));
	printf("根据编号发送模拟数据：\n");
	printf("\n1、设备上报注册信息");
	printf("\n2、平台返回注册信息帧");
	printf("\n4、标定信息帧");
	printf("\n5、限位信息帧");
	printf("\n10、实时工况数据");
	printf("\n11、报警信息");
	printf("\n12、人员身份认证信息");
	printf("\n");
	printf("\n20、设备注册信息上传");
	printf("\n21、后台注册信息下传");
	printf("\n22、设备属性信息上传");
	printf("\n26、设备实时数据上传");
	printf("\n28、工作循环数据上传");
	printf("\n");
	printf("\n30、扬尘平台数据");
	printf("\n");

	while (1)
	{
		printf("\n输入编号发送数据：");
		scanf("%d",&n);
		if(n==1 || n==2 || n==4 || n==5 || n==10 || n==11 || n==12)
		{
			if(n==10)
			{
				analogdata_elevator(n);
			}
			else
			{
				analogdata_elevator(n);
				printf("\n非实时数据，客户端关闭！\n");
				break;
			}
		}
		else if(n==28 || n==26 || n==22 || n==21 || n==20)
		{
			if(n==26)
			{
				analogdata_TowerCrane(n);
			}
			else
			{
				analogdata_TowerCrane(n);
				printf("\n非实时数据，客户端关闭！\n");
				break;
			}
					
		}
		else if(n==30)
		{
			analogdata_dust(n);
			printf("\n非实时数据，客户端关闭！\n");
			break;
		}
		else
		{
			printf("\n无此编号信息呗\n");
		}
	
	}
		
	closesocket(sclient);
	WSACleanup();

	system("pause");
	return 0;
}





