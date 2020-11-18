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
	char ELEVATOR_HEAD[1024] = "A55A";				/* ͷ��*/
	char *ELEVATOR_TAIL = "CC33C33C";			 /* β��*/
	char *ELEVATOR_COMMAND = "00";                     /* �Զ��� */
	char *ELEVATOR_COMMAND_REGISTER = "01";		    /* �豸�ϱ�ע����Ϣ */
	char *ELEVATOR_COMMAND_REGISTER_RESPONSE = "02";   /* ƽ̨����ע����Ϣ */
    char *ELEVATOR_COMMAND_UPLOAD = "03";              /* �豸�ϱ���������Ϣ */
    char *ELEVATOR_COMMAND_CALIBRATE = "04";           /* �궨��Ϣ */
    char *ELEVATOR_COMMAND_SPACING = "05";             /* ��λ��Ϣ */
    char *ELEVATOR_COMMAND_REALTIME = "10";            /* ʵʱ�������� */
    char *ELEVATOR_COMMAND_WARNING = "11";             /* ������Ϣ */
	char *ELEVATOR_COMMAND_AUTHENTICATE = "12";		 /* ��Ա�����֤��Ϣ */
	
	//�豸�ϱ�ע����Ϣ 0x01 A55A01110000011207CC33C33C
	if(n==1)
	{

		char *ELEVATOR_DATA_LENGTH = "12";					/*����*/
		char *ELEVATOR_DATA_CHECKSUM = "07";					/*У��λ*/
		char *cage = "11";/*����(������������Լ����ҵ���)*/
		char *serial_no = "000001";/*�豸������*/
		
		strcat(ELEVATOR_HEAD, ELEVATOR_COMMAND_REGISTER);//ƴ������
		strcat(ELEVATOR_HEAD, cage);
		strcat(ELEVATOR_HEAD, serial_no);

		strcat(ELEVATOR_HEAD, ELEVATOR_DATA_LENGTH);
		strcat(ELEVATOR_HEAD, ELEVATOR_DATA_CHECKSUM);
		strcat(ELEVATOR_HEAD, ELEVATOR_TAIL);
		
	}

	//ƽ̨����ע����Ϣ֡  0x02  A55A02 11 000001 01 10 01 01 01 01 01 01 29 0F CC33C33C
	if(n==2)
	{
		char *ELEVATOR_DATA_LENGTH = "29";					/*����*/
		char *ELEVATOR_DATA_CHECKSUM = "0F";					/*У��λ*/
		char *cage = "11";/*����(������������Լ����ҵ���)*/
		char *serial_no = "000001";/*�豸������*/
		char *staTus="01";//ע����
		char *timeInterval="100101010101";//�ϱ����ݼ��
		char *recordTIME="01";//���ݽ���ʱ��


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
	
	//�궨��Ϣ֡  0x04   A55A04 11 000001 11112222333344441111222233334444BA17CC33C33C
	if(n==4)
	{
		char *ELEVATOR_DATA_LENGTH = "BA";					/*����*/
		char *ELEVATOR_DATA_CHECKSUM = "17";					/*У��λ*/
		char *cage = "11";/*����(������������Լ����ҵ���)*/
		char *serial_no = "000001";/*�豸������*/
		char *weiemptyAd="1111";//��������ADֵ
		char *weiemptyActual="2222";//��������ʵ��ֵ
		char *weiloadAd="3333";//��������ADֵ
		char *weiloadActual="4444";//��������ʵ��ֵ
		char *heibotAd="1111";//�߶ȵ׶�ADֵ
		char *heibotActual="2222";//�߶ȵ׶�ʵ��ֵ
		char *heitopAd="3333";//�߶ȶ���ADֵ
		char *heitopActual="4444";//�߶ȶ���ʵ��ֵ

		
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
	
	//��λ��Ϣ֡ 0x05 A55A0511 000001 11112222333344445555666677778888DA17CC33C33C
	if(n==5)
	{
		char *ELEVATOR_DATA_LENGTH = "DA";					/*����*/
		char *ELEVATOR_DATA_CHECKSUM = "17";					/*У��λ*/
		char *cage = "11";/*����(������������Լ����ҵ���)*/
		char *serial_no = "000001";/*�豸������*/
		char *maxliftingWarning="1111";//�������Ԥ��
		char *maxliftingCtp="2222";//������ر���
		char *maxliftingHei="3333";//��������߶�
		char *maxspeedWarning="4444";//����ٶ�Ԥ��
		char *maxspeedCtp="5555";//����ٶȱ���
		char *maxloadPeo="6666";//����������
		char *tiltWarning="7777";//��бԤ��ֵ
		char *tiltCtp="8888";//��б����ֵ


		strcat(ELEVATOR_HEAD, ELEVATOR_COMMAND_SPACING);//ƴ������
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
		
	
	//ʵʱ��������   0x10   A55A1011000001 200910010101 1010 20 17 1819 20 21 2223 24 11 11 1111 C41CCC33C33C
	if(n==10)
	{

		char *ELEVATOR_DATA_LENGTH = "C4";					/*����*/
		char *ELEVATOR_DATA_CHECKSUM = "1C";					/*У��λ*/
		char *cage = "11";/*����(������������Լ����ҵ���)*/
		char *serial_no = "000001";/*�豸������*/
		char *recordTIME="200910010101";//ʱ��
		char *loAdd="1010";//������������
		char *loadPErcent="20";//��������������ذٷֱ�
		char *peoplenum="17";//ʵʱ����
		char *startHEight="1819";//ʵʱ�߶�
		char *heightper="20";//�߶Ȱٷֱ�
		char *speeDddirecTion="21";//ʵʱ�ٶȷ���
		char *tilt="2223";//ʵʱ��б
		char *tiltper="24";//��б�ٷֱ�
		char *deiver="11";//��ʻԱ��֤���
		char *lock="11";//����״̬
		char *status="1111";//ϵͳ״̬

		
		strcat(ELEVATOR_HEAD, ELEVATOR_COMMAND_REALTIME);//ƴ������
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

	//������Ϣ    0x11  A55A 11 11 000001 050201050201 1111 22 33 4444 55 66 7777 88 99 11 22 33 511C CC33C33C
	if(n==11)
	{
		char *ELEVATOR_DATA_LENGTH = "51";					/*����*/
		char *ELEVATOR_DATA_CHECKSUM = "1c";					/*У��λ*/
		char *cage = "11";/*����(������������Լ����ҵ���)*/
		char *serial_no = "000001";/*�豸������*/
		char *recordTIME="050201050201";//ʱ��
		char *realLifting="1111";//ʵʱ������
		char *weightPer="22";//�����ٷֱ�
		char *realPeoplenum="33";//ʵʱ����
		char *realHeight="4444";//ʵʱ�߶�
		char *realHeightper="55";//�߶Ȱٷֱ�
		char *realSpeedtiltDirection="66";//ʵʱ�ٶȷ���
		char *realTilt="7777";//ʵʱ��б��
		char *tiltPer="88";//��б�ٷֱ�
		char *driverStatus="99";//��ʻԱ�����֤���
		char *lockstatus="11";//����״̬
		char *alarmCause="22";//����ԭ��
		char *alarmLevel="33";//����



		strcat(ELEVATOR_HEAD, ELEVATOR_COMMAND_WARNING);//ƴ������
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


	//��Ա�����֤��Ϣ   0x12  A55A 12 11 000001 01 e4b880e4ba8ce4b889e59b9be4ba94e585ade4b883e585abe4b99de58d81 6162636465666768 99 333730383239313939393038333630323334 B341 CC33C33C
	//A55A121100000101e4b880e4ba8ce4b889e59b9be4ba94e585ade4b883e585abe4b99de58d81616263646566676899333730383239313939393038333630323334B341CC33C33C
	if(n==12)
	{
		char *ELEVATOR_DATA_LENGTH = "B3";					/*����*/
		char *ELEVATOR_DATA_CHECKSUM = "41";					/*У��λ*/
		char *cage = "11";/*����(������������Լ����ҵ���)*/
		char *serial_no = "000001";/*�豸������*/
		char *distStatus="01";//ʶ����״ֵ̬
		char *driverName="e4b880e4ba8ce4b889e59b9be4ba94e585ade4b883e585abe4b99de58d81";//�û���
		char *userId="6162636465666768";//�û�ID
		char *distNum="99";//ʶ�����
		char *driverId="333730383239313939393038333630323334";//���֤����



		
		strcat(ELEVATOR_HEAD, ELEVATOR_COMMAND_AUTHENTICATE);//ƴ������
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
		printf("�������ݣ�");
		printf("%s",ELEVATOR_HEAD);
		printf("\n");
		printf("��������");
		printf(revdata);
	}


}
char analogdata_TowerCrane(int n)
{
	//char ELEVATOR_HEAD[1024] = "A55A";				/* ͷ��*/
	char TOWERCRANE_HEAD[1024] = "A5AA";                      /* ͷ�� */
    char *TOWERCRANE_TAIL = "CCC3C33C";                  /* β��*/
    char *TOWERCRANE_COMMAND = "99";                     /* �Զ��� */
    char *TOWERCRANE_COMMAND_REGISTER = "00";            /* �豸ע����Ϣ�ϴ� */
    char *TOWERCRANE_COMMAND_REGISTER_DOWN = "01";       /* ��̨ע����Ϣ�´� */
    char *TOWERCRANE_COMMAND_ATTRIBUTE = "02";           /* �豸������Ϣ�ϴ� */
    char *TOWERCRANE_COMMAND_ANSWER_1 = "03";            /* ��̨Ӧ����Ϣ�´� */
    char *TOWERCRANE_COMMAND_HEARTBEAT = "04";           /* �豸�������ϴ� */
    char *TOWERCRANE_COMMAND_ANSWER_2 = "05";            /* ��̨Ӧ����Ϣ�´� */
    char *TOWERCRANE_COMMAND_REAL_DATA = "06";           /* �豸ʵʱ�����ϴ� */
    char *TOWERCRANE_COMMAND_ANSWER_3 = "07";            /* ��̨Ӧ����Ϣ�´� */
    char *TOWERCRANE_COMMAND_LOOP = "08";                /* �豸����ѭ�������ϴ� */
    char *TOWERCRANE_COMMAND_ANSWER_4 = "09";            /* ��̨Ӧ����Ϣ�´� */

	//�豸ע����Ϣ�ϴ�0x00
    //A5AA0922220011223344EECCC3C33C
	if(n==20)
	{

		char *TOWERCRANE_DATA_LENGTH = "09";  /* ���� */
		char *TOWERCRANE_DATA_CHECKSUM = "EE"; /* У�� */
		char *factoryNum="22";   //���ұ��
		char *proVersion="22";   // Э��汾
		char *deviceSerial="11223344";// �豸���
		
		//֡ͷ   ֡����   ���ұ��    Э��汾    ֡����   �豸���   ����Ϣ�Σ� У���  ֡β
		strcat(TOWERCRANE_HEAD, TOWERCRANE_DATA_LENGTH);//֡����
		strcat(TOWERCRANE_HEAD, factoryNum);//���ұ��
		strcat(TOWERCRANE_HEAD, proVersion);//Э��汾
		strcat(TOWERCRANE_HEAD, TOWERCRANE_COMMAND_REGISTER);//֡����
		strcat(TOWERCRANE_HEAD, deviceSerial);//�豸���
		
		//add��Ϣ��

		strcat(TOWERCRANE_HEAD, TOWERCRANE_DATA_CHECKSUM);//У���
		strcat(TOWERCRANE_HEAD, TOWERCRANE_TAIL);//֡β
		
		
	}

	//��̨ע����Ϣ�´�0x01
    //A5AA 10 22 22 01 11223344 200913010101 22 4FCCC3C33C
	if(n==21)
	{

		char *TOWERCRANE_DATA_LENGTH = "10";  /* ���� */
		char *TOWERCRANE_DATA_CHECKSUM = "4F"; /* У�� */
		char *factoryNum="22";   //���ұ��
		char *proVersion="22";   // Э��汾
		char *deviceSerial="11223344";// �豸���
		char *ti_me="200913010101";//ʱ��
		char *cycleUp="22";//�ϴ�����
		
		//֡ͷ   ֡����   ���ұ��    Э��汾    ֡����   �豸���   ����Ϣ�Σ� У���  ֡β
		strcat(TOWERCRANE_HEAD, TOWERCRANE_DATA_LENGTH);//֡����
		strcat(TOWERCRANE_HEAD, factoryNum);//���ұ��
		strcat(TOWERCRANE_HEAD, proVersion);//Э��汾
		strcat(TOWERCRANE_HEAD, TOWERCRANE_COMMAND_REGISTER_DOWN);//֡����
		strcat(TOWERCRANE_HEAD, deviceSerial);//�豸���
		
		strcat(TOWERCRANE_HEAD, ti_me);//ʱ��
		strcat(TOWERCRANE_HEAD, cycleUp);//�ϴ�����

		strcat(TOWERCRANE_HEAD, TOWERCRANE_DATA_CHECKSUM);//У���
		strcat(TOWERCRANE_HEAD, TOWERCRANE_TAIL);//֡β
		
	}

	//�豸������Ϣ�ϴ�0x02
    //A5AA 5F 22 22 02 11223344 0102 33334444555566667777888899 111122223333444455556666777788889999 111122223333444455556666777788889999 111122223333444455556666777788889999 1111222233334444555566667777 010203 98 CCC3C33C
	if(n==22)
	{

		char *TOWERCRANE_DATA_LENGTH = "5F";  /* ���� */
		char *TOWERCRANE_DATA_CHECKSUM = "98"; /* У�� */
		char *factoryNum="22";   //���ұ��
		char *proVersion="22";   // Э��汾
		char *deviceSerial="11223344";// �豸���

		char *towerNumber="01";//�������
		char *towerCurve="02";//��������
		char *towerX="3333";//����X
		char *towerY="4444";//����Y
		char *towerBoomlen="5555";//���ر۳�
		char *towerBalancelen="6666";//ƽ��۳�
		char *towerCaphei="7777";//��ñ��
		char *towerBoomhei="8888";//���ر۸�
		char *towerRope="99";//��������
		char *towerheiad1="1111";//�߶ȱ궨
		char *towerHeix1="2222";//�߶ȱ궨X1
		char *towerHeiad2="3333";//�߶ȱ궨AD2
		char *towerHeix2="4444";//�߶ȱ궨X2
		char *towerRangead1="5555";//���ȱ궨AD1
		char *towerRangex1="6666";//���ȱ궨X1
		char *towerRangead2="7777";//���ȱ�ǩAD2
		char *towerRangex2="8888";//���ȱ궨X2
		char *towerTurnad1="9999";//��ת�궨AD1
		char *towerTurnx1="1111";//��ת�궨X1
		char *towerTurnad2="2222";//��ת�궨AD2
		char *towerTurnx2="3333";//��ת�궨X2
		char *towerWeid1="4444";//�����궨AD1
		char *towerWeix1="5555";//�����궨X1
		char *towerWeid2="6666";//�����궨AD2
		char *towerWeix2="7777";//�����궨X2
		char *windCalibration="8888";//���ٱ궨У׼ֵ
		char *tiltCalibration="9999";//��б�궨У׼ֵ
		char *heightStart="1111";//�߶������λ
		char *heightEnd="2222";//�߶��յ���λ
		char *rangeStart="3333";//���������λ
		char *rangeEnd="4444";//�����յ���λ
		char *trunLf="5555";//��ת����λ
		char *trunRi="6666";//��ת����λ
		char *warningHor="7777";//ˮƽ��������
		char *warningVer="8888";//��ֱ��������
		char *warningHei="9999";//���������ٷֱ�
		char *warningWin="1111";//���ٱ���ֵ
		char *warningTil="2222";//��б����ֵ
		char *earlywarningHor="3333";//ˮƽԤ������
		char *earlywarningVer="4444";//��ֱԤ������
		char *earlywarningHer="5555";//����Ԥ���ٷֱ�
		char *earlywarningWin="6666";//����Ԥ��ֵ
		char *earlywarningTil="7777";//��бԤ��ֵ
		char *collisionJudge="01";//��ײ�ƶ�����
		char *idJudge="02";//�����֤�Ƿ�����
		char *gprsJudge="03";//GPRS����



		
		//֡ͷ   ֡����   ���ұ��    Э��汾    ֡����   �豸���   ����Ϣ�Σ� У���  ֡β
		strcat(TOWERCRANE_HEAD, TOWERCRANE_DATA_LENGTH);//֡����
		strcat(TOWERCRANE_HEAD, factoryNum);//���ұ��
		strcat(TOWERCRANE_HEAD, proVersion);//Э��汾
		strcat(TOWERCRANE_HEAD, TOWERCRANE_COMMAND_ATTRIBUTE);//֡����
		strcat(TOWERCRANE_HEAD, deviceSerial);//�豸���
		
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

		strcat(TOWERCRANE_HEAD, TOWERCRANE_DATA_CHECKSUM);//У���
		strcat(TOWERCRANE_HEAD, TOWERCRANE_TAIL);//֡β
		
	}

	//�豸ʵʱ�����ϴ�0x06
	//A5AA 2B 22220611223344 200913052013 11112222333344445555667777888899 112233445566778899110122 8E CCC3C33C
	if(n==26)
	{

		char *TOWERCRANE_DATA_LENGTH = "2B";  /* ���� */
		char *TOWERCRANE_DATA_CHECKSUM = "8E"; /* У�� */
		char *factoryNum="22";   //���ұ��
		char *proVersion="22";   // Э��汾
		char *deviceSerial="11223344";// �豸���
		char *ti_me="200913052013";//ʱ��
		char *Height="1111";//�߶�
		char *Range="2222";//����
		char *Turn="3333";//��ת
		char *Load="4444";//����
		char *loadJudge="5555";//��ǰ��������
		char *loadPer="66";//���ذٷֱ�
		char *Wind="7777";//����
		char *Tilt="8888";//��б
		char *heightSpa="99";//�߶���λֵ
		char *rangeSpa="11";//���Ȼ�ת��λ
		char *loadSpa="22";//��������ֵ
		char *tiltwindSpa="33";//��б��������ֵ
		char *interferenceSx="44";//����������λ
		char *interferenceQh="55";//����ǰ����λ
		char *interferenceZy="66";//����������λ
		char *collisionSx="77";//��ײ������λ
		char *collisionQh="88";//��ײǰ����λ
		char *collisionZy="99";//��ײ������λ
		char *relayState="11";//�̵���״̬
		char *workState="01";//����״̬
		char *sensorState="22";//����������״̬



		
		//֡ͷ   ֡����   ���ұ��    Э��汾    ֡����   �豸���   ����Ϣ�Σ� У���  ֡β
		strcat(TOWERCRANE_HEAD, TOWERCRANE_DATA_LENGTH);//֡����
		strcat(TOWERCRANE_HEAD, factoryNum);//���ұ��
		strcat(TOWERCRANE_HEAD, proVersion);//Э��汾
		strcat(TOWERCRANE_HEAD, TOWERCRANE_COMMAND_REAL_DATA);//֡����
		strcat(TOWERCRANE_HEAD, deviceSerial);//�豸���
		
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

		strcat(TOWERCRANE_HEAD, TOWERCRANE_DATA_CHECKSUM);//У���
		strcat(TOWERCRANE_HEAD, TOWERCRANE_TAIL);//֡β
		
		
	}

	//����ѭ�������ϴ�0x08
	//A5AA 2B 22220811223344 180706050201 180706050201 222233334444 180706050201222233334444 11113301 2F CCC3C33C
	if(n==28)
	{

		char *TOWERCRANE_DATA_LENGTH = "2B";  /* ���� */
		char *TOWERCRANE_DATA_CHECKSUM = "2F"; /* У�� */
		char *factoryNum="22";   //���ұ��
		char *proVersion="22";   // Э��汾
		char *deviceSerial="11223344";// �豸���

		char *upload_time="180706050201";//�ϴ�ʱ��
		char *liftingTime="180706050201";//���ʱ��
		char *liftingHei="2222";//�����߶�
		char *liftingRange="3333";//��������
		char *liftingTurn="4444";//������ת
		char *liftingTime2="180706050201";//���ʱ��2
		char *liftingHei2="2222";//�����߶�2
		char *liftingRange2="3333";//��������2
		char *liftingTurn2="4444";//������ת2
		char *liftingWei="1111";//������
		char *liftingLoad="33";//��󸺺�
		char *violationReg="01";//�Ƿ�Υ��



		
		//֡ͷ   ֡����   ���ұ��    Э��汾    ֡����   �豸���   ����Ϣ�Σ� У���  ֡β
		strcat(TOWERCRANE_HEAD, TOWERCRANE_DATA_LENGTH);//֡����
		strcat(TOWERCRANE_HEAD, factoryNum);//���ұ��
		strcat(TOWERCRANE_HEAD, proVersion);//Э��汾
		strcat(TOWERCRANE_HEAD, TOWERCRANE_COMMAND_LOOP);//֡����
		strcat(TOWERCRANE_HEAD, deviceSerial);//�豸���
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
		strcat(TOWERCRANE_HEAD, TOWERCRANE_DATA_CHECKSUM);//У���
		strcat(TOWERCRANE_HEAD, TOWERCRANE_TAIL);//֡β
		
		
	}


	send(sclient,TOWERCRANE_HEAD,strlen(TOWERCRANE_HEAD),0);
	ret = recv(sclient,revdata,1024,0);
	if(ret > 0)
	{
			
		revdata[ret] = 0x00;
		printf("\n");
		printf("�������ݣ�");
		printf("%s",TOWERCRANE_HEAD);
		printf("\n");
		printf("��������");
		printf(revdata);
		printf("\n");
	}

}
char analogdata_dust(int n)
{
	char DUST_HEAD[1024] = "#,";				/* ͷ��*/
	char *DUST_TAIL = "#";			 /* β��*/
	char *DUST_SEPARATE = ",";//ÿһ�������Զ��ŷָ�

	//�ﳾƽ̨����
	//#,11.1,22.2,33.3,44.4,55.5,66.6,77.7,88.8#
	if(n==30)
	{
		char *temperature="11.1";//�¶�
		char *humidity="22.2";//ʪ��
		char *wind_speed="33.3";//����
		char *wind_direction="44.4";//����
		char *atmosphere="55.5";//����ѹ��
		char *pm2_5="66.6";//PM2.5
		char *pm_10="77.7";//PM10
		char *noise="88.8";//����


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
		strcat(DUST_HEAD, DUST_TAIL);//ƴ��β��

	}

	send(sclient,DUST_HEAD,strlen(DUST_HEAD),0);
	ret = recv(sclient,revdata,1024,0);
	if(ret > 0)
	{
			
		revdata[ret] = 0x00;
		printf("\n");
		printf("�������ݣ�");
		printf("%s",DUST_HEAD);
		printf("\n");
		printf("��������");
		printf(revdata);
		printf("\n");
	}
}


int main(void)
{
	if(WSAStartup(sockVision,&wsadata) != 0)
	{
		printf("WSA��ʼ��ʧ��\n");
		return 0;
	}

	sclient = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
	if(sclient == INVALID_SOCKET)
	{
		printf("socket�ͻ��˴���ʧ��\n");
		return 0;
	}
	
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(2222);
	serAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");


	


	if( connect(sclient,(SOCKADDR *)&serAddr,sizeof(serAddr)) == SOCKET_ERROR )
	{
		printf("socket�ͻ�������ʧ��\n");
		return 0;
	}

	printf("socket�ͻ������ӳɹ���\n");
	printf("�Է�IP��%s\n",inet_ntoa(serAddr.sin_addr));
	printf("�����˿ڣ�%d\n",ntohs(serAddr.sin_port));
	printf("���ݱ�ŷ���ģ�����ݣ�\n");
	printf("\n1���豸�ϱ�ע����Ϣ");
	printf("\n2��ƽ̨����ע����Ϣ֡");
	printf("\n4���궨��Ϣ֡");
	printf("\n5����λ��Ϣ֡");
	printf("\n10��ʵʱ��������");
	printf("\n11��������Ϣ");
	printf("\n12����Ա�����֤��Ϣ");
	printf("\n");
	printf("\n20���豸ע����Ϣ�ϴ�");
	printf("\n21����̨ע����Ϣ�´�");
	printf("\n22���豸������Ϣ�ϴ�");
	printf("\n26���豸ʵʱ�����ϴ�");
	printf("\n28������ѭ�������ϴ�");
	printf("\n");
	printf("\n30���ﳾƽ̨����");
	printf("\n");

	while (1)
	{
		printf("\n�����ŷ������ݣ�");
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
				printf("\n��ʵʱ���ݣ��ͻ��˹رգ�\n");
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
				printf("\n��ʵʱ���ݣ��ͻ��˹رգ�\n");
				break;
			}
					
		}
		else if(n==30)
		{
			analogdata_dust(n);
			printf("\n��ʵʱ���ݣ��ͻ��˹رգ�\n");
			break;
		}
		else
		{
			printf("\n�޴˱����Ϣ��\n");
		}
	
	}
		
	closesocket(sclient);
	WSACleanup();

	system("pause");
	return 0;
}





