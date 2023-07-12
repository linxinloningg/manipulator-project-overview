#include <iostream>
#include "JAKAZuRobot.h"
#include "jktypes.h"
#include "jkerr.h"
#include <windows.h>
#include <string.h>
#include <stdio.h>
#include <thread>
#include <time.h>
#define PI 3.1415926
//4.1~4.9机器人手动运动
std::string ipaddr = "172.30.1.205";
void checklogin(int ret)
{
	if (ret == 0)
	{
		printf("\nlogin robot:%s success\n", ipaddr.c_str());
	}
	else
	{
		printf("\nlogin failed ,please check ip addr\n");
	}
}

int example_jog()
{
	int ret = 1;
	//实例API对象demo 
	JAKAZuRobot demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	ret = demo.login_in(ipaddr.c_str());
	checklogin(ret);
	//机器人上电
	ret = demo.power_on();
	//机器人上使能
	ret = demo.enable_robot();
	//关节空间运动，其中INCR代表增量运动，0.5代表速度为0.5rad/s ,30*PI/180代表执行该行命令运动30*PI/180rad，
	demo.jog(0, ABS, COORD_JOINT, -0.5, 30*PI/180);
	Sleep(1000);
	demo.jog_stop(0);
	printf("\ndisable robot\n");
	//机器人去使能
	demo.disable_robot();
	printf("\npower_off\n");
	//机器人下电
	demo.power_off();
	return 0;
}

//4.11机器人关节运动 ，关节速度上限180deg/s
int example_joint_move()
{
	int ret = 1;
	//实例API对象demo 
	JAKAZuRobot demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	ret = demo.login_in(ipaddr.c_str());
	checklogin(ret);
	//机器人上电
	demo.power_on();
	//机器人上使能
	demo.enable_robot();
	printf("start move");
	//定义并初始化关JointValue变量
	JointValue joint_pos = { 45 * PI / 180, 50 * PI / 180, 50 * PI / 180, 0 * PI / 180, 45 * PI / 180, 0 * PI / 180 };
	//关节空间运动，其中ABS代表绝对运动，TRUE代表指令是阻塞的，0.1代表速度为1rad/s  
	demo.joint_move(&joint_pos, ABS, TRUE, 0.1);
	return 0;
}

//4.12机器人末端直线运动,注意避免奇异点
int example_linear_move()
{
	int ret;
	//实例API对象demo 
	JAKAZuRobot demo;
	RobotStatus robstatus;
	//登陆控制器，需要将192.168.2.229替换为自己控制器的IP
	ret = demo.login_in(ipaddr.c_str());\
	checklogin(ret);
	//机器人上电
	demo.power_on();
	//机器人上使能
	demo.enable_robot();
	//定义并初始化CartesianPose变量，旋转角为弧度。
	CartesianPose cart;
	cart.tran.x = 0; cart.tran.y = 0; cart.tran.z = -10;
	cart.rpy.rx = 0 * PI / 180; cart.rpy.ry = 0 * PI / 180; cart.rpy.rz = 0 * PI / 180;
	//demo.set_tool_id(2);
	//笛卡尔空间运动，其中ABS代表绝对运动，FALSE代表指令是非阻塞的，10代表速度为10mm/s   
	ret = demo.linear_move(&cart, INCR, true, 200, 10 ,1,NULL);
	printf("ret=%d", ret);
	demo.login_out();
	return 0;
}

//4.13~14机器人伺服关节运动
//使用该接口时需要先调用servo_move_enable(TRUE)开启伺服控制
//关节速度上限180deg/s
//本指令与joint_move有较大差别，joint_move的插补由控制器进行，servo_j需要预先进行轨迹规划。
int example_servo_j()
{
	int ret;
	//实例API对象demo 
	JAKAZuRobot demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	ret = demo.login_in(ipaddr.c_str());
	checklogin(ret);
	//机器人上电
	demo.power_on();
	//机器人上使能
	demo.enable_robot();
	//TRUE为进入伺服模式
	demo.servo_move_enable(TRUE);
	//定义并初始化关JointValue变量
	JointValue joint_pos = {  -0.01, 0* PI / 180, 0* PI / 180, 0* PI / 180, 0* PI / 180, -0.001 };
	JointValue joint_pos2 = { 0.01, 0 * PI / 180, 0 * PI / 180, 0 * PI / 180, 0 * PI / 180, 0.001 };
	int n = 0;
	while (n<10) {
		for (int i = 0; i < 100; i++)
		{
			//关节空间伺服运动，其中INCR代表增量运动
			demo.servo_j(&joint_pos, INCR);
		}
		for (int i = 0; i < 100; i++)
		{
			//关节空间伺服运动，其中INCR代表增量运动
			demo.servo_j(&joint_pos2, INCR);
		}
		n++;
	}
	
	//FALSE为退出伺服模式
	demo.servo_move_enable(FALSE);
	return 0;
}

//4.16机器人伺服笛卡尔空间运动
//使用该接口时需要先调用servo_move_enable(TRUE)开启伺服控制
//关节速度上限180deg/s，笛卡尔空间没有相对直观的限制，但应满足该关节速度限制
//本指令与linear_move有较大差别，linear_move的插补由控制器进行，servo_p需要预先进行轨迹规划。
int example_servo_p()//机器人伺服笛卡尔空间运动
{
	int ret;
	//实例API对象demo 
	JAKAZuRobot demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	ret = demo.login_in(ipaddr.c_str());
	checklogin(ret);
	//机器人上电
	demo.power_on();
	//机器人上使能
	demo.enable_robot();
	JointValue joint_pos = { -50*PI/180, 60 * PI / 180, -85 * PI / 180, 80 * PI / 180, 90 * PI / 180, 0 };
	demo.joint_move(&joint_pos, ABS, TRUE, 1);
	//TRUE为进入伺服模式
	demo.servo_move_use_none_filter();
	demo.servo_move_enable(TRUE);
	//定义并初始化关CartesianPose变量
	CartesianPose cart;
	cart.tran.x = 0; cart.tran.y = 1; cart.tran.z = 0;
	cart.rpy.rx = 0; cart.rpy.ry = 0; cart.rpy.rz = 0;
	CartesianPose cart2;
	cart2.tran.x = 0; cart2.tran.y = 0; cart2.tran.z = 0;
	cart2.rpy.rx = 0; cart2.rpy.ry = 0; cart2.rpy.rz = 0;
	double dur1;
	clock_t start1, end1;
	for (int i = 0; i < 10; i++)
	{
		start1 = clock();
		demo.servo_p(&cart, INCR);
		end1 = clock();
		Sleep(2);
		dur1 = (double)(end1 - start1);
		//笛卡尔空间伺服运动，其中INCR代表增量运动
		printf("Use Time:%f\n", (dur1 / CLOCKS_PER_SEC));
	}
	//for (int i = 0; i < 100; i++)
	//{
	//	demo.servo_p(&cart2, INCR);
	//	Sleep(2);
	//}
	//FALSE为退出伺服模式
	demo.servo_move_enable(FALSE);
	return 0;
}


//4.18设置与查询数字输出
int example_set_digital_output()
{
	BOOL DO3;
	//实例API对象demo 
	JAKAZuRobot demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	demo.login_in(ipaddr.c_str());
	//机器人上电
	demo.power_on();	
	//查询do3的状态
	demo.get_digital_output(IO_CABINET, 2, &DO3);
	printf("D03 = %d\n", DO3);
	//io_cabinet是控制柜面板IO，2代表DO3，1对应要设置的DO值。
	demo.set_digital_output(IO_CABINET, 2, 1);
	Sleep(1000);//需要window.h延时1s
	//查询do3的状态
	demo.get_digital_output(IO_CABINET, 2, &DO3);
	printf("D03 = %d\n", DO3);	
	return 0;
}
//4.19设置与查询模拟输出
int example_set_analog_output()
{

	//实例API对象demo 
	JAKAZuRobot demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	demo.login_in(ipaddr.c_str());
	//机器人上电
	demo.power_on();
	float AO35;
	//查询Ao的状态
	demo.get_analog_output(IO_CABINET, 34, &AO35);
	printf("A035 = %f\n", AO35);
	//io_cabinet是控制柜面板IO，2代表DO3，1.5对应要设置的DO值。
	demo.set_analog_output(IO_CABINET, 34, 1.5);
	Sleep(1000);//需要window.h延时1s
	//查询Ao的状态
	demo.get_analog_output(IO_CABINET, 34, &AO35);
	printf("A035 = %f\n", AO35);
	return 0;
}

//4.24查询扩展IO状态
int example_is_extio_running()
{
	//实例API对象demo 
	JAKAZuRobot demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	demo.login_in(ipaddr.c_str());
	//机器人上电
	demo.power_on();
	BOOL is_running;
	//查询TIO的状态
	demo.is_extio_running(&is_running);
	printf("tio = %d\n", is_running);	
	return 0;
}

//4.25~4.32脚本加载，运行控制，过程查看
int example_program()
{
	char name[128];
	int cur_line;
	int ret;
	//实例API对象demo 
	JAKAZuRobot demo;
	ProgramState pstatus;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	ret=demo.login_in("192.168.2.214");
	std::cout << "login :" << ret << std::endl;
	//机器人上电
	demo.power_on();
	//机器人上使能
	demo.enable_robot();
	//加载预先通过app编辑的example脚本
	ret=demo.program_load("ftp_test");
	std::cout << "load_ftp_program :" << ret << std::endl;
	//获取已加载的程序名
	demo.get_loaded_program(name);
	std::cout <<"Pro_name is :"<< name << std::endl;
	//运行当前加载的程序
	demo.program_run();
	Sleep(1000);//需要window.h延时1s
	//暂停当前运行的程序
	demo.program_pause();
	//获取当前执行程序的行号
	demo.get_current_line(&cur_line);
	std::cout << "cur_line is :" << cur_line << std::endl;
	//获取当前程序状态
	demo.get_program_state(&pstatus);
	std::cout <<  "pro_status is : " << pstatus << std::endl;
	//继续运行当前程序
	demo.program_resume();
	Sleep(10000);//需要window.h延时10s
	//终止当前程序
	demo.program_abort();
	return 0;
}

//4.33~34机器人速度查看及调整
int example_rapidrate()
{
	double rapid_rate;
	//实例API对象demo 
	JAKAZuRobot demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	demo.login_in("192.168.2.152");
	//机器人上电
	demo.power_on();
	//机器人上使能
	demo.enable_robot();
	demo.get_rapidrate(&rapid_rate);
	std::cout << "rapid_rate is : " << rapid_rate << std::endl;
	demo.set_rapidrate(0.4);
	Sleep(100);
	demo.get_rapidrate(&rapid_rate);
	std::cout << "rapid_rate is : " << rapid_rate << std::endl;
	return 0;
}

//4.35~38工具坐标系查看及调整
int example_tool()
{
	int id_ret,id_set;
	id_set = 2;
	CartesianPose tcp_ret,tcp_set;
	char name[50] = "test";
	//实例API对象demo 
	JAKAZuRobot demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	demo.login_in(ipaddr.c_str());
	//机器人上电
	demo.power_on();
	//查询当前使用的工具ID
	demo.get_tool_id(&id_ret);
	//获取当前使用的工具信息
	demo.get_tool_data(id_ret,&tcp_ret);
	printf("id_using=%d \nx=%f, y=%f, z=%f\n", id_ret, tcp_ret.tran.x, tcp_ret.tran.y, tcp_ret.tran.y);
	printf("rx=%f, ry=%f, rz=%f\n", tcp_ret.rpy.rx, tcp_ret.rpy.ry, tcp_ret.rpy.rz);
	//初始化工具坐标
	tcp_set.tran.x = 0; tcp_set.tran.y = 0; tcp_set.tran.z = 10;
	tcp_set.rpy.rx = 120 * PI / 180; tcp_set.rpy.ry = 90 * PI / 180; tcp_set.rpy.rz = -90 * PI / 180;
	//设置工具信息
	demo.set_tool_data(id_set, &tcp_set, name);
	//切换当前使用的工具坐标
	demo.set_tool_id(id_set);
	Sleep(1000);
	//查询当前使用的工具ID
	demo.get_tool_id(&id_ret);
	//获取设置的工具信息
	demo.get_tool_data(id_ret, &tcp_ret);
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
	JAKAZuRobot demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	demo.login_in(ipaddr.c_str());
	//机器人上电
	demo.power_on();
	//查询当前使用的用户坐标系ID
	demo.get_user_frame_id(&id_ret);
	//获取当前使用的用户坐标系信息
	demo.get_user_frame_data(id_ret, &tcp_ret);
	printf("id_using=%d \nx=%f, y=%f, z=%f\n", id_ret, tcp_ret.tran.x, tcp_ret.tran.y, tcp_ret.tran.y);
	printf("rx=%f, ry=%f, rz=%f\n", tcp_ret.rpy.rx, tcp_ret.rpy.ry, tcp_ret.rpy.rz);
	//初始化用户坐标系坐标
	tcp_set.tran.x = 0; tcp_set.tran.y = 0; tcp_set.tran.z = 10;
	tcp_set.rpy.rx = 120 * PI / 180; tcp_set.rpy.ry = 90 * PI / 180; tcp_set.rpy.rz = -90 * PI / 180;
	//设置用户坐标系信息
	demo.set_user_frame_data(id_set, &tcp_set, name);
	//切换当前使用的用户坐标系坐标
	demo.set_user_frame_id(id_set);
	//查询当前使用的用户坐标系ID
	demo.get_user_frame_id(&id_ret);
	//获取设置的用户坐标系信息
	demo.get_user_frame_data(id_ret, &tcp_ret);
	printf("id_using=%d \nx=%f, y=%f, z=%f\n", id_ret, tcp_ret.tran.x, tcp_ret.tran.y, tcp_ret.tran.y);
	printf("rx=%f, ry=%f, rz=%f\n", tcp_ret.rpy.rx, tcp_ret.rpy.ry, tcp_ret.rpy.rz);
	
	return 0;
}

//4.43~44拖拽模式
int  example_drag()
{
	BOOL in_drag;
	//实例API对象demo 
	JAKAZuRobot demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	demo.login_in("192.168.2.160");
	//机器人上电
	demo.power_on();
	//机器人上使能
	demo.enable_robot();
	//确认机器人是否在拖拽模式下
	demo.is_in_drag_mode(&in_drag);
	std::cout << "in_drag is : " << in_drag << std::endl;
	//使能拖拽模式
	demo.drag_mode_enable(TRUE);
	Sleep(100);
	demo.is_in_drag_mode(&in_drag);
	std::cout << "in_drag is : " << in_drag << std::endl;
	while (1)
	{
		demo.is_in_drag_mode(&in_drag);
		std::cout << "in_drag is : " << in_drag << std::endl;
		Sleep(100);
	}
	//去使能拖拽模式
	demo.drag_mode_enable(FALSE);
	Sleep(100);
	return 0;
}

//4.45获取机器人状态(急停 上电 伺服使能)
int example_get_robstate()
{
	//实例API对象demo 
	JAKAZuRobot demo;
	RobotState state;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	demo.login_in(ipaddr.c_str());
	//机器人上电
	demo.power_on();
	//机器人上使能
	demo.enable_robot();
	demo.get_robot_state(&state);
	std::cout << "is e_stoped : " << state.estoped << std::endl;
	std::cout << "is powered : " << state.poweredOn << std::endl;
	std::cout << "is servoEnabled : " << state.servoEnabled << std::endl;
	return 0;
}

//4.46获取工具末端位姿
int example_get_tcp_position()
{
	//实例API对象demo 
	JAKAZuRobot demo;
	CartesianPose tcp_pos;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	demo.login_in(ipaddr.c_str());
	//机器人上电
	demo.power_on();
	//机器人上使能
	demo.enable_robot();
	//获取工具末端位姿
	demo.get_tcp_position(&tcp_pos);
	std::cout << "tcp_pos is :\n x: " << tcp_pos.tran.x << "  y: " << tcp_pos.tran.y << "  z: " << tcp_pos.tran.z << std::endl;
	std::cout << "rx: " << tcp_pos.rpy.rx << "  ry: " << tcp_pos.rpy.ry << "  rz: " << tcp_pos.rpy.rz << std::endl;
	return 0;
}

//4.47获取当前机器人关节角
int example_get_joint_position()
{
	//实例API对象demo 
	JAKAZuRobot demo;
	JointValue jot_pos;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	demo.login_in(ipaddr.c_str());
	//机器人上电
	demo.power_on();
	//机器人上使能
	demo.enable_robot();
	//获取当前关节角
	demo.get_joint_position(&jot_pos);
	for (int i = 0; i < 6; i++)
	{
		std::cout << "joint [" << i+1 <<"] is :"<< jot_pos.jVal[i] << std::endl;
	}
	return 0;
}

//4.49查询是否超出限位
int example_is_on_limit()
{
	//实例API对象demo 
	JAKAZuRobot demo;
	BOOL on_limit;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	demo.login_in("192.168.2.152");
	//机器人上电
	demo.power_on();
	//机器人上使能
	demo.enable_robot();
	while (1)
	{
		//查询是否超限
		demo.is_on_limit(&on_limit);
		std::cout << " on_limit is :" << on_limit << std::endl;
		Sleep(200);
	}
	return 0;
}

//4.50查询机器人运动是否停止
int example_is_in_pos()
{
	//实例API对象demo 
	JAKAZuRobot demo;
	BOOL in_pos;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	demo.login_in("192.168.2.22");
	//机器人上电
	demo.power_on();
	//机器人上使能
	demo.enable_robot();
	while (1)
	{
		//查询是否运动停止
		demo.is_in_pos(&in_pos);
		std::cout << " in_pos is :" << in_pos << std::endl;
		Sleep(200);
	}
	return 0;
}

//4.48 4.51碰撞保护状态查看，恢复
int example_collision_recover()
{
	//实例API对象demo 
	JAKAZuRobot demo;
	BOOL in_collision;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	demo.login_in("192.168.2.152");
	//机器人上电
	demo.power_on();
	//机器人上使能
	demo.enable_robot();
	//查询是否处于运动保护状态
	demo.is_in_collision(&in_collision);
	std::cout << " in_collision is :" << in_collision << std::endl;
	if (in_collision)
		//如果处于碰撞保护模式，则从碰撞保护中恢复
		{demo.collision_recover();}
	else
		{std::cout << "demo is not collision" << std::endl;}
	return 0;
}

//4.52~53碰撞等级查看，设置
int example_collision_level()
{
	//实例API对象demo 
	JAKAZuRobot demo;
	int level;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	demo.login_in("192.168.2.152");
	//机器人上电
	demo.power_on();
	//机器人上使能
	demo.enable_robot();
	//查询当前碰撞等级
	demo.get_collision_level(&level);
	std::cout << " collision level is :" << level << std::endl;
	//设置碰撞等级，[0,5]，0为关闭碰撞，1为碰撞阈值25N，2为碰撞阈值50N，3为碰撞阈值75N，4为碰撞阈值100N，5为碰撞阈值125N，
	demo.set_collision_level(2);
	//查询当前碰撞等级
	demo.get_collision_level(&level);
	std::cout << " collision level is :" << level << std::endl;
	return 0;
}

// 4.54机器人逆解 已知tcp_pos,求joint_pos
int example_kine_inverse()
{
	int ret;
	//实例API对象demo 
	JAKAZuRobot demo;
	//初始化参考点
	JointValue ref_jpos = { 0.558, 0.872, 0.872 , 0.349, 0.191, 0.191 };
	//初始化笛卡尔空间点坐标
	CartesianPose tcp_pos;
	tcp_pos.tran.x = 243.568; tcp_pos.tran.y = 164.064; tcp_pos.tran.z = 742.002;
	tcp_pos.rpy.rx = -1.81826; tcp_pos.rpy.ry = -0.834253;  tcp_pos.rpy.rz = -2.30243;
	//初始化返回值
	JointValue joint_pos = { 0,0,0,0,0,0 }; ;

	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	demo.login_in(ipaddr.c_str());
	ret = demo.kine_inverse(&ref_jpos, &tcp_pos, &joint_pos);
	std::cout << ret << std::endl;
	for (int i = 0; i < 6; i++)
	{
		std::cout << "joint [" << i + 1 << "] is :" << joint_pos.jVal[i] << std::endl;
	}
	return 0;
}

// 4.55机器人正解 已知joint_pos,求tcp_pos
int example_kine_forward()
{
	int ret;
	//实例API对象demo 
	JAKAZuRobot demo;
	//初始化笛卡尔空间点坐标
	CartesianPose tcp_pos;
	//初始化返回值
	JointValue joint_pos = { 0.558, 0.872, 0.872 , 0.349, 0.191, 0.191 };

	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	demo.login_in(ipaddr.c_str());
	ret = demo.kine_forward(&joint_pos, &tcp_pos);
	std::cout << ret << std::endl;
	std::cout << "tcp_pos is :\n x: " << tcp_pos.tran.x << "  y: " << tcp_pos.tran.y << "  z: " << tcp_pos.tran.z << std::endl;
	std::cout << "rx: " << tcp_pos.rpy.rx << "  ry: " << tcp_pos.rpy.ry << "  rz: " << tcp_pos.rpy.rz << std::endl;
	return 0;
}

// 4.56欧拉角到旋转矩阵
int example_rpy_to_rot_matrix()
{
	int ret;
	//实例API对象demo 
	JAKAZuRobot demo;
	//初始化欧拉角
	Rpy rpy;
	rpy.rx = -1.81826; rpy.ry = -0.834253;  rpy.rz = -2.30243;
	//初始化旋转矩阵
	RotMatrix rot_matrix;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	demo.login_in(ipaddr.c_str());
	ret = demo.rpy_to_rot_matrix(&rpy, &rot_matrix);
	std::cout << ret << "     eul2rotm" << std::endl;
	printf("%f %f %f\n", rot_matrix.z.x, rot_matrix.y.x, rot_matrix.x.x);
	printf("%f %f %f\n", rot_matrix.z.y, rot_matrix.y.y, rot_matrix.x.y);
	printf("%f %f %f\n", rot_matrix.z.z, rot_matrix.y.z, rot_matrix.x.z);
	return 0;
}

// 4.57旋转矩阵--->欧拉角
int example_rot_matrix_to_rpy()
{
	int ret;
	//实例API对象demo 
	JAKAZuRobot demo;
	//初始化欧拉角
	Rpy rpy;
	//初始化旋转矩阵
	RotMatrix rot_matrix;
	rot_matrix.x.x = -0.4488, rot_matrix.y.x = -0.4998, rot_matrix.z.x = 0.7408;
	rot_matrix.x.y = -0.6621, rot_matrix.y.y = -0.3708, rot_matrix.z.y = -0.6513;
	rot_matrix.x.z = 0.6002, rot_matrix.y.z = -0.7828, rot_matrix.z.z = -0.1645;
	//rot_matrix.z.x = 0, rot_matrix.y.x = 1, rot_matrix.x.x = 0;
	//rot_matrix.z.y = 0, rot_matrix.y.y = 0, rot_matrix.x.y = 1;
	//rot_matrix.z.z = -1, rot_matrix.y.z = 0, rot_matrix.x.z = 0;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	demo.login_in(ipaddr.c_str());
	ret = demo.rot_matrix_to_rpy(&rot_matrix, &rpy);
	std::cout << ret << "     rotm2eul:" << std::endl;
	printf("%f %f %f \n", rpy.rx, rpy.ry, rpy.rz);
	return 0;
}

// 4.58四元数-->旋转矩阵
int example_quaternion_to_rot_matrix()
{
	int ret;
	//实例API对象demo 
	JAKAZuRobot demo;
	//初始化四元数
	Quaternion quat;
	quat.s = 0.0629;  quat.x = 0.522886; quat.y = -0.5592;  quat.z = 0.6453;
	//quat.s = 0.707;  quat.x = 0; quat.y = 0.707107;  quat.z = 0;
	//初始化旋转矩阵
	RotMatrix rot_matrix;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	demo.login_in(ipaddr.c_str());
	ret = demo.quaternion_to_rot_matrix(&quat, &rot_matrix);
	std::cout << ret << "     quatl2rotm:" << std::endl;
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
	JAKAZuRobot demo;
	//初始化四元数
	Quaternion quat;
	//初始化旋转矩阵
	RotMatrix rot_matrix;
	rot_matrix.x.x = -0.4488774, rot_matrix.y.x = -0.499824, rot_matrix.z.x = 0.740795;
	rot_matrix.x.y = -0.662098, rot_matrix.y.y = -0.370777, rot_matrix.z.y = -0.651268;
	rot_matrix.x.z = 0.600190, rot_matrix.y.z = -0.782751, rot_matrix.z.z = -0.164538;
	//rot_matrix.x.x = 0, rot_matrix.y.x = 0, rot_matrix.z.x = -1;
	//rot_matrix.x.y = 0, rot_matrix.y.y = 1, rot_matrix.z.y = 0;
	//rot_matrix.x.z = 1, rot_matrix.y.z = 0, rot_matrix.z.z = 0;

	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	demo.login_in(ipaddr.c_str());
	ret = demo.rot_matrix_to_quaternion(&rot_matrix, &quat);
	std::cout << ret << "    rotm2quat:" << std::endl;
	printf("%lf %lf %lf %lf \n", quat.s, quat.x, quat.y, quat.z);
	return 0;
}

// 4.60 注册机器人出错函数
//错误处理
void user_error_handle(int error_code)
{
	std::cout << error_code << std::endl;
}
//注册
int example_set_err_handle()
{
	//实例API对象demo 
	JAKAZuRobot demo;
	//登陆控制器，需要将192.168.2.229替换为自己控制器的IP
	demo.login_in("192.168.2.160");
	//机器人上电
	demo.power_on();
	//机器人上使能
	demo.enable_robot();
	//设置用户异常回调函数
	demo.set_error_handler(user_error_handle);

	return 0;
}

//4.61~4.62负载查看及设置
int example_payload()
{
	//实例API对象demo 
	JAKAZuRobot demo;
	PayLoad payloadret;
	PayLoad payload_set;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	demo.login_in(ipaddr.c_str());
	//查询当前负载数据
	demo.get_payload(&payloadret);
	std::cout << " payload mass is :" << payloadret.mass << " kg" << std::endl;
	std::cout << " payload center of mass is \nx: " << payloadret.centroid.x<< "y: " << payloadret.centroid.y << "z: " << payloadret.centroid.z << std::endl;
	payload_set.mass = 1.0;
	//单位mm
	payload_set.centroid.x = 0; payload_set.centroid.y = 0; payload_set.centroid.z = 10;
	//设置当前负载数据
	demo.set_payload(&payload_set);
	//查询当前负载数据
	demo.get_payload(&payloadret);
	std::cout << " payload mass is :" << payloadret.mass << " kg" << std::endl;
	std::cout << " payload center of mass is \nx: " << payloadret.centroid.x << "y: " << payloadret.centroid.y << "z: " << payloadret.centroid.z << std::endl;
	return 0;
}

//4.63获取sdk版本号
int example_getsdk_version()
{
	//实例API对象demo 
	JAKAZuRobot demo;
	char ver[100];
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	demo.login_in(ipaddr.c_str());
	//查询当前SDK版本
	demo.get_sdk_version(ver);
	std::cout << " SDK version is :" << ver << std::endl;

	return 0;
}

//4.64获取控制器ip,启动app时，该函数失效。
int example_get_controller_ip()
{
	int ret;
	//实例API对象demo 
	JAKAZuRobot demo;
	char ip_list[2000] = {};
	char  controller_name1[50] = "";
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	demo.login_in(ipaddr.c_str());
	//获取控制器ip
	ret = demo.get_controller_ip( controller_name1, ip_list);
	std::cout << ret << std::endl;
	std::cout << " ip_list is :\n" << ip_list << std::endl;
	return 0;
}

//4.65获取机器人状态监测数据
int example_get_robot_status()
{
	//实例API对象demo 
	JAKAZuRobot demo;
	RobotStatus robstatus;
	int ret;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	ret = demo.login_in("192.168.2.149");
	std::cout << " ret :" << ret << std::endl;
	//机器人上电
	demo.power_on();
	//机器人上使能
	demo.enable_robot();
	//获取机器人状态监测数据
	while (1)
	{
		demo.get_robot_status(&robstatus);
		std::cout << " is_socket_connect is :" << robstatus.is_socket_connect << std::endl;
		Sleep(1000);
	}
	demo.get_robot_status(&robstatus);
	std::cout << " errcode is :" << robstatus.errcode << std::endl;
	std::cout << " inpos is :" << robstatus.inpos << std::endl;
	std::cout << " powered_on is :" << robstatus.powered_on << std::endl;
	std::cout << " enabled is :" << robstatus.errcode << std::endl;
	std::cout << " rapidrate is :" << robstatus.rapidrate << std::endl;
	std::cout << " protective_stop is :" << robstatus.protective_stop << std::endl;
	std::cout << " emergency_stop is :" << robstatus.emergency_stop << std::endl;
	std::cout << " rapidrate is :" << robstatus.rapidrate << std::endl;
	std::cout << " dout is : {";
	for (int i = 1; i < (sizeof(robstatus.dout) / sizeof(robstatus.dout[0])); i++)
	{
		std::cout << robstatus.dout[i] << ",";
		if (0 == i % 20)
			std::cout << std::endl;
	}
	std::cout << robstatus.dout[sizeof(robstatus.dout) / sizeof(robstatus.dout[0]) - 1] << "}" << std::endl;
	std::cout << " tio_dout is : {";
	for (int i = 1; i < (sizeof(robstatus.tio_dout) / sizeof(robstatus.tio_dout[0])); i++)
	{
		std::cout << robstatus.tio_dout[i] << ",";
		if (0 == i % 20)
			std::cout << std::endl;
	}
	std::cout << robstatus.tio_dout[sizeof(robstatus.tio_dout) / sizeof(robstatus.tio_dout[0]) - 1] << "}" << std::endl;
	std::cout << " din is : {";
	for (int i = 1; i < (sizeof(robstatus.din) / sizeof(robstatus.din[0])); i++)
	{
		std::cout << robstatus.din[i] << ",";
		if (0 == i % 20)
			std::cout << std::endl;
	}
	std::cout << robstatus.din[sizeof(robstatus.din) / sizeof(robstatus.din[0]) - 1] << "}" << std::endl;
	std::cout << " tio_din is : {";
	for (int i = 1; i < (sizeof(robstatus.tio_din) / sizeof(robstatus.tio_din[0])); i++)
	{
		std::cout << robstatus.tio_din[i] << ",";
		if (0 == i % 20)
			std::cout << std::endl;
	}
	std::cout << robstatus.tio_din[sizeof(robstatus.tio_din) / sizeof(robstatus.tio_din[0]) - 1] << "}" << std::endl;
	std::cout << " ain is :\n {";
	for (int i = 1; i < (sizeof(robstatus.ain) / sizeof(robstatus.ain[0])); i++)
	{
		std::cout << robstatus.ain[i] << ",";
		if (0 == i % 20)
			std::cout << std::endl;
	}
	std::cout << robstatus.ain[sizeof(robstatus.ain) / sizeof(robstatus.ain[0]) - 1] << "}" << std::endl;
	std::cout << " tio_ain is\n : {";
	for (int i = 1; i < (sizeof(robstatus.tio_ain) / sizeof(robstatus.tio_ain[0])) ; i++)
	{
		std::cout << robstatus.tio_ain[i] << ",";
		if (0 == i % 20)
			std::cout << std::endl;
	}
	std::cout << robstatus.tio_ain[sizeof(robstatus.tio_ain) / sizeof(robstatus.tio_ain[0]) - 1] << "}" << std::endl;
	std::cout << " aout is : \n{";
	for (int i = 1; i < (sizeof(robstatus.aout) / sizeof(robstatus.aout[0])) ; i++)
	{
		std::cout << robstatus.aout[i] << ",";
		if (0 == i % 20)
			std::cout << std::endl;
	}
	std::cout << robstatus.aout[sizeof(robstatus.aout) / sizeof(robstatus.aout[0]) - 1] << "}" << std::endl;
	std::cout << " current_tool_id is :" << robstatus.current_tool_id << std::endl;
	std::cout << "tcp_pos is : x: " << robstatus.cartesiantran_position[0] << "  y: " << robstatus.cartesiantran_position[1] << "  z: " << robstatus.cartesiantran_position[2];
	std::cout << "rx: " << robstatus.cartesiantran_position[3] << "  ry: " << robstatus.cartesiantran_position[4] << "  rz: " << robstatus.cartesiantran_position[5] << std::endl;
	std::cout << " joint_pos is : {";
	for (int i = 0; i < (sizeof(robstatus.joint_position) / sizeof(robstatus.joint_position[0])) - 1; i++)
	{
		std::cout << robstatus.joint_position[i] << ",";
	}
	std::cout << robstatus.joint_position[sizeof(robstatus.joint_position) / sizeof(robstatus.joint_position[0]) - 1] << "}" << std::endl;
	std::cout << " on_soft_limit is :" << robstatus.on_soft_limit << std::endl;
	std::cout << " current_user_coordinate_id is :" << robstatus.current_user_id << std::endl;
	std::cout << " drag_status is :" << robstatus.drag_status << std::endl;
	std::cout << " is_socket_connect is :" << robstatus.is_socket_connect << std::endl;
	demo.disable_robot();
	demo.power_off();
	demo.login_out();
	return 0;
}

//4.66设置SDK是否开启调试模式
int example_set_debug_mode()
{
	//实例API对象demo 
	JAKAZuRobot demo;
	//设置调试模式
	demo.set_debug_mode(TRUE);
	printf("debug :true");
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	demo.login_in(ipaddr.c_str());
	//机器人上电
	demo.power_on();
	//机器人上使能
	demo.enable_robot();

	return 0;
}

//4.67机器人运动终止
int example_motion_abort()
{
	//实例API对象demo 
	JAKAZuRobot demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	demo.login_in(ipaddr.c_str());
	//机器人上电
	demo.power_on();
	//机器人上使能
	demo.enable_robot();
	//定义并初始化关JointValue变量
	printf("start_move");
	JointValue joint_pos = { 0 * PI / 180, 0 * PI / 180, 50 * PI / 180, 0 * PI / 180, 0 * PI / 180, 0 * PI / 180 };
	//关节空间运动，其中ABS代表绝对运动，TRUE代表指令是阻塞的，1代表速度为1rad/s  
	demo.joint_move(&joint_pos, ABS, FALSE, 1);
	Sleep(500);
	//运动0.5s后终止
	demo.motion_abort();
	printf("stop_move");
	return 0;
}

//4.68~4.69错误码查看
int example_get_last_errcode()
{
	int ret;
	char path[100] = "E:\\JAKA_ERROR_CODE.csv";
	//实例API对象demo 
	JAKAZuRobot demo;
	ErrorCode Eret;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	demo.login_in(ipaddr.c_str());
	//机器人上电
	demo.power_on();
	//机器人上使能
	demo.enable_robot();
	ret = demo.program_load("not_exist999875");//故意加载一个不存在的程序，引发报错。
	std::cout << ret ;
	demo.get_last_error(&Eret);//查询最后一个报错信息
	std::cout << " error code is :" << Eret.code << " message: "<< Eret.message<< std::endl;
	ret = demo.set_errorcode_file_path(path);//设置错误码说明文件
	std::cout << ret << std::endl;
	demo.get_last_error(&Eret);//查询最后一个报错信息
	std::cout << " error code is :" << Eret.code << " message: " << Eret.message << std::endl;
	return 0;
	}

//4.70~4.71轨迹复现参数查看及设置
int example_traj_config()
{
	//实例API对象demo 
	JAKAZuRobot demo;
	TrajTrackPara trajpar_read;
	TrajTrackPara trajpar_set;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	demo.login_in(ipaddr.c_str());
	//查询当前轨迹复现参数
	demo.get_traj_config(&trajpar_read);
	std::cout << " trajTrackPara is :\n xyz interval:" << trajpar_read.xyz_interval << "  rpy interval is :" << trajpar_read.rpy_interval << std::endl;
	std::cout << " vel: " << trajpar_read.vel << "  acc: " << trajpar_read.acc << std::endl;

	//设置当前轨迹复现参数
	trajpar_set.xyz_interval = 0.01; trajpar_set.rpy_interval = 0.01; trajpar_set.vel = 10; trajpar_set.acc = 2;	
	demo.set_traj_config(&trajpar_set);

	//查询当前轨迹复现参数
	demo.get_traj_config(&trajpar_read);
	std::cout << " trajTrackPara is :\n xyz interval:" << trajpar_read.xyz_interval << "  rpy interval is :" << trajpar_read.rpy_interval << std::endl;
	std::cout << " vel: " << trajpar_read.vel << "  acc: " << trajpar_read.acc << std::endl;
	return 0;
}

//4.72~4.73轨迹采集开关与状态查询
int example_traj_sample()
{
	BOOL samp_stu;
	//实例API对象demo 
	JAKAZuRobot demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	demo.login_in("192.168.2.160");
	//机器人上电
	demo.power_on();
	//机器人上使能
	demo.enable_robot();
	char name[20] = "testjog";
	//开启轨迹复现数据采集开关
	demo.set_traj_sample_mode(TRUE, name);
	printf("start!\n");
	//查询轨迹复现采集状态
	demo.get_traj_sample_status(&samp_stu);
	Sleep(10000);
	printf("end!\n");
	demo.set_traj_sample_mode(FALSE, name);
	return 0;
}

//4.74查询控制器中已经存在的轨迹复现数据的文件名
int example_get_traj_existed_filename()
{
	//实例API对象demo 
	JAKAZuRobot demo;
	MultStrStorType traj_file;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	demo.login_in("192.168.2.160");

	//查询当前轨迹文件名。
	demo.get_exist_traj_file_name(&traj_file);
	std::cout << "file nums :" << traj_file.len << std::endl;
	for(int i=0; i<traj_file.len;i++)
		std::cout << traj_file.name[i] << std::endl;
	return 0;
}

//4.75重命名轨迹复现的数据文件名
int example_rename_traj_file_name()
{
	//实例API对象demo 
	JAKAZuRobot demo;
	MultStrStorType traj_file;
	char name_new[20] = "555";
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	demo.login_in(ipaddr.c_str());

	//查询当前轨迹文件名。
	demo.get_exist_traj_file_name(&traj_file);
	std::cout << "file nums :" << traj_file.len << std::endl;
	for (int i = 0; i < traj_file.len; i++)
		std::cout << traj_file.name[i] << std::endl;
	//重命名轨迹复现的数据文件名
	demo.rename_traj_file_name(traj_file.name[0], name_new);
	//查询当前轨迹文件名。
	demo.get_exist_traj_file_name(&traj_file);
	std::cout << "file nums :" << traj_file.len << std::endl;
	for (int i = 0; i < traj_file.len; i++)
		std::cout << traj_file.name[i] << std::endl;
	return 0;
}

//4.77 


//4.80机器人圆弧运动 ，关节速度上限180deg/s
int example_circle_move()
{
	OptionalCond opt;
	CartesianPose end_p,mid_p;
	end_p.tran.x = -200; end_p.tran.y = 400; end_p.tran.z = 400;
	end_p.rpy.rx = -90 * PI/ 180; end_p.rpy.ry = 0 * PI / 180; end_p.rpy.rz =0 * PI / 180;
	mid_p.tran.x = -300; mid_p.tran.y = 400; mid_p.tran.z = 500;
	mid_p.rpy.rx = -90 * PI / 180; mid_p.rpy.ry = 0 * PI / 180; mid_p.rpy.rz =0 * PI / 180;
	//实例API对象demo 
	JAKAZuRobot demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	demo.login_in(ipaddr.c_str());
	//机器人上电
	demo.power_on();
	//机器人上使能
	demo.enable_robot();
	//定义并初始化关JointValue变量
	JointValue joint_pos = { 85.76 * PI / 180, -6.207 * PI / 180, 111.269 * PI / 180, 74.938 * PI / 180, 94.24 * PI / 180, 0 * PI / 180 };
	//关节空间运动，其中ABS代表绝对运动，TRUE代表指令是阻塞的，1代表速度为1rad/s  
	demo.joint_move(&joint_pos, ABS, TRUE, 1);
	//圆弧运动，其中ABS代表绝对运动，TRUE代表指令是阻塞的，20代表直线速度为20mm/s，1代表加速度，0.1代表机器人终点误差，opt为可选参数。 
	demo.circular_move(&end_p, &mid_p, ABS, TRUE, 20, 1, 0.1,&opt);
	return 0;
}

//4.81 servo模式禁用滤波器
int example_servo_use_none_filter()
{
	int ret;
	//实例API对象demo 
	JAKAZuRobot demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	demo.login_in(ipaddr.c_str());
	//机器人上电
	demo.power_on();
	//机器人上使能
	demo.enable_robot();
	ret = demo.servo_move_use_none_filter();
	std::cout << ret << std::endl;
	return 0;
}


//4.82 servo模式下关节空间一阶低通滤波
int example_servo_use_joint_LPF()
{
	int ret;
	//实例API对象demo 
	JAKAZuRobot demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	demo.login_in(ipaddr.c_str());
	//机器人上电
	demo.power_on();
	//机器人上使能
	demo.enable_robot();
	//servo模式下关节空间一阶低通滤波,截止频率50Hz
	ret = demo.servo_move_use_joint_LPF(50);
	std::cout << ret << std::endl;
	return 0;
}

//4.85 servo模式下关节空间非线性滤波
int example_servo_use_joint_NLF()
{
	int ret;
	//实例API对象demo 
	JAKAZuRobot demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	demo.login_in(ipaddr.c_str());
	//机器人上电
	demo.power_on();
	//机器人上使能
	demo.enable_robot();
	//servo模式下关节空间非线性滤波
	ret = demo.servo_move_use_joint_NLF(2,2,4);
	std::cout << ret << std::endl;
	return 0;
}

//4.86 servo模式下笛卡尔空间非线性滤波
int example_servo_use_carte_NLF()
{
	int ret;
	//实例API对象demo 
	JAKAZuRobot demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	demo.login_in(ipaddr.c_str());
	//机器人上电
	demo.power_on();
	//机器人上使能
	demo.enable_robot();
	//servo模式下笛卡尔空间非线性滤波
	ret = demo.servo_move_use_carte_NLF(2, 2, 4, 2, 2, 4);
	std::cout << ret << std::endl;
	return 0;
}

//4.87 servo模式下关节空间多阶均值滤波
int example_servo_use_joint_MMF()
{
	int ret;
	//实例API对象demo 
	JAKAZuRobot demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	demo.login_in(ipaddr.c_str());
	//机器人上电
	demo.power_on();
	//机器人上使能
	demo.enable_robot();
	//servo模式下关节空间多阶均值滤波
	ret = demo.servo_move_use_joint_MMF(200, 2, 4, 2);
	std::cout << ret << std::endl;
	return 0;
}

//4.88 servo模式下速度前瞻参数设置
int example_speed_foresight()
{
	int ret;
	//实例API对象demo 
	JAKAZuRobot demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	demo.login_in(ipaddr.c_str());
	//机器人上电
	demo.power_on();
	//机器人上使能
	demo.enable_robot();
	//servo模式下关节空间多阶均值滤波
	ret = demo.servo_speed_foresight(200, 2);
	std::cout << ret << std::endl;
	return 0;
}

//4.89 设置SDK日志路径
int example_set_SDK_filepath()
{
	char path[20] = "E://";
	int ret;
	//实例API对象demo 
	JAKAZuRobot demo;
	ret = demo.set_SDK_filepath(path);//设置SDK文件路径
	std::cout << ret << std::endl;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	demo.login_in(ipaddr.c_str());
	//机器人上电
	demo.power_on();
	//机器人上使能
	demo.enable_robot();
	
	return 0;
}

//4.90 设置传感器品牌
int example_set_torsensor_brand()
{
	int ret;
	//实例API对象demo 
	JAKAZuRobot demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	demo.login_in(ipaddr.c_str());
	//机器人上电
	demo.power_on();
	//机器人上使能
	demo.enable_robot();
	//设置传感器品牌
	ret = demo.set_torsenosr_brand(1);
	std::cout << ret << std::endl;
	return 0;
}

//4.91 获取传感器品牌
int example_get_torsensor_brand()
{
	int ret,cur_sensor;
	//实例API对象demo 
	JAKAZuRobot demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	demo.login_in(ipaddr.c_str());
	//机器人上电
	demo.power_on();
	//机器人上使能
	demo.enable_robot();
	//获取传感器品牌
	ret = demo.get_torsenosr_brand(&cur_sensor);
	std::cout << ret << std::endl;
	return 0;
}

//4.92 开启或关闭力矩传感器
int example_set_torque_sensor_mode()
{
	int ret;
	//实例API对象demo 
	JAKAZuRobot demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	demo.login_in(ipaddr.c_str());
	//机器人上电
	demo.power_on();
	//机器人上使能
	demo.enable_robot();
	//设置力矩传感器状态，1打开，0关闭
	ret = demo.set_torque_sensor_mode(1);
	std::cout << ret << std::endl;
	return 0;
}

//4.93 设置柔顺控制参数
int example_set_admit_ctrl_config()
{
	int ret;
	//实例API对象demo 
	JAKAZuRobot demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	demo.login_in(ipaddr.c_str());
	//机器人上电
	demo.power_on();
	//机器人上使能
	demo.enable_robot();
	//设置柔顺控制参数
	ret = demo.set_admit_ctrl_config(1,1,50,30,0,0);
	std::cout << ret << std::endl;
	return 0;
}

//4.94~4.98 辨识工具末端负载和获取负载辨识状态，设置与获取传感器末端负载
int example_sensor_payload()
{
	JointValue joint_pos;
	PayLoad pl,pl_ret;
	int ret;
	//实例API对象demo 
	JAKAZuRobot demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	demo.login_in(ipaddr.c_str());
	//机器人上电
	demo.power_on();
	//机器人上使能
	demo.enable_robot();
	//开始辨识传感器负载
	ret = demo.start_torq_sensor_payload_identify(&joint_pos);
	do
	{
		//查询传感器负载状态
		demo.get_torq_sensor_identify_staus(&ret);
		std::cout << ret << std::endl;
	} while (1 == ret);
	//获取辨识结果
	ret = demo.get_torq_sensor_payload_identify_result(&pl);
	std::cout << ret << std::endl;
	//设置传感器末端负载
	ret = demo.set_torq_sensor_tool_payload(&pl);
	//获取当前设置的传感器末端负载
	ret = demo.get_torq_sensor_tool_payload(&pl_ret);
	return 0;
}

//4.99 力控拖拽使能
int example_enable_admittance_ctrl()
{
	int ret;
	//实例API对象demo 
	JAKAZuRobot demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	demo.login_in(ipaddr.c_str());
	//机器人上电
	demo.power_on();
	//机器人上使能
	demo.enable_robot();
	demo.set_torsenosr_brand(2);
	demo.set_torque_sensor_mode(1);
	demo.set_compliant_type(1, 1);
	printf("inint sensor comple");
	printf("ready to run");
	//设置柔顺控制参数
	ret = demo.set_admit_ctrl_config(0, 0, 20, 5, 0, 0);
	ret = demo.set_admit_ctrl_config(1, 0, 20, 5, 0, 0);
	ret = demo.set_admit_ctrl_config(2, 99, 20, 10, 0, 0);
	ret = demo.set_admit_ctrl_config(3, 0, 20, 5, 0, 0);
	ret = demo.set_admit_ctrl_config(4, 0, 20, 5, 0, 0);
	ret = demo.set_admit_ctrl_config(5, 0, 20, 5, 0, 0);
	//#设置力控拖拽使能，1打开，0关闭
	ret = demo.enable_admittance_ctrl(1);

	//设置力控拖拽使能，1打开，0关闭
	ret = demo.enable_admittance_ctrl(0);
	ret = demo.set_admit_ctrl_config(2, 0, 20, 5, 0, 0);
	demo.set_torque_sensor_mode(0);
	std::cout << ret << std::endl;
	demo.login_out();
	return 0;
}

//4.100~101 设置与获取力控类型和传感器初始化状态
int example_set_compliant_type()
{
	int ret,sensor_compensation,compliance_type;
	//实例API对象demo 
	JAKAZuRobot demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	demo.login_in(ipaddr.c_str());
	//机器人上电
	demo.power_on();
	//机器人上使能
	demo.enable_robot();
	//设置力控类型和传感器初始化状态
	ret = demo.set_compliant_type(1,1);
	std::cout << ret << std::endl;
	ret = demo.get_compliant_type(&sensor_compensation, &compliance_type);
	std::cout << ret << std::endl;
	return 0;
}

//4.102 获取力控柔顺控制参数
int example_get_admit_ctrl_config()
{
	RobotAdmitCtrl adm_ctr_cfg;
	int ret;
	//实例API对象demo 
	JAKAZuRobot demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	demo.login_in(ipaddr.c_str());
	//机器人上电
	demo.power_on();
	//机器人上使能
	demo.enable_robot();
	//获取力控柔顺控制参数
	ret = demo.get_admit_ctrl_config(&adm_ctr_cfg);
	std::cout << ret << std::endl;
	return 0;
}

//4.103~104 设置与获取力控传感器通信参数
int example_torque_sensor_comm()
{
	char ip_set[20]="192.168.2.14";
	int ret,type_set=0,port_set=10000;
	char ip_ret[20];
	int type_ret, port_ret;
	//实例API对象demo 
	JAKAZuRobot demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	demo.login_in(ipaddr.c_str());
	//机器人上电f
	demo.power_on();
	//机器人上使能
	demo.enable_robot();
	//设置力控通信参数
	ret = demo.set_torque_sensor_comm(type_set, ip_set, port_set);
	std::cout << ret << std::endl;
	//获取力控通讯参数
	ret = demo.get_torque_sensor_comm(&type_ret, ip_ret, &port_ret);
	std::cout << ret << std::endl;
	return 0;
}

//4.105 关闭力矩控制
int example_disable_force_control()
{
	int ret;
	//实例API对象demo 
	JAKAZuRobot demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	demo.login_in(ipaddr.c_str());
	//机器人上电f
	demo.power_on();
	//机器人上使能
	demo.enable_robot();
	//设置控柔顺控制参数
	ret = demo.disable_force_control();
	std::cout << ret << std::endl;
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
	JAKAZuRobot demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	demo.login_in(ipaddr.c_str());
	//机器人上电
	demo.power_on();
	//机器人上使能
	demo.enable_robot();
	//设置速度柔顺控制参数
	ret = demo.set_vel_compliant_ctrl(&vel_cfg);
	std::cout << ret << std::endl;
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
	JAKAZuRobot demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	demo.login_in(ipaddr.c_str());
	//机器人上电
	demo.power_on();
	//机器人上使能
	demo.enable_robot();
	//设置柔顺力矩条件
	ret = demo.set_compliance_condition(&ft);
	std::cout << ret << std::endl;
	return 0;
}

//4.108 设置网络异常时机器人自动终止运动类型
int example_set_network_exception_handle()
{
	float milisec = 100;
	int ret;
	//实例API对象demo 
	JAKAZuRobot demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	demo.login_in(ipaddr.c_str());
	//机器人上电
	demo.power_on();
	//机器人上使能
	demo.enable_robot();
	//设置自动终止类型
	ret = demo.set_network_exception_handle(milisec, MOT_ABORT);
	std::cout << ret << std::endl;
	return 0;
}

//4.109 设置状态自动更新时间 （10004端口)
int example_set_status_data_updata_interval()
{
	float milisec = 100;
	int ret;
	//实例API对象demo 
	JAKAZuRobot demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	demo.login_in(ipaddr.c_str());
	//机器人上电
	demo.power_on();
	//机器人上使能
	demo.enable_robot();
	//设置状态自动更新时间
	ret = demo.set_status_data_update_time_interval(milisec);
	//定义并初始化关JointValue变量
	JointValue joint_pos1 = { 1,1,1,1,1,1 };
	JointValue joint_pos2 = {-1,1,1,1,1,1 };
	
	std::cout << ret << std::endl;
	ret = 0;
	while (1)
	{
		//关节空间运动，其中ABS代表绝对运动，TRUE代表指令是阻塞的，1代表速度为1rad/s  
		demo.joint_move(&joint_pos1, ABS, FALSE, 1);
		demo.joint_move(&joint_pos2, ABS, FALSE, 1);
		Sleep(500);
		ret++;
		std::cout << ret << std::endl;
	}
	return 0;
}

int test_linear_move()
{
	int ret;
	//实例API对象demo 
	JAKAZuRobot demo;
	//登陆控制器，需要将192.168.2.229替换为自己控制器的IP
	demo.login_in(ipaddr.c_str());
	//机器人上电
	ret = demo.power_on();
	std::cout <<"power on :"<< ret << std::endl;
	//机器人上使能
	ret = demo.enable_robot();
	std::cout << "enable :" << ret << std::endl;
	//定义并初始化关CartesianPose变量
	CartesianPose cart;
	cart.tran.x = -200; cart.tran.y = -100; cart.tran.z = 400;
	cart.rpy.rx = 0; cart.rpy.ry = 0; cart.rpy.rz = 0;
	printf("rx=%f , ry=%f, rz=%f\n", cart.rpy.rx, cart.rpy.ry, cart.rpy.rz);
	ret = demo.linear_move(&cart, ABS, true, 10, 200, 0, NULL);
	std::cout <<"linear_move1 :"<< ret << std::endl;
	ret = demo.linear_move(&cart, ABS, true, 10, 200, 0, NULL);
	std::cout << "linear_move2 :" << ret << std::endl;
	cart.tran.z = 700;
	printf("rx=%f , ry=%f, rz=%f\n", cart.rpy.rx, cart.rpy.ry, cart.rpy.rz);
	ret = demo.linear_move(&cart, ABS, true, 10, 200, 0, NULL);
	std::cout << "linear_move1 :" << ret << std::endl;
	ret = demo.linear_move(&cart, ABS, true, 10, 200, 0, NULL);
	std::cout << "linear_move2 :" << ret << std::endl;
	demo.login_out();
	return 0;
}
//
int example_get_ftp_dir()
{
	int ret;
	//实例API对象demo 
	JAKAZuRobot demo;
	char result[2000] = "\0";
	char dir[20] = "/program/圆弧/";
	//登陆控制器，需要将192.168.2.229替换为自己控制器的IP
	ret = demo.login_in("192.168.2.26");
	demo.init_ftp_client();
	demo.get_ftp_dir(dir, 0, result);
	printf("%s", result);
	demo.close_ftp_client();
	demo.login_out();
	return 0;
}

int example_download_file()
{
	int ret;
	//实例API对象demo 
	JAKAZuRobot test;
	char remote[] = "/program/";
	char local[] = "C:\\Users\\Administrator\\Desktop\\lxxpro";
	//登陆控制器，需要将192.168.2.229替换为自己控制器的IP
	test.login_in("192.168.2.149");
	test.init_ftp_client();
	ret = test.download_file(local, remote, 2);
	printf("%d", ret);
	test.close_ftp_client();
	test.login_out();
	return 0;
}

int example_upload_file()
{
	int ret;
	//实例API对象demo 
	JAKAZuRobot test;
	char remote[] = "/program/jkrc/jkrc.c";
	char local[] = "C:\\Users\\Administrator\\Desktop\\jkrc.c";
	//登陆控制器，需要将192.168.2.229替换为自己控制器的IP
	ret = test.login_in("192.168.2.12");
	test.init_ftp_client();
	test.upload_file(local, remote, 1);
	test.close_ftp_client();
	test.login_out();
	return 0;
}

int example_del_ftp_dir()
{
	int ret;
	//实例API对象demo 
	JAKAZuRobot demo;
	char result[2000] = "\0";
	char dir[20] = "/圆弧/";
	//登陆控制器，需要将192.168.2.229替换为自己控制器的IP
	ret = demo.login_in("192.168.2.26");
	demo.init_ftp_client();
	demo.del_ftp_file(dir, 2);
	printf("%s", result);
	demo.close_ftp_client();
	demo.login_out();
	return 0;
}

// 力控平移
int example_enable_admittance_ctrl_move()
{
	int ret;
	//实例API对象demo 
	JAKAZuRobot demo;
	//登陆控制器，需要将192.168.2.194替换为自己控制器的IP
	demo.login_in(ipaddr.c_str());
	//机器人上电
	demo.power_on();
	//机器人上使能
	demo.enable_robot();
	demo.set_torsenosr_brand(2);
	demo.set_torque_sensor_mode(1);
	demo.set_compliant_type(1, 1);
	printf("inint sensor comple");
	printf("ready to run\n");
	//设置柔顺控制参数
	ret = demo.set_admit_ctrl_config(0, 0, 0, 0, 0, 0);
	ret = demo.set_admit_ctrl_config(1, 0, 0, 0, 0, 0);
	ret = demo.set_admit_ctrl_config(2, 3, 20, 2, 0, 0);
	ret = demo.set_admit_ctrl_config(3, 0, 0, 0, 0, 0);
	ret = demo.set_admit_ctrl_config(4, 0, 0, 0, 0, 0);
	ret = demo.set_admit_ctrl_config(5, 0, 0, 0, 0, 0);
	//#设置力控拖拽使能，1打开，0关闭
	//ret = demo.enable_admittance_ctrl(1);
	CartesianPose cart;
	cart.tran.x = 0; cart.tran.y = -40; cart.tran.z = 0;
	cart.rpy.rx = 0; cart.rpy.ry = 0; cart.rpy.rz = 0;
	ret = demo.linear_move(&cart, INCR, true, 20, 200, 0, NULL);
	std::cout << ret << std::endl;
	std::cout << "wait input" << std::endl;
	std::cin >> ret;
	//设置力控拖拽使能，1打开，0关闭
	ret = demo.enable_admittance_ctrl(0);
	ret = demo.set_admit_ctrl_config(2, 0, 20, 5, 0, 0);
	demo.set_torque_sensor_mode(0);
	std::cout << ret << std::endl;
	demo.login_out();
	return 0;
}

int main()
{
	printf("main start\n");
	//!!!!passed!!!!
	//example_jog();
	//example_joint_move();
	//example_linear_move();
	//example_servo_j();
	example_servo_p();
	//example_set_digital_output();
	//example_set_analog_output();
	//example_program();
	//example_rapidrate();
	//example_drag();
	//example_get_robstate();
	//example_get_tcp_position();
	//example_get_joint_position();
	//example_is_on_limit();
	//example_is_in_pos();
	//example_collision_recover();
	//example_collision_level();
	//example_kine_inverse();
	//example_kine_forward();
	//example_rpy_to_rot_matrix();
	//example_rot_matrix_to_rpy();
	//example_quaternion_to_rot_matrix();
	//example_rot_matrix_to_quaternion();
	//example_payload();
	//example_getsdk_version();
	//example_get_robot_status();
	//example_get_traj_existed_filename();
	//example_rename_traj_file_name();
	//example_get_controller_ip();
	//example_user_frame();
	//example_motion_abort();
	//example_traj_config();
	//example_circle_move();
	//example_servo_use_none_filter();
	//example_servo_use_joint_LPF();
	//example_servo_use_joint_NLF();
	//example_servo_use_carte_NLF();
	//example_servo_use_joint_MMF();
	//example_set_compliant_type();
	//example_get_admit_ctrl_config();
	//example_torque_sensor_comm();
	//example_disable_force_control();
	//example_set_vel_comliant_ctrl();
	//example_set_compliance_condition();
	//example_set_network_exception_handle();
	//example_set_status_data_updata_interval();
	//example_set_err_handle();
	//example_traj_sample();
	//example_get_traj_existed_filename();
	//test_linear_move();
	//example_get_ftp_dir();
	//example_rename_ftp_dir();
	//example_del_ftp_dir();
	//example_upload_file();
	//example_download_file();
	//example_get_ftp_dir_extend();
	//example_enable_admittance_ctrl_move();
	return 0;
}

void output()
{
	clock_t start;
	while (1)
	{
		start = clock();
		printf("thread:    %f\n", ((double)start / CLOCKS_PER_SEC));
		Sleep(500);
	}
}

