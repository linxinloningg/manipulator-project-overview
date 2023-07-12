using System;
using System.Collections.Generic;
//using System.Numerics;
using System.Text;
using System.Runtime.InteropServices;


namespace jkType
{

	public class JKTYPE
	{
		/**
        * @brief 笛卡尔空间位置数据类型
        */
		[StructLayout(LayoutKind.Sequential)]
		public struct CartesianTran
		{

			public double x;       ///< x轴坐标,单位mm
			public double y;       ///< y轴坐标,单位mm
			public double z;       ///< z轴坐标,单位mm
		};

		/**
		* @brief 欧拉角姿态数据类型
		*/
		[StructLayout(LayoutKind.Sequential)]
		public struct Rpy
		{
			public double rx;      ///< 绕固定轴X旋转角度,单位：rad
			public double ry;	   ///< 绕固定轴Y旋转角度,单位：rad
			public double rz;      ///< 绕固定轴Z旋转角度,单位：rad
		};

		/**
		* @brief 四元数姿态数据类型
		*/
		[StructLayout(LayoutKind.Sequential)]
		public struct Quaternion
		{
			public double s;
			public double x;
			public double y;
			public double z;
		};

		/**
		*@brief 笛卡尔空间位姿类型
		*/
		[StructLayout(LayoutKind.Sequential)]
		public struct CartesianPose
		{
			public CartesianTran tran;     ///< 笛卡尔空间位置
			public Rpy rpy;                ///< 笛卡尔空间姿态
		};

		/**
		* @brief 旋转矩阵数据类型
		*/
		[StructLayout(LayoutKind.Sequential)]
		public struct RotMatrix
		{
			public CartesianTran x;        ///< x轴列分量
			public CartesianTran y;		   ///< y轴列分量
			public CartesianTran z;        ///< z轴列分量
		};

		/**
		* @brief 程序运行状态枚举类型
		*/
		public enum ProgramState
		{
			PROGRAM_IDLE,					///< 机器人停止运行
			PROGRAM_RUNNING,				///< 机器人正在运行
			PROGRAM_PAUSED					///< 机器人暂停	
		};

		/**
		* @brief 坐标系选择枚举类型
		*/
		public enum CoordType
		{
			COORD_BASE,						///< 基坐标系
			COORD_JOINT,					///< 关节空间
			COORD_TOOL						///< 工具坐标系
		};

		/**
		* @brief jog运动模式枚举
		*/
		public enum MoveMode
		{
			ABS = 0,						///< 绝对运动
			INCR,							///< 增量运动
			CONTINUE						///< 连续运动或延工具坐标运动
		};

		/**
		* @brief 系统监测数据类型
		*/
		[StructLayout(LayoutKind.Sequential)]
		public struct SystemMonitorData
		{
			public int scbMajorVersion;											///<scb主版本号
			public int scbMinorVersion;											///<scb次版本号
			public int cabTemperature;											///<控制柜温度	
			public double robotAveragePower;									///<控制柜总线平均功率
			public double robotAverageCurrent;									///<控制柜总线平均电流
			[MarshalAs(UnmanagedType.ByValArray, SizeConst = 6)]
			public double[] instCurrent;										///<机器人6个轴的瞬时电流
			[MarshalAs(UnmanagedType.ByValArray, SizeConst = 6)]
			public double[] instVoltage;										///<机器人6个轴的瞬时电压
			[MarshalAs(UnmanagedType.ByValArray, SizeConst = 6)]
			public double[] instTemperature;									///<机器人6个轴的瞬时温度
		};

		/**
		* @brief 负载数据类型
		*/
		[StructLayout(LayoutKind.Sequential)]
		public struct PayLoad
		{
			public double mass;													///<负载质量,单位：kg
			public CartesianTran centroid;										///<负载质心, 单位：mm
		};

		/**
		* @brief 关节位置数据类型
		*/
		public struct JointValue
		{
			[MarshalAs(UnmanagedType.ByValArray, SizeConst = 6)]
			public double[] jVal ;												///< 6关节位置值,单位：rad	
		};

		/**
		* @brief IO类型枚举
		*/
		public enum IOType
		{
			IO_CABINET, ///< 控制柜面板IO
			IO_TOOL,	///< 工具IO
			IO_EXTEND,	///< 扩展IO
			IO_REALY,   ///< 继电器IO，目前仅CAB V3支持DO
			IO_MODBUS_SLAVE, ///< Modbus从站IO,从0索引
			IO_PROFINET_SLAVE, ///< Profinet从站IO,从0索引
			IO_EIP_SLAVE      ///< ETHRENET/IP从站IO,从0索引
		};

		/**
		* @brief 机器人状态数据
		*/
		[StructLayout(LayoutKind.Sequential)]
		public struct RobotState
		{
			public int estoped;			///< 是否急停
			public int poweredOn;		///< 是否打开电源
			public int servoEnabled;    ///< 是否开启伺服模式
		};

		/**
		* @brief 机器人力矩数据
		*/
		[StructLayout(LayoutKind.Sequential)]
		public struct TorqueValue
		{
			[MarshalAs(UnmanagedType.ByValArray, SizeConst = 6)]
			public double[] jTorque;    ///< 是否使能
		}

		/**
		* @brief a group of io数据
		*/
		[StructLayout(LayoutKind.Sequential)]
		public struct Io_group
		{
			[MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
			public int[] din;				  ///< 数字输入din[0]为有效信号的个数
			[MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
			public int[] dout;				  ///< 数字输出dout[0]为有效信号的个数
			[MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
			public int[] ain;				  ///< 模拟输入ain[0]为有效信号的个数
			[MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
			public int[] aout;			      ///< 模拟输出aout[0]为有效信号的个数
		} 

		/**
		* @brief 机器人关节监测数据类型
		*/
		[StructLayout(LayoutKind.Sequential)]
		public struct JointMonitorData
		{
			public double instCurrent;         ///< 瞬时电流
			public double instVoltage;         ///< 瞬时电压
			public double instTemperature;     ///< 瞬时温度
			public double instVel;			   ///< 瞬时速度
			public double instTorq;			   ///< 瞬时力矩
		}


		/**
		* @brief 机器人监测数据类型
		*/
		[StructLayout(LayoutKind.Sequential)]
		public struct RobotMonitorData
		{
			double scbMajorVersion;								///< scb主版本号
			double scbMinorVersion;								///< scb小版本号
			double cabTemperature;								///< 控制器温度
			double robotAveragePower;							///< 机器人平均电压
			double robotAverageCurrent;							///< 机器人平均电流
			[MarshalAs(UnmanagedType.ByValArray, SizeConst = 6)]
			public JointMonitorData[] jointMonitorData;			///< 机器人6个关节的监测数据
		}

		/**
		* @brief 力矩传感器监测数据类型
		*/
		[StructLayout(LayoutKind.Sequential)]
		public struct TorqSensorMonitorData
		{
			[MarshalAs(UnmanagedType.ByValArray, SizeConst = 20)]
			public char[] ip;									///< 力矩传感器ip地址
			int port;											///< 力矩传感器端口号
			PayLoad payLoad;									///< 工具负载
			int status;											///< 力矩传感器状态
			int errcode;										///< 力矩传感器异常错误码
			[MarshalAs(UnmanagedType.ByValArray, SizeConst = 6)]
			public double[] actTorque;							///< 力矩传感器实际接触力值
			[MarshalAs(UnmanagedType.ByValArray, SizeConst = 6)]
			public double[] torque;								///< 力矩传感器原始读数值
		}

		/**
		* @brief 机器人状态监测数据,使用get_robot_status函数更新机器人状态数据
		*/
		
		[StructLayout(LayoutKind.Sequential)]
		public struct RobotStatus
		{
			public int errcode;												///< 机器人运行出错时错误编号,0为运行正常,其它为运行异常
			public int inpos;												///< 机器人运动是否到位标志,0为没有到位,1为运动到位
			public int powered_on;											///< 机器人是否上电标志,0为没有上电,1为上电
			public int enabled;												///< 机器人是否使能标志,0为没有使能,1为使能
			public double rapidrate;										///< 机器人运动倍率
			public int protective_stop;										///< 机器人是否检测到碰撞,0为没有检测到碰撞,1为检测到碰撞
			public int emergency_stop;										///< 机器人是否急停,0为没有急停,1为急停
			[MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
			public int []dout;												///< 机器人控制柜数字输出信号,dout[0]为信号的个数
			[MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
			public int []din;												///< 机器人控制柜数字输入信号,din[0]为信号的个数
			[MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
			public double []ain;											///< 机器人控制柜模拟输入信号,ain[0]为信号的个数
			[MarshalAs(UnmanagedType.ByValArray, SizeConst = 256)]
			public double []aout;											///< 机器人控制柜模拟输出信号,aout[0]为信号的个数
			[MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
			public int[] tio_dout;								        ///< 机器人末端工具数字输出信号,tio_dout[0]为信号的个数
			[MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
			public int[] tio_din;										///< 机器人末端工具数字输入信号,tio_din[0]为信号的个数
			[MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
			public double[] tio_ain;									///< 机器人末端工具模拟输入信号,tio_ain[0]为信号的个数
			[MarshalAs(UnmanagedType.ByValArray, SizeConst = 3)]
			public int[] tio_key;                                		///< 机器人末端工具按钮 [0]free;[1]point;[2]pause_resume;
			public Io_group extio;								    		///< 机器人外部应用IO
			public Io_group modbus_slave;									///< 机器人Modbus从站
			public Io_group profinet_slave;									///< 机器人Profinet从站
			public Io_group eip_slave;										///< 机器人Ethernet/IP从站
			public int current_tool_id;										///< 机器人目前使用的工具坐标系id
			[MarshalAs(UnmanagedType.ByValArray, SizeConst = 6)]
			public double []cartesiantran_position;							///< 机器人末端所在的笛卡尔空间位置
			[MarshalAs(UnmanagedType.ByValArray, SizeConst = 6)]
			public double []joint_position;									///< 机器人关节空间位置
			public int on_soft_limit;										///< 机器人是否处于限位,0为没有触发限位保护,1为触发限位保护
			public int current_user_id;										///< 机器人目前使用的用户坐标系id
			public int drag_status;											///< 机器人是否处于拖拽状态,0为没有处于拖拽状态,1为处于拖拽状态
			public RobotMonitorData robot_monitor_data;                     ///< 机器人状态监测数据
			public TorqSensorMonitorData torq_sensor_monitor_data;          ///< 机器人力矩传感器状态监测数据
			public int is_socket_connect;									///< sdk与控制器连接通道是否正常,0为连接通道异常,1为连接通道正常
		}


		/**
		* @brief 机器人错误码数据类型
		*/
		[StructLayout(LayoutKind.Sequential)]
		public struct ErrorCode
		{
			public long code;                                   ///< 错误码编号
			[MarshalAs(UnmanagedType.ByValArray, SizeConst = 120)]
			public char[] message;								///< 错误码对应提示信息
		}

		/**
		* @brief 轨迹复现配置参数数据类型
		*/
		[StructLayout(LayoutKind.Sequential)]
		public struct TrajTrackPara
		{
			public double xyz_interval;                         ///< 空间位置采集精度
			public double rpy_interval;                         ///< 姿态采集精度
			public double vel;                                  ///< 执行脚本运行速度
			public double acc;                                  ///< 执行脚本运行加速度
		}

		/**
		* @brief 多个字符串存储数据类型
		*/
		[StructLayout(LayoutKind.Sequential)]
		public struct MultStrStorType
		{
			public int len;										///< 字符串个数
			[MarshalAs(UnmanagedType.ByValArray, SizeConst = 128*128)]
			public char[] name ;                              ///< 数据存储二维数组
		}

		/**
		* @brief 运动参数可选项
		*/
		[StructLayout(LayoutKind.Sequential)]
		public struct OptionalCond
		{
			int executingLineId;                                ///< 控制命令id编号
		}

		/**
		* @brief 网络异常机器人运动自动终止类型枚举
		*/
		public enum ProcessType
		{
			MOT_KEEP,  ///< 网络异常时机器人继续保持原来的运动
			MOT_PAUSE, ///< 网络异常时机器人暂停运动
			MOT_ABORT  ///< 网络异常时机器人终止运动
		}

		/**
		* @brief 柔顺控制参数类型
		*/
		[StructLayout(LayoutKind.Sequential)]
		public struct AdmitCtrlType
		{
			int opt;             ///< 柔顺方向,可选值为 1 2 3 4 5 6分别对应 fx fy fz mx my mz,0代表没有勾选
			double ft_user;      ///< 用户用多大的力才能让机器人的沿着某个方向以最大速度进行运动
			double ft_rebound;   ///< 回弹力:机器人回到初始状态的能力
			double ft_constant;  ///< 恒力
			int ft_normal_track; ///< 法向跟踪是否开启,0为没有开启,1为开启
		}

		/**
		* @brief 机器人柔顺控制参数类型
		*/
		[StructLayout(LayoutKind.Sequential)]
		public struct RobotAdmitCtrl
		{
			[MarshalAs(UnmanagedType.ByValArray, SizeConst = 6)]
			public AdmitCtrlType[] admit_ctrl;
		}

		/**
		* @brief 速度柔顺控制等级和比率等级设置
		* 速度柔顺控制分三个等级,并且  1>rate1>rate2>rate3>rate4>0
		* 等级为1时,只能设置rate1,rate2两个等级。rate3,rate4的值为0
		* 等级为2时,只能设置rate1,rate2,rate3 三个等级。rate4的值为0
		* 等级为3时,能设置 rate1,rate2,rate3,rate4 4个等级
		*/
		[StructLayout(LayoutKind.Sequential)]
		public struct VelCom
		{
			int vc_level;                                         //速度柔顺控制等级
			double rate1;                                         //比率1等级
			double rate2;                                         //比率2等级
			double rate3;                                         //比率3等级
			double rate4;                                         //比率4等级
		}

		/**
		* @brief 力传感器的受力分量和力矩分量
		*/
		[StructLayout(LayoutKind.Sequential)]
		public struct FTxyz
		{
			public double fx;                                           // 沿x轴受力分量
			public double fy;                                           // 沿y轴受力分量
			public double fz;                                           // 沿z轴受力分量
			public double tx;                                           // 绕x轴力矩分量
			public double ty;                                           // 绕y轴力矩分量
			public double tz;                                           // 绕z轴力矩分量
		}

		/**
		*  @brief DH参数
		*/
		[StructLayout(LayoutKind.Sequential)]
		public struct DHParam
		{
			[MarshalAs(UnmanagedType.ByValArray, SizeConst = 6)]
			double[] alpha;
			[MarshalAs(UnmanagedType.ByValArray, SizeConst = 6)]
			double[] a;
			[MarshalAs(UnmanagedType.ByValArray, SizeConst = 6)]
			double[] d;
			[MarshalAs(UnmanagedType.ByValArray, SizeConst = 6)]
			double[] joint_homeoff;
		} 
	}
}
