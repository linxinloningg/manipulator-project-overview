	/**
	* @last update Nov 30 2021 
	* @sdkversion 2.1.2.3_dev
	* @Maintenance star@jaka
	*/
#ifndef _JHTYPES_H_
#define _JHTYPES_H_

#define TRUE 1
#define FALSE 0
#include <stdio.h>

typedef int BOOL;	 //��������
typedef int JKHD;	 //��е�ۿ��ƾ������
typedef int errno_t; //�ӿڷ���ֵ����

/**
* @brief �ѿ����ռ�λ����������
*/
typedef struct
{
	double x; ///< x�����꣬��λmm
	double y; ///< y�����꣬��λmm
	double z; ///< z�����꣬��λmm
} CartesianTran;

/**
* @brief ŷ������̬��������
*/
typedef struct
{
	double rx; ///< �ƹ̶���X��ת�Ƕȣ���λ��rad
	double ry; ///< �ƹ̶���Y��ת�Ƕȣ���λ��rad
	double rz; ///< �ƹ̶���Z��ת�Ƕȣ���λ��rad
} Rpy;

/**
* @brief ��Ԫ����̬��������
*/
typedef struct
{
	double s;
	double x;
	double y;
	double z;
} Quaternion;

/**
 *@brief �ѿ����ռ�λ������
 */
typedef struct
{
	CartesianTran tran; ///< �ѿ����ռ�λ��
	Rpy rpy;			///< �ѿ����ռ���̬
} CartesianPose;

/**
* @brief ��ת������������
*/
typedef struct
{
	CartesianTran x; ///< x���з���
	CartesianTran y; ///< y���з���
	CartesianTran z; ///< z���з���
} RotMatrix;

/**
* @brief ��������״̬ö������
*/
typedef enum
{
	PROGRAM_IDLE,	 ///< ������ֹͣ����
	PROGRAM_RUNNING, ///< ��������������
	PROGRAM_PAUSED	 ///< ��������ͣ
} ProgramState;

/**
* @brief ����ϵѡ��ö������
*/
typedef enum
{
	COORD_BASE,	 ///< ������ϵ
	COORD_JOINT, ///< �ؽڿռ�
	COORD_TOOL	 ///< ��������ϵ
} CoordType;

/**
* @brief jog�˶�ģʽö�� 
*/
typedef enum
{
	ABS = 0, ///< �����˶�
	INCR,	 ///< �����˶�
	CONTINUE ///< �����˶�
} MoveMode;

/**
* @brief ϵͳ�����������
*/
typedef struct
{
	int scbMajorVersion;		///<scb���汾��
	int scbMinorVersion;		///<scb�ΰ汾��
	int cabTemperature;			///<���ƹ��¶�
	double robotAveragePower;	///<���ƹ�����ƽ������
	double robotAverageCurrent; ///<���ƹ�����ƽ������
	double instCurrent[6];		///<������6�����˲ʱ����
	double instVoltage[6];		///<������6�����˲ʱ��ѹ
	double instTemperature[6];	///<������6�����˲ʱ�¶�
} SystemMonitorData;

/**
* @brief ������������
*/
typedef struct
{
	double mass;			///<������������λ��kg
	CartesianTran centroid; ///<��������, ��λ��mm
} PayLoad;

/**
* @brief �ؽ�λ����������
*/
typedef struct
{
	double jVal[6]; ///< 6�ؽ�λ��ֵ����λ��rad
} JointValue;

/**
* @brief IO����ö��
*/
typedef enum
{
	IO_CABINET, ///< ���ƹ����IO
	IO_TOOL,	///< ����IO
	IO_EXTEND,	///< ��չIO
	IO_REALY,   ///< �̵���IO��Ŀǰ��CAB V3֧��DO
	IO_MODBUS_SLAVE, ///< Modbus��վIO,��0����
	IO_PROFINET_SLAVE, ///< Profinet��վIO,��0����
	IO_EIP_SLAVE      ///< ETHRENET/IP��վIO,��0����
} IOType;

/**
* @brief ������״̬����
*/
typedef struct
{
	BOOL estoped;	   ///< �Ƿ�ͣ
	BOOL poweredOn;	   ///< �Ƿ�򿪵�Դ
	BOOL servoEnabled; ///< �Ƿ�ʹ��
} RobotState;

/**
* @brief �����˻ص�����ָ��
*/
typedef void (*CallBackFuncType)(int);

/**
* @brief ����������ǰ������
*/

/**
* @brief �����˹ؽڼ������
*/
typedef struct
{
	double instCurrent;		///< ˲ʱ����
	double instVoltage;		///< ˲ʱ��ѹ
	double instTemperature; ///< ˲ʱ�¶�
	double instVel;			///< ˲ʱ�ٶ� ������1.7.0.20������
	double instTorq;		///< ˲ʱ����
} JointMonitorData;

/**
* @brief EXtio����
*/
typedef struct
{
	int din[256];				  ///< ��������din[0]Ϊ��Ч�źŵĸ���
	int dout[256];				  ///< �������dout[0]Ϊ��Ч�źŵĸ���
	int ain[256];				  ///< ģ������ain[0]Ϊ��Ч�źŵĸ���
	int aout[256];			      ///< ģ�����aout[0]Ϊ��Ч�źŵĸ���
} Io_group;

/**
* @brief �����˼������
*/
typedef struct
{
	double scbMajorVersion;				  ///< scb���汾��
	double scbMinorVersion;				  ///< scbС�汾��
	double cabTemperature;				  ///< �������¶�
	double robotAveragePower;			  ///< ������ƽ����ѹ
	double robotAverageCurrent;			  ///< ������ƽ������
	JointMonitorData jointMonitorData[6]; ///< ������6���ؽڵļ������
} RobotMonitorData;

/**
* @brief ���ش������������
*/
typedef struct
{
	char ip[20];		 ///< ���ش�����ip��ַ
	int port;			 ///< ���ش������˿ں�
	PayLoad payLoad;	 ///< ���߸���
	int status;			 ///< ���ش�����״̬
	int errcode;		 ///< ���ش������쳣������
	double actTorque[6]; ///< ���ش�����ʵ�ʽӴ���ֵ
	double torque[6];	 ///< ���ش�����ԭʼ����ֵ
} TorqSensorMonitorData;

/**
* @brief ������״̬�������,ʹ��get_robot_status�������»�����״̬����
*/
typedef struct
{
	int errcode;									///< ���������г���ʱ�����ţ�0Ϊ��������������Ϊ�����쳣
	int inpos;										///< �������˶��Ƿ�λ��־��0Ϊû�е�λ��1Ϊ�˶���λ
	int powered_on;									///< �������Ƿ��ϵ��־��0Ϊû���ϵ磬1Ϊ�ϵ�
	int enabled;									///< �������Ƿ�ʹ�ܱ�־��0Ϊû��ʹ�ܣ�1Ϊʹ��
	double rapidrate;								///< �������˶�����
	int protective_stop;							///< �������Ƿ��⵽��ײ��0Ϊû�м�⵽��ײ��1Ϊ��⵽��ײ
	int emergency_stop;								///< �������Ƿ�ͣ��0Ϊû�м�ͣ��1Ϊ��ͣ
	int dout[256];									///< �����˿��ƹ���������ź�,dout[0]Ϊ�źŵĸ���
	int din[256];									///< �����˿��ƹ����������ź�,din[0]Ϊ�źŵĸ���	
	double ain[256];								///< �����˿��ƹ�ģ�������ź�,ain[0]Ϊ�źŵĸ���
	double aout[256];								///< �����˿��ƹ�ģ������ź�,aout[0]Ϊ�źŵĸ���
	int tio_dout[16];								///< ������ĩ�˹�����������ź�,tio_dout[0]Ϊ�źŵĸ���
	int tio_din[16];								///< ������ĩ�˹������������ź�,tio_din[0]Ϊ�źŵĸ���
	double tio_ain[16];								///< ������ĩ�˹���ģ�������ź�,tio_ain[0]Ϊ�źŵĸ���
	int tio_key[3];                                 ///< ������ĩ�˹��߰�ť [0]free;[1]point;[2]pause_resume;
	Io_group extio;								    ///< �������ⲿӦ��IO
	Io_group modbus_slave;							///< ������Modbus��վ
	Io_group profinet_slave;						///< ������Profinet��վ
	Io_group eip_slave;								///< ������Ethernet/IP��վ
	unsigned int current_tool_id;					///< ������Ŀǰʹ�õĹ�������ϵid
	double cartesiantran_position[6];				///< ������ĩ�����ڵĵѿ����ռ�λ��
	double joint_position[6];						///< �����˹ؽڿռ�λ��
	unsigned int on_soft_limit;						///< �������Ƿ�����λ��0Ϊû�д�����λ������1Ϊ������λ����
	unsigned int current_user_id;					///< ������Ŀǰʹ�õ��û�����ϵid
	int drag_status;								///< �������Ƿ�����ק״̬��0Ϊû�д�����ק״̬��1Ϊ������ק״̬
	RobotMonitorData robot_monitor_data;			///< ������״̬�������
	TorqSensorMonitorData torq_sensor_monitor_data; ///< ���������ش�����״̬�������
	int is_socket_connect;							///< sdk�����������ͨ���Ƿ�������0Ϊ����ͨ���쳣��1Ϊ����ͨ������
} RobotStatus;

/**
* @brief �����˴�������������
*/
typedef struct
{
	long code;		   ///< ��������
	char message[120]; ///< �������Ӧ��ʾ��Ϣ
} ErrorCode;

/**
* @brief �켣�������ò����洢��������
*/
typedef struct
{
	double xyz_interval; ///< �ռ�λ�òɼ�����
	double rpy_interval; ///< ��̬�ɼ�����
	double vel;			 ///< ִ�нű������ٶ�
	double acc;			 ///< ִ�нű����м��ٶ�
} TrajTrackPara;

/**
* @brief ����ַ����洢��������
*/
typedef struct
{
	int len;			 ///< �ַ�������
	char name[128][128]; ///< ���ݴ洢��ά����
} MultStrStorType;

/**
* @brief �˶�������ѡ��
*/
typedef struct
{
	int executingLineId; ///< ��������id���
} OptionalCond;

/**
* @brief �����쳣�������˶��Զ���ֹ����ö��
*/
typedef enum
{
	MOT_KEEP,  ///< �����쳣ʱ�����˼�������ԭ�����˶�
	MOT_PAUSE, ///< �����쳣ʱ��������ͣ�˶�
	MOT_ABORT  ///< �����쳣ʱ��������ֹ�˶�
} ProcessType;

/**
* @brief ��˳���Ʋ�������
*/
typedef struct
{
	int opt;			 ///< ��˳���򣬿�ѡֵΪ 1 2 3 4 5 6�ֱ��Ӧ fx fy fz mx my mz,0����û�й�ѡ
	double ft_user;		 ///< �û��ö����������û����˵�����ĳ������������ٶȽ����˶�
	double ft_rebound;	 ///< �ص���:�����˻ص���ʼ״̬������
	double ft_constant;	 ///< ����
	int ft_normal_track; ///< ��������Ƿ�����0Ϊû�п�����1Ϊ����
} AdmitCtrlType;

/**
* @brief ��������˳���Ʋ�������
*/
typedef struct
{
	AdmitCtrlType admit_ctrl[6];
} RobotAdmitCtrl;

/**
* @brief �ٶ���˳���Ƶȼ��ͱ��ʵȼ�����
* �ٶ���˳���Ʒ������ȼ�������  1>rate1>rate2>rate3>rate4>0
* �ȼ�Ϊ1ʱ��ֻ������rate1,rate2�����ȼ���rate3,rate4��ֵΪ0
* �ȼ�Ϊ2ʱ��ֻ������rate1,rate2��rate3 �����ȼ���rate4��ֵΪ0
* �ȼ�Ϊ3ʱ�������� rate1,rate2��rate3,rate4 4���ȼ�
*/
typedef struct
{
	int vc_level; //�ٶ���˳���Ƶȼ�
	double rate1; //����1�ȼ�
	double rate2; //����2�ȼ�
	double rate3; //����3�ȼ�
	double rate4; //����4�ȼ�
} VelCom;

/**
* @brief �����������������������ط���
*/
typedef struct
{
	double fx; // ��x����������
	double fy; // ��y����������
	double fz; // ��z����������
	double tx; // ��x�����ط���
	double ty; // ��y�����ط���
	double tz; // ��z�����ط���
} FTxyz;

/**
* @brief ftp�ļ���������
*/
struct FtpFile
{
	const char *filename;
	FILE *stream;
};

/**
 *  @brief DH����
 */
typedef struct
{
	double alpha[6];
	double a[6];
	double d[6];
	double joint_homeoff[6];
} DHParam;

#endif
