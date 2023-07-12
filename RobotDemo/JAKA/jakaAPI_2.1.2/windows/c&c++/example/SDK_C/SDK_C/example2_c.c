#include "jakaAPI.h"
#include <stdio.h>
#include <windows.h>
#define PI 3.1415926

char IP[100] = "192.168.2.194";

//4.1~4.9机器人手动运动
int example_jog()
{
	//实例API对象demo 
	JKHD demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	create_handler(IP, &demo);
	//机器人上电
	power_on(&demo);
	//机器人上使能
	enable_robot(&demo);
	//关节空间运动，其中INCR代表增量运动，0.5代表速度为0.5rad/s ,pi代表执行该行命令运动3.14rad，
	jog(&demo,1, INCR, COORD_JOINT, 0.5, 30 * PI / 180);
	Sleep(10000);
	jog_stop(&demo,1);
	return 0;
}

//4.10关节速度上限180deg/s
int example_joint_move()
{
	//实例API对象demo 
	JKHD demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	create_handler(IP, &demo);
	//机器人上电
	power_on(&demo);
	//机器人上使能
	enable_robot(&demo);
	//定义并初始化关JointValue变量
	JointValue joint_pos = { 45 * PI / 180, 50 * PI / 180, 50 * PI / 180, 0 * PI / 180, 0 * PI / 180, 0 * PI / 180 };
	//关节空间运动，其中ABS代表绝对运动，TRUE代表指令是阻塞的，1代表速度为1rad/s  
	joint_move(&demo, &joint_pos, ABS, TRUE, 1);
	return 0;
}

//4.11机器人末端直线运动,注意避免奇异点
int example_linear_move()
{
	//实例API对象demo 
	JKHD demo;
	RobotStatus status;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	create_handler(IP, &demo);
	//机器人上电
	power_on(&demo);
	//机器人上使能
	enable_robot(&demo);
	//定义并初始化CartesianPose变量，旋转角为弧度。
	CartesianPose cart;
	cart.tran.x = 100; cart.tran.y = 200; cart.tran.z = 300;
	cart.rpy.rx = 120 * PI / 180; cart.rpy.ry = 90 * PI / 180; cart.rpy.rz = -90 * PI / 180;
	//笛卡尔空间运动，其中ABS代表绝对运动，FALSE代表指令是非阻塞的，10代表速度为10mm/s   
	printf("rx=%f , ry=%f, rz=%f\n", cart.rpy.rx, cart.rpy.ry, cart.rpy.rz);
	linear_move(&demo ,&cart, ABS, TRUE, 10);
	get_robot_status(&demo ,&status);
	printf("errcode=%d \nx=%f, y=%f, z=%f\n", status.errcode, status.cartesiantran_position[0], status.cartesiantran_position[1], status.cartesiantran_position[2]);
	printf("rx=%f, ry=%f, rz=%f", status.cartesiantran_position[3], status.cartesiantran_position[4], status.cartesiantran_position[5]);
	Sleep(1000);
	return 0;
}

//4.17设置数字输出
int example_set_digital_output()
{
	BOOL DO3;
	//实例API对象demo 
	JKHD demo;
	RobotStatus status;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	create_handler(IP, &demo);
	//机器人上电
	power_on(&demo);
	//机器人上使能
	enable_robot(&demo);
	//查询do3的状态
	get_digital_output(&demo,IO_CABINET, 2, &DO3);
	printf("D03 = %d\n", DO3);
	//io_cabinet是控制柜面板IO，2代表DO3，1对应要设置的DO值。
	set_digital_output(&demo,IO_CABINET, 2, 1);
	Sleep(1000);//需要window.h延时1s
	//查询do3的状态
	get_digital_output(&demo,IO_CABINET, 2, &DO3);
	printf("D03 = %d\n", DO3);
	return 0;
}

//4.18设置模拟输出
int example_set_analog_output()
{
	//实例API对象demo 
	JKHD demo;
	RobotStatus status;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	create_handler(IP, &demo);
	//机器人上电
	power_on(&demo);
	float AO35;
	//查询do的状态
	get_analog_output(&demo,IO_CABINET, 34, &AO35);
	printf("A035 = %f\n", AO35);
	//io_cabinet是控制柜面板IO，2代表DO3，1.5对应要设置的DO值。
	set_analog_output(&demo,IO_CABINET, 34, 1.5);
	Sleep(1000);//需要window.h延时1s
	//查询do的状态
	get_analog_output(&demo,IO_CABINET, 34, &AO35);
	printf("A035 = %f\n", AO35);
	return 0;
}

//4.24查询扩展IO状态
int example_is_extio_running()
{
	//实例API对象demo 
	JKHD demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	create_handler(IP, &demo);
	//机器人上电
	power_on(&demo);
	BOOL is_running;
	//查询TIO的状态
	is_extio_running(&demo, &is_running);
	printf("tio = %d\n", is_running);
	return 0;
}

//4.25~4.32脚本加载，运行控制，过程查看
int example_program()
{
	char name[128];
	int cur_line;
	//实例API对象demo 
	JKHD demo;
	ProgramState pstatus;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	create_handler(IP, &demo);
	//机器人上电
	power_on(&demo);
	//机器人上使能
	enable_robot(&demo);
	//加载预先通过app编辑的example脚本
	program_load(&demo, "example");
	//获取已加载的程序名
	get_loaded_program(&demo,name);
	printf("Pro_name is :  %s", name);
	//运行当前加载的程序
	program_run(&demo);
	Sleep(1000);//需要window.h延时1s
	//暂停当前运行的程序
	program_pause(&demo);
	//获取当前执行程序的行号
	get_current_line(&demo, &cur_line);
	printf("cur_line is : %d", cur_line);
	//获取当前程序状态
	get_program_state(&demo, &pstatus);
	printf("pro_status is : %d",pstatus);
	//继续运行当前程序
	program_resume(&demo);
	Sleep(10000);//需要window.h延时10s
	//终止当前程序
	program_abort(&demo);
	return 0;
}

//4.33~34机器人速度查看及调整
int example_rapidrate()
{
	double rapid_rate;
	//实例API对象demo 
	JKHD demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	create_handler(IP, &demo);
	//机器人上电
	power_on(&demo);
	//机器人上使能
	enable_robot(&demo);
	get_rapidrate(&demo, &rapid_rate);
	printf("rapid_rate is : %f",rapid_rate);
	set_rapidrate(&demo, 0.4);
	Sleep(100);
	get_rapidrate(&demo, &rapid_rate);
	printf("rapid_rate is : %f", rapid_rate );
	return 0;
}

//4.35~38工具坐标系查看及调整
int example_tool()
{
	int id_ret, id_set;
	id_set = 2;
	CartesianPose tcp_ret, tcp_set;
	char name[50] = "test";
	//实例API对象demo 
	JKHD demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	create_handler(IP, &demo);
	//机器人上电
	power_on(&demo);
	//查询当前使用的工具ID
	get_tool_id(&demo, &id_ret);
	//获取当前使用的工具信息
	get_tool_data(&demo, id_ret, &tcp_ret);
	printf("id_using=%d \nx=%f, y=%f, z=%f\n", id_ret, tcp_ret.tran.x, tcp_ret.tran.y, tcp_ret.tran.y);
	printf("rx=%f, ry=%f, rz=%f\n", tcp_ret.rpy.rx, tcp_ret.rpy.ry, tcp_ret.rpy.rz);
	//初始化工具坐标
	tcp_set.tran.x = 0; tcp_set.tran.y = 0; tcp_set.tran.z = 10;
	tcp_set.rpy.rx = 120 * PI / 180; tcp_set.rpy.ry = 90 * PI / 180; tcp_set.rpy.rz = -90 * PI / 180;
	//设置工具信息
	set_tool_data(&demo, id_set, &tcp_set, name);
	//切换当前使用的工具坐标
	set_tool_id(&demo, id_set);
	Sleep(1000);
	//查询当前使用的工具ID
	get_tool_id(&demo, &id_ret);
	//获取设置的工具信息
	get_tool_data(&demo, id_ret, &tcp_ret);
	printf("id_using=%d \nx=%f, y=%f, z=%f\n", id_ret, tcp_ret.tran.x, tcp_ret.tran.y, tcp_ret.tran.y);
	printf("rx=%f, ry=%f, rz=%f\n", tcp_ret.rpy.rx, tcp_ret.rpy.ry, tcp_ret.rpy.rz);
	return 0;
}

//4.39~42用户坐标系查看及调整
int example_user_frame()
{
	int id_ret, id_set;
	id_set = 2;
	CartesianPose tcp_ret, tcp_set;
	char name[50] = "test";
	//实例API对象demo 
	JKHD demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	create_handler(IP, &demo);
	//机器人上电
	power_on(&demo);
	//查询当前使用的用户坐标系ID
	get_user_frame_id(&demo, &id_ret);
	//获取当前使用的用户坐标系信息
	get_user_frame_data(&demo, id_ret, &tcp_ret);
	printf("id_using=%d \nx=%f, y=%f, z=%f\n", id_ret, tcp_ret.tran.x, tcp_ret.tran.y, tcp_ret.tran.y);
	printf("rx=%f, ry=%f, rz=%f\n", tcp_ret.rpy.rx, tcp_ret.rpy.ry, tcp_ret.rpy.rz);
	//初始化用户坐标系坐标
	tcp_set.tran.x = 0; tcp_set.tran.y = 0; tcp_set.tran.z = 10;
	tcp_set.rpy.rx = 120 * PI / 180; tcp_set.rpy.ry = 90 * PI / 180; tcp_set.rpy.rz = -90 * PI / 180;
	//设置用户坐标系信息
	set_user_frame_data(&demo, id_set, &tcp_set, name);
	//切换当前使用的用户坐标系坐标
	set_user_frame_id(&demo, id_set);
	//查询当前使用的用户坐标系ID
	get_user_frame_id(&demo, &id_ret);
	//获取设置的用户坐标系信息
	get_user_frame_data(&demo, id_ret, &tcp_ret);
	printf("id_using=%d \nx=%f, y=%f, z=%f\n", id_ret, tcp_ret.tran.x, tcp_ret.tran.y, tcp_ret.tran.y);
	printf("rx=%f, ry=%f, rz=%f\n", tcp_ret.rpy.rx, tcp_ret.rpy.ry, tcp_ret.rpy.rz);

	return 0;
}

//4.43~44拖拽模式
int  example_drag()
{
	BOOL in_drag;
	//实例API对象demo 
	JKHD demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	create_handler(IP, &demo);
	//机器人上电
	power_on(&demo);
	//机器人上使能
	enable_robot(&demo);
	//确认机器人是否在拖拽模式下
	is_in_drag_mode(&demo, &in_drag);
	printf("in_drag is : %d", in_drag);
	//使能拖拽模式
	drag_mode_enable(&demo, TRUE);
	Sleep(1000);
	is_in_drag_mode(&demo, &in_drag);
	printf("in_drag is : %d", in_drag);
	//去使能拖拽模式
	drag_mode_enable(&demo, FALSE);
	Sleep(100);
	is_in_drag_mode(&demo, &in_drag);
	printf("in_drag is : %d",in_drag);
	while (1)
	{
		is_in_drag_mode(&demo, &in_drag);
		printf("in_drag is : " ,in_drag);
		Sleep(100);
	}
	return 0;
}

//4.45获取机器人状态(急停 上电 伺服使能)
int example_get_robstate()
{
	//实例API对象demo 
	JKHD demo;
	RobotState state;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	create_handler(IP, &demo);
	//机器人上电
	power_on(&demo);
	//机器人上使能
	enable_robot(&demo);
	get_robot_state(&demo, &state);
	printf( "is e_stoped : ", state.estoped );
	return 0;
}

//4.46获取工具末端位姿
int example_get_tcp_position()
{
	//实例API对象demo 
	JKHD demo;
	CartesianPose tcp_pos;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	create_handler(IP, &demo);
	//机器人上电
	power_on(&demo);
	//机器人上使能
	enable_robot(&demo);
	//获取工具末端位姿
	get_tcp_position(&demo ,&tcp_pos);
	return 0;
}

//4.47获取当前机器人关节角
int example_get_joint_position()
{
	//实例API对象demo 
	JKHD demo;
	JointValue jot_pos;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	create_handler(IP, &demo);
	//机器人上电
	power_on(&demo);
	//机器人上使能
	enable_robot(&demo);
	//获取当前关节角
	get_joint_position(&demo, &jot_pos);
	return 0;
}

//4.49查询是否超出限位
int example_is_on_limit()
{
	//实例API对象demo 
	JKHD demo;
	BOOL on_limit;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	create_handler(IP, &demo);
	//机器人上电
	power_on(&demo);
	//机器人上使能
	enable_robot(&demo);
	while (1)
	{
		//查询是否超限
		is_on_limit(&demo, &on_limit);
		printf(" on_limit is :%d",on_limit );
		Sleep(200);
	}
	return 0;
}

//4.50查询机器人运动是否停止
int example_is_in_pos()
{
	//实例API对象demo 
	JKHD demo;
	BOOL in_pos;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	create_handler(IP, &demo);
	//机器人上电
	power_on(&demo);
	//机器人上使能
	enable_robot(&demo);
	while (1)
	{
		//查询是否运动停止
		is_in_pos(&demo, &in_pos);
		printf(" in_pos is :%d",in_pos);
		Sleep(200);
	}
	return 0;
}

//4.48 4.51碰撞保护状态查看，恢复
int example_collision_recover()
{
	//实例API对象demo 
	JKHD demo;
	BOOL in_collision;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	create_handler(IP, &demo);
	//机器人上电
	power_on(&demo);
	//机器人上使能
	enable_robot(&demo);
	//查询是否处于碰撞保护状态
	is_in_collision(&demo, &in_collision);
	if (in_collision)
		//如果处于碰撞保护模式，则从碰撞保护中恢复
	{
		collision_recover(&demo);
	}
	else
	{
		printf("robot is not collision");
	}
	return 0;
}

//4.52~53碰撞等级查看，设置
int example_collision_level()
{
	//实例API对象demo 
	JKHD demo;
	int level;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	create_handler(IP, &demo);
	//机器人上电
	power_on(&demo);
	//机器人上使能
	enable_robot(&demo);
	//查询当前碰撞等级
	get_collision_level(&demo, &level);
	printf(" collision level is :%d",level );
	//设置碰撞等级，[0,5]，0为关闭碰撞，1为碰撞阈值25N，2为碰撞阈值50N，3为碰撞阈值75N，4为碰撞阈值100N，5为碰撞阈值125N，
	set_collision_level(&demo, 2);
	//查询当前碰撞等级
	get_collision_level(&demo, &level);
	printf( " collision level is :%d",level);
	return 0;
}

// 4.54机器人逆解 已知tcp_pos,求joint_pos
int example_kine_inverse()
{
	int ret;
	//实例API对象demo 
	JKHD demo;
	//初始化参考点
	JointValue ref_jpos = { 0.558, 0.872, 0.872 , 0.349, 0.191, 0.191 };
	//初始化笛卡尔空间点坐标
	CartesianPose tcp_pos;
	tcp_pos.tran.x = 243.568; tcp_pos.tran.y = 164.064; tcp_pos.tran.z = 742.002;
	tcp_pos.rpy.rx = -1.81826; tcp_pos.rpy.ry = -0.834253;  tcp_pos.rpy.rz = -2.30243;
	//初始化返回值
	JointValue joint_pos = { 0,0,0,0,0,0 }; ;
	ret = kine_inverse(&demo, &ref_jpos, &tcp_pos, &joint_pos);
	for (int i = 0; i < 6; i++)
	{
		printf("joint_pos[%d] is : %d ", i, joint_pos.jVal[i]);
	}
	return 0;
}

// 4.55机器人正解 已知joint_pos,求tcp_pos
int example_kine_forward()
{
	int ret;
	//实例API对象demo 
	JKHD demo;
	//初始化笛卡尔空间点坐标
	CartesianPose tcp_pos;
	//初始化返回值
	JointValue joint_pos = { 0.558, 0.872, 0.872 , 0.349, 0.191, 0.191 };
	ret = kine_forward(&demo, &joint_pos, &tcp_pos);
	printf("tcp_pos is :\n x:%d  y:%d  z:%d rx:%d  ry:%d  rz:%d", tcp_pos.tran.x, tcp_pos.tran.y, tcp_pos.tran.z, tcp_pos.rpy.rx, tcp_pos.rpy.ry, tcp_pos.rpy.rz);
	return 0;
}

// 4.56欧拉角到旋转矩阵
int example_rpy_to_rot_matrix()
{
	int ret;
	//实例API对象demo 
	JKHD demo;
	//初始化欧拉角
	Rpy rpy;
	rpy.rx = -1.81826; rpy.ry = -0.834253;  rpy.rz = -2.30243;
	//初始化旋转矩阵
	RotMatrix rot_matrix;
	ret = rpy_to_rot_matrix(&demo, &rpy, &rot_matrix);
	printf("     eul2rotm");
	printf("%f %f %f\n", rot_matrix.x.x, rot_matrix.y.x, rot_matrix.z.x);
	printf("%f %f %f\n", rot_matrix.x.y, rot_matrix.y.y, rot_matrix.z.y);
	printf("%f %f %f\n", rot_matrix.x.z, rot_matrix.y.z, rot_matrix.z.z);
	return 0;
}

// 4.57旋转矩阵--->欧拉角
int example_rot_matrix_to_rpy()
{
	int ret;
	//实例API对象demo 
	JKHD demo;
	//初始化欧拉角
	Rpy rpy;
	//初始化旋转矩阵
	RotMatrix rot_matrix;
	rot_matrix.x.x = -0.4488, rot_matrix.y.x = -0.4998, rot_matrix.z.x = 0.7408;
	rot_matrix.x.y = -0.6621, rot_matrix.y.y = -0.3708, rot_matrix.z.y = -0.6513;
	rot_matrix.x.z = 0.6002, rot_matrix.y.z = -0.7828, rot_matrix.z.z = -0.1645;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	create_handler(IP, &demo);
	ret = rot_matrix_to_rpy(&demo, &rot_matrix, &rpy);
	printf(" %d    rotm2eul:",ret);
	printf("%f %f %f \n", rpy.rx, rpy.ry, rpy.rz);
	return 0;
}

// 4.58四元数-->旋转矩阵
int example_quaternion_to_rot_matrix()
{
	int ret;
	//实例API对象demo 
	JKHD demo;
	//初始化四元数
	Quaternion quat;
	quat.s = 0.0629;  quat.x = 0.522886; quat.y = -0.5592;  quat.z = 0.6453;
	//quat.s = 0.707;  quat.x = 0; quat.y = 0.707107;  quat.z = 0;
	//初始化旋转矩阵
	RotMatrix rot_matrix;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	create_handler(IP, &demo);
	ret = quaternion_to_rot_matrix(&demo, &quat, &rot_matrix);
	printf(" %d    quatl2rotm:",ret);
	printf("%f %f %f\n", rot_matrix.x.x, rot_matrix.y.x, rot_matrix.z.x);
	printf("%f %f %f\n", rot_matrix.x.y, rot_matrix.y.y, rot_matrix.z.y);
	printf("%f %f %f\n", rot_matrix.x.z, rot_matrix.y.z, rot_matrix.z.z);
	return 0;
}

// 4.59旋转矩阵--->四元数
int example_rot_matrix_to_quaternion()
{
	int ret;
	//实例API对象demo 
	JKHD demo;
	//初始化四元数
	Quaternion quat;
	//初始化旋转矩阵
	RotMatrix rot_matrix;
	rot_matrix.x.x = -0.4488774, rot_matrix.y.x = -0.499824, rot_matrix.z.x = 0.740795;
	rot_matrix.x.y = -0.662098, rot_matrix.y.y = -0.370777, rot_matrix.z.y = -0.651268;
	rot_matrix.x.z = 0.600190, rot_matrix.y.z = -0.782751, rot_matrix.z.z = -0.164538;

	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	create_handler(IP, &demo);
	ret = rot_matrix_to_quaternion(&demo, &rot_matrix, &quat);
	printf(" %d   rotm2quat:",ret);
	printf("%lf %lf %lf %lf \n", quat.s, quat.x, quat.y, quat.z);
	return 0;
}

// 4.60 注册机器人出错函数
//错误处理，类中断
void user_error_handle(int error_code)
{
	printf("%d",error_code);
}
//注册
int example_set_err_handle()
{
	//实例API对象demo 
	JKHD demo;
	//登陆控制器，需要将192.168.2.229替换为自己控制器的IP
	create_handler(IP, &demo);
	//机器人上电
	power_on(&demo);
	//机器人上使能
	enable_robot(&demo);
	//设置用户异常回调函数
	set_error_handler(&demo, user_error_handle);
	return 0;
}

//4.61~4.62负载查看及设置
int example_payload()
{
	//实例API对象demo 
	JKHD demo;
	PayLoad payloadret;
	PayLoad payload_set;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	create_handler(IP, &demo);
	//查询当前负载数据
	get_payload(&demo, &payloadret);
	printf(" payload mass is : %f kg",payloadret.mass);
	printf(" payload center of mass is \nx: %f  y: %f z: %f ", payloadret.centroid.x , payloadret.centroid.y ,payloadret.centroid.z);
	payload_set.mass = 1.0;
	//单位mm
	payload_set.centroid.x = 0; payload_set.centroid.y = 0; payload_set.centroid.z = 10;
	//设置当前负载数据
	set_payload(&demo, &payload_set);
	//查询当前负载数据
	get_payload(&demo, &payloadret);
	printf(" payload mass is : %f kg", payloadret.mass);
	printf(" payload center of mass is \nx: %f  y: %f z: %f ", payloadret.centroid.x, payloadret.centroid.y, payloadret.centroid.z);
	return 0;
}

//4.63获取sdk版本号
int example_getsdk_version()
{
	//实例API对象demo 
	JKHD demo;
	char ver[100];
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	create_handler(IP, &demo);
	//查询当前SDK版本
	get_sdk_version(&demo, ver);
	printf(" SDK version is :%s", ver );
	return 0;
}

//4.64获取控制器ip
int example_get_controller_ip()
{
	int ret;
	//实例API对象demo 
	JKHD demo;
	////登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	//create_handler(IP, &demo);
	char ip_list[2000] = "AA";
	char  controller_name1[50] = "";
	printf(" %d ip_list is :\n %s\n", ip_list, ip_list);
	//获取控制器ip
	ret = get_controller_ip(controller_name1, ip_list);
	printf(" %d ip_list is :\n %s\n" ,ip_list, ip_list);
	return 0;
}

//4.65获取机器人状态监测数据
int example_get_robot_status()
{
	//实例API对象demo 
	JKHD demo;
	RobotStatus robstatus;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	create_handler(IP, &demo);
	set_debug_mode(&demo, TRUE);
	//机器人上电
	power_on(&demo);
	//机器人上使能
	enable_robot(&demo);
	while (1)
	{
		Sleep(1000);
		//获取机器人状态监测数据
		get_robot_status(&demo, &robstatus);
		printf("is_connect: %d\n", robstatus.is_socket_connect);
	}
	disable_robot(&demo);
	power_off(&demo);
	destory_handler(&demo);
	return 0;
}

//4.66设置SDK是否开启调试模式
int example_set_debug_mode()
{
	BOOL mode;
	//实例API对象demo 
	JKHD demo;
	//设置调试模式
	set_debug_mode(&demo, TRUE);
	printf("debug :true");
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	create_handler(IP, &demo);
	//机器人上电
	power_on(&demo);
	//机器人上使能
	enable_robot(&demo);
	return 0;
}

//4.67机器人运动终止
int example_motion_abort()
{
	//实例API对象demo 
	JKHD demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	create_handler(IP, &demo);
	//机器人上电
	power_on(&demo);
	//机器人上使能
	enable_robot(&demo);
	//定义并初始化关JointValue变量
	printf("start_move");
	JointValue joint_pos = { 0 * PI / 180, 0 * PI / 180, 50 * PI / 180, 0 * PI / 180, 0 * PI / 180, 0 * PI / 180 };
	//关节空间运动，其中ABS代表绝对运动，TRUE代表指令是阻塞的，1代表速度为1rad/s  
	joint_move(&demo, &joint_pos, ABS, FALSE, 1);
	Sleep(500);
	//运动0.5s后终止
	//motion_abort(&demo);
	printf("stop_move");
	return 0;
}

//4.68~4.69错误码查看
int example_get_last_errcode()
{
	int ret;
	char path[100] = "E:\\JAKA_ERROR_CODE.csv";
	//实例API对象demo 
	JKHD demo;
	ErrorCode Eret;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	create_handler(IP, &demo);
	//机器人上电
	power_on(&demo);
	//机器人上使能
	enable_robot(&demo);
	ret = program_load(&demo, "not_exist999875");//故意加载一个不存在的程序，引发报错。
	get_last_error(&demo, &Eret);//查询最后一个报错信息
	printf(" error code is : %x \nmessage:%s " ,Eret.code, Eret.message);
	ret = set_errorcode_file_path(&demo, path);//设置错误码说明文件
	get_last_error(&demo, &Eret);//查询最后一个报错信息
	printf(" error code is : %x \nmessage:%s ", Eret.code, Eret.message);
	return 0;
}

//4.70~4.71轨迹复现参数查看及设置
int example_traj_config()
{
	//实例API对象demo 
	JKHD demo;
	TrajTrackPara trajpar_read;
	TrajTrackPara trajpar_set;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	create_handler(IP, &demo);
	//查询当前轨迹复现参数
	get_traj_config(&demo, &trajpar_read);
	printf(" trajTrackPara is :\n xyz interval:%f  rpy interval is :%f  vel:%f  acc:%f ", trajpar_read.xyz_interval, trajpar_read.rpy_interval, trajpar_read.vel, trajpar_read.acc);
	//设置当前轨迹复现参数
	trajpar_set.xyz_interval = 0.01; trajpar_set.rpy_interval = 0.01; trajpar_set.vel = 10; trajpar_set.acc = 2;
	set_traj_config(&demo, &trajpar_set);

	//查询当前轨迹复现参数
	get_traj_config(&demo, &trajpar_read);
	printf(" trajTrackPara is :\n xyz interval:%f  rpy interval is :%f  vel:%f  acc:%f ", trajpar_read.xyz_interval, trajpar_read.rpy_interval, trajpar_read.vel, trajpar_read.acc);
	return 0;
}

//4.72~4.73轨迹采集开关与状态查询
int example_traj_sample()
{
	BOOL samp_stu;
	//实例API对象demo 
	JKHD demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	create_handler(IP, &demo);
	//机器人上电
	power_on(&demo);
	//机器人上使能
	enable_robot(&demo);
	char name[20] = "testxx";
	//开启轨迹复现数据采集开关
	set_traj_sample_mode(&demo, TRUE, name);
	//查询轨迹复现采集状态
	get_traj_sample_status(&demo, &samp_stu);
	Sleep(10000);
	set_traj_sample_mode(&demo, FALSE, name);
	return 0;
}

//4.74查询控制器中已经存在的轨迹复现数据的文件名
int example_get_traj_existed_filename()
{
	//实例API对象demo 
	JKHD demo;
	MultStrStorType traj_file;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	create_handler(IP, &demo);

	//查询当前轨迹文件名。
	get_exist_traj_file_name(&demo, &traj_file);
	printf( "file nums :%d" , traj_file.len);
	for (int i = 0; i < traj_file.len; i++)
		printf("%s\n",traj_file.name[i]);
	return 0;
}

//4.75重命名轨迹复现的数据文件名
int example_rename_traj_file_name()
{
	//实例API对象demo 
	JKHD demo;
	MultStrStorType traj_file;
	char name_new[20] = "555";
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	create_handler(IP, &demo);
	//查询当前轨迹文件名。
	get_exist_traj_file_name(&demo, &traj_file);
	printf("file nums :%d", traj_file.len);
	for (int i = 0; i < traj_file.len; i++)
		printf("%s\n", traj_file.name[i]);
	//重命名轨迹复现的数据文件名
	rename_traj_file_name(&demo, traj_file.name[0], name_new);
	//查询当前轨迹文件名。
	get_exist_traj_file_name(&demo, &traj_file);
	printf("file nums :%d", traj_file.len);
	for (int i = 0; i < traj_file.len; i++)
		printf("%s\n", traj_file.name[i]);
	return 0;
}

//4.77 


//4.80机器人圆弧运动 ，关节速度上限180deg/s
int example_circle_move()
{
	OptionalCond opt;
	CartesianPose end_p, mid_p;
	end_p.tran.x = -200; end_p.tran.y = 400; end_p.tran.z = 400;
	end_p.rpy.rx = -90 * PI / 180; end_p.rpy.ry = 0 * PI / 180; end_p.rpy.rz = 0 * PI / 180;
	mid_p.tran.x = -300; mid_p.tran.y = 400; mid_p.tran.z = 500;
	mid_p.rpy.rx = -90 * PI / 180; mid_p.rpy.ry = 0 * PI / 180; mid_p.rpy.rz = 0 * PI / 180;
	//实例API对象demo 
	JKHD demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	create_handler(IP, &demo);
	//机器人上电
	power_on(&demo);
	//机器人上使能
	enable_robot(&demo);
	//定义并初始化关JointValue变量
	JointValue joint_pos = { 85.76 * PI / 180, -6.207 * PI / 180, 111.269 * PI / 180, 74.938 * PI / 180, 94.24 * PI / 180, 0 * PI / 180 };
	//关节空间运动，其中ABS代表绝对运动，TRUE代表指令是阻塞的，1代表速度为1rad/s  
	joint_move(&demo, &joint_pos, ABS, TRUE, 1);
	//圆弧运动，其中ABS代表绝对运动，TRUE代表指令是阻塞的，20代表直线速度为20mm/s，1代表加速度，0.1代表机器人终点误差，opt为可选参数。 
	circular_move(&demo, &end_p, &mid_p, ABS, TRUE, 20, 1, 0.1, &opt);
	return 0;
}

//4.81 servo模式禁用滤波器
int example_servo_use_none_filter()
{
	int ret;
	//实例API对象demo 
	JKHD demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	create_handler(IP, &demo);
	//机器人上电
	power_on(&demo);
	//机器人上使能
	enable_robot(&demo);
	ret = servo_move_use_none_filter(&demo);
	return 0;
}


//4.82 servo模式下关节空间一阶低通滤波
int example_servo_use_joint_LPF()
{
	int ret;
	//实例API对象demo 
	JKHD demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	create_handler(IP, &demo);
	//机器人上电
	power_on(&demo);
	//机器人上使能
	enable_robot(&demo);
	//servo模式下关节空间一阶低通滤波,截止频率0.5Hz
	ret = servo_move_use_joint_LPF(&demo, 50);
	return 0;
}

//4.85 servo模式下关节空间非线性滤波
int example_servo_use_joint_NLF()
{
	int ret;
	//实例API对象demo 
	JKHD demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	create_handler(IP, &demo);
	//机器人上电
	power_on(&demo);
	//机器人上使能
	enable_robot(&demo);
	//servo模式下关节空间非线性滤波
	ret = servo_move_use_joint_NLF(&demo, 2, 2, 4);
	return 0;
}

//4.86 servo模式下笛卡尔空间非线性滤波
int example_servo_use_carte_NLF()
{
	int ret;
	//实例API对象demo 
	JKHD demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	create_handler(IP, &demo);
	//机器人上电
	power_on(&demo);
	//机器人上使能
	enable_robot(&demo);
	//servo模式下笛卡尔空间非线性滤波
	ret = servo_move_use_carte_NLF(&demo, 2, 2, 4, 2, 2, 4);
	return 0;
}

//4.87 servo模式下关节空间多阶均值滤波
int example_servo_use_joint_MMF()
{
	int ret;
	//实例API对象demo 
	JKHD demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	create_handler(IP, &demo);
	//机器人上电
	power_on(&demo);
	//机器人上使能
	enable_robot(&demo);
	//servo模式下关节空间多阶均值滤波
	ret = servo_move_use_joint_MMF(&demo, 200, 2, 4, 2);
	return 0;
}

//4.88 servo模式下速度前瞻参数设置
int example_speed_foresight()
{
	int ret;
	//实例API对象demo 
	JKHD demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	create_handler(IP, &demo);
	//机器人上电
	power_on(&demo);
	//机器人上使能
	enable_robot(&demo);
	//servo模式下关节空间多阶均值滤波
	ret = servo_speed_foresight(&demo, 200, 2);
	return 0;
}

//4.89 设置SDK日志路径
int example_set_SDK_filepath()
{
	char path[20] = "E://";
	int ret;
	//实例API对象demo 
	JKHD demo;
	ret = set_SDK_filepath(&demo, path);//设置SDK文件路径
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	create_handler(IP, &demo);
	//机器人上电
	power_on(&demo);
	//机器人上使能
	enable_robot(&demo);
	return 0;
}

//4.90 设置传感器品牌
int example_set_torsensor_brand()
{
	int ret;
	//实例API对象demo 
	JKHD demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	create_handler(IP, &demo);
	//机器人上电
	power_on(&demo);
	//机器人上使能
	enable_robot(&demo);
	//设置传感器品牌
	ret = set_torsenosr_brand(&demo, 1);
	return 0;
}

//4.91 获取传感器品牌
int example_get_torsensor_brand()
{
	int ret, cur_sensor;
	//实例API对象demo 
	JKHD demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	create_handler(IP, &demo);
	//机器人上电
	power_on(&demo );
	//机器人上使能
	enable_robot(&demo);
	//获取传感器品牌
	ret = get_torsenosr_brand(&demo, &cur_sensor);
	printf("cur_sensor is :%d", cur_sensor);
	return 0;
}

//4.92 开启或关闭力矩传感器
int example_set_torque_sensor_mode()
{
	int ret;
	//实例API对象demo 
	JKHD demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	create_handler(IP, &demo);
	//机器人上电
	power_on(&demo);
	//机器人上使能
	enable_robot(&demo);
	//设置力矩传感器状态，1打开，0关闭
	ret = set_torque_sensor_mode(&demo, 1);
	return 0;
}

//4.93 设置柔顺控制参数
int example_set_admit_ctrl_config()
{
	int ret;
	//实例API对象demo 
	JKHD demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	create_handler(IP, &demo);
	//机器人上电
	power_on(&demo);
	//机器人上使能
	enable_robot(&demo);
	//设置柔顺控制参数
	ret = set_admit_ctrl_config(&demo, 1, 1, 50, 30, 0, 0);
	return 0;
}

//4.94~4.98 辨识工具末端负载和获取负载辨识状态，设置与获取传感器末端负载
int example_sensor_payload()
{
	JointValue joint_pos;
	PayLoad pl, pl_ret;
	int ret;
	//实例API对象demo 
	JKHD demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	create_handler(IP, &demo);
	//机器人上电
	power_on(&demo);
	//机器人上使能
	enable_robot(&demo);
	//开始辨识传感器负载
	ret = start_torq_sensor_payload_identify(&demo, &joint_pos);
	do
	{
		//查询传感器负载状态
		get_torq_sensor_identify_staus(&demo, &ret);
	} while (1 == ret);
	//获取辨识结果
	ret = get_torq_sensor_payload_identify_result(&demo, &pl);
	//设置传感器末端负载
	ret = set_torq_sensor_tool_payload(&demo, &pl);
	Sleep(10000);
	//获取当前设置的传感器末端负载
	ret = get_torq_sensor_tool_payload(&demo, &pl_ret);
	Sleep(10000);
	return 0;
}

//4.99 力控拖拽使能
int example_enable_admittance_ctrl()
{
	int ret;
	//实例API对象demo 
	JKHD demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	create_handler(IP, &demo);
	//机器人上电
	power_on(&demo);
	//机器人上使能
	enable_robot(&demo);
	//设置力控拖拽使能，1打开，0关闭
	ret = enable_admittance_ctrl(&demo, 1);
	return 0;
}

//4.100~101 设置与获取力控类型和传感器初始化状态
int example_set_compliant_type()
{
	int ret, sensor_compensation, compliance_type;
	//实例API对象demo 
	JKHD demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	create_handler(IP, &demo);
	//机器人上电
	power_on(&demo);
	//机器人上使能
	enable_robot(&demo);
	//设置力控类型和传感器初始化状态
	ret = set_compliant_type(&demo, 1, 1);
	Sleep(1000);
	ret = get_compliant_type(&demo, &sensor_compensation, &compliance_type);
	Sleep(1000);
	return 0;
}

//4.102 获取力控柔顺控制参数
int example_get_admit_ctrl_config()
{
	RobotAdmitCtrl adm_ctr_cfg;
	int ret;
	//实例API对象demo 
	JKHD demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	create_handler(IP, &demo);
	//机器人上电
	power_on(&demo );
	//机器人上使能
	enable_robot(&demo);
	//获取力控柔顺控制参数
	ret = get_admit_ctrl_config(&demo, &adm_ctr_cfg);
	return 0;
}

//4.103~104 设置与获取力控传感器通信参数
int example_torque_sensor_comm()
{
	char ip_set[20] = "192.168.2.14";
	int ret, type_set = 0, port_set = 10000;
	char ip_ret[20];
	int type_ret, port_ret;
	//实例API对象demo 
	JKHD demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	create_handler(IP, &demo);
	//机器人上电f
	power_on(&demo);
	//机器人上使能
	enable_robot(&demo);
	//设置力控通信参数
	ret = set_torque_sensor_comm(&demo, type_set, ip_set, port_set);
	Sleep(1000);
	//获取力控通讯参数
	ret = get_torque_sensor_comm(&demo, &type_ret, ip_ret, &port_ret);
	return 0;
}

//4.105 关闭力矩控制
int example_disable_force_control()
{
	int ret;
	//实例API对象demo 
	JKHD demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	create_handler(IP, &demo);
	//机器人上电f
	power_on(&demo);
	//机器人上使能
	enable_robot(&demo);
	//设置控柔顺控制参数
	ret = disable_force_control(&demo);
	return 0;
}

//4.106 设置速度柔顺控制参数
int example_set_vel_comliant_ctrl()
{
	VelCom vel_cfg;
	vel_cfg.vc_level = 1;
	vel_cfg.rate1 = 0.9; vel_cfg.rate2 = 0.6;
	vel_cfg.rate3 = 0; vel_cfg.rate4 = 0;
	int ret;
	//实例API对象demo 
	JKHD demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	create_handler(IP, &demo);
	//机器人上电
	power_on(&demo);
	//机器人上使能
	enable_robot(&demo);
	//设置速度柔顺控制参数
	ret = set_vel_compliant_ctrl(&demo, &vel_cfg);
	return 0;
}

//4.107 设置柔顺力矩条件
int example_set_compliance_condition()
{
	FTxyz ft;
	ft.fx = 10; ft.fy = 10; ft.fz = 10;
	ft.tx = 10; ft.ty = 10; ft.tz = 10;
	int ret;
	//实例API对象demo 
	JKHD demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	create_handler(IP, &demo);
	//机器人上电
	power_on(&demo);
	//机器人上使能
	enable_robot(&demo);
	//设置柔顺力矩条件
	ret = set_compliance_condition(&demo, &ft);
	return 0;
}

//4.108 设置网络异常时机器人自动终止运动类型
int example_set_network_exception_handle()
{
	float milisec = 100;
	int ret;
	//实例API对象demo 
	JKHD demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	create_handler(IP, &demo);
	//机器人上电
	power_on(&demo);
	//机器人上使能
	enable_robot(&demo);
	//设置柔顺力矩条件
	ret = set_network_exception_handle(&demo, milisec, MOT_KEEP);

	return 0;
}

//4.109 设置状态自动更新时间
int example_set_status_data_updata_interval()
{
	float milisec = 100;
	int ret;
	//实例API对象demo 
	JKHD demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	create_handler(IP, &demo);
	//机器人上电
	power_on(&demo);
	//机器人上使能
	enable_robot(&demo);
	//设置柔顺力矩条件
	ret = set_status_data_update_time_interval(&demo, milisec);

	return 0;
}

int example_get_ftp_dir()
{
	int ret;
	//实例API对象demo 
	JKHD demo;
	char result[2000] = "\0";
	char dir[20] = "/program/";
	//登陆控制器，需要将192.168.2.229替换为自己控制器的IP
	create_handler("192.168.2.26", &demo);
	init_ftp_client(&demo);
	get_ftp_dir(&demo, dir, 0, result);
	printf("%s\n", result);
	close_ftp_client(&demo);
	return 0;
}

int example_upload_dir()
{
	int ret;
	//实例API对象demo 
	JKHD demo;
	char result[2000] = "\0";
	char remote[64] = "/lxxpro/";
	char local[100] = "C:\\Users\\Administrator\\Desktop\\program\\track\\";
	//登陆控制器，需要将192.168.2.229替换为自己控制器的IP
	create_handler("192.168.2.26", &demo);
	init_ftp_client(&demo);
	upload_file(&demo, local, remote, 2);
	printf("%s\n", result);
	close_ftp_client(&demo);
	return 0;
}

int example_rename_dir()
{
	int ret;
	//实例API对象demo 
	JKHD demo;
	char result[2000] = "\0";
	char remote[20] = "/lxxpro/";
	char des[20] = "lxx";
	//登陆控制器，需要将192.168.2.229替换为自己控制器的IP
	create_handler("192.168.2.26", &demo);
	init_ftp_client(&demo);
	rename_ftp_file(&demo, remote, des, 2);
	printf("%s\n", result);
	close_ftp_client(&demo);
	return 0;
}

int main()
{
	int ret;
	//实例API对象demo 
	JKHD demo;
	char result[2000] = "\0";
	char remote[20] = "/lxxpro/";
	char des[20] = "lxx";
	while (1) {
		//登陆控制器，需要将192.168.2.229替换为自己控制器的IP
		create_handler("172.30.1.205", &demo);
		Sleep(2);
	}

	//init_ftp_client(&demo);
	//rename_ftp_file(&demo, remote, des, 2);
	//printf("%s\n", result);
	//close_ftp_client(&demo);
	//return 0;
}
