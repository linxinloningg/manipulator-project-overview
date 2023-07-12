using System;
using jakaApi;//API引用
using jkType;//数据结构声明
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Text;
namespace sdk_CS
{
    class Program
    {
        static double PI = 3.1415926535;


        /// <summary>
        /// jog运动 vel_cmd超过pi/4会被限幅 
        /// </summary>
        static void example_jog()
        {
            int handle = 0;
            //实例化机器人，将ip切换为自己的ip
            int result = jakaAPI.create_handler("192.168.2.194".ToCharArray(), ref handle);
            jakaAPI.power_on(ref handle);//机器人上电
            jakaAPI.enable_robot(ref handle);//机器人上使能
            int aj_num = 0;
            //选择关节1，运动模式：增量运动；关节坐标系；以3.14/4的速度沿关节1反方向运动1rad。
            jakaAPI.jog(ref handle, aj_num, JKTYPE.MoveMode.INCR, JKTYPE.CoordType.COORD_JOINT, 3.14 / 4, -1);
            System.Threading.Thread.Sleep(1000);
            jakaAPI.jog_stop(ref handle, -1);//-1代表停止所有轴的运动
            //jakaAPI.destory_handler(ref handle);
        }
        /// <summary>
        /// joint move 关节限速pi/2 rad/s
        /// 支持阻塞和非阻塞，速度单位rad/s
        /// </summary>
        static void example_joint_move()
        {
            int handle = 0;
            Stopwatch sw = new Stopwatch();//计时器
            //实例化机器人，将ip切换为自己的ip
            int result = jakaAPI.create_handler("192.168.2.194".ToCharArray(), ref handle);
            jakaAPI.power_on(ref handle);
            jakaAPI.enable_robot(ref handle);
            //定义并初始化关JointValue变量
            JKTYPE.JointValue joint_pos = new JKTYPE.JointValue();
            joint_pos.jVal = new double[] { 1, 1, 1, 1, 1, 1 };
            Console.WriteLine("joint_move指令执行开始");
            sw.Start();
            //阻塞运动到目标点位
            jakaAPI.joint_move(ref handle, ref joint_pos, JKTYPE.MoveMode.ABS, true, 1);
            sw.Stop();
            Console.WriteLine("joint_move指令执行结束{0}ms", sw.ElapsedTicks / (decimal)Stopwatch.Frequency);
            jakaAPI.destory_handler(ref handle);
        }
        /// <summary>
        /// linear move 
        /// 支持阻塞和非阻塞，速度单位mm/s
        /// 注意避免奇异点，常见奇异点：
        /// * 工具末端位置在轴线Z1和Z2构成的平面上；
        /// * 轴线Z2,Z3,Z4共面；
        /// * 关节5角度为0或180°，即Z4,Z6平行；
        /// </summary>
        static void example_linear_move()
        {
            int handle = 0;
            Stopwatch sw = new Stopwatch();//计时器
            Console.WriteLine(sw.ElapsedTicks / (decimal)Stopwatch.Frequency);
            //实例化机器人，将ip切换为自己的ip
            int result = jakaAPI.create_handler("192.168.2.160".ToCharArray(), ref handle);
            jakaAPI.power_on(ref handle);
            jakaAPI.enable_robot(ref handle);
            Console.WriteLine("linear_move指令执行开始");
            JKTYPE.CartesianPose tcp_pos = new JKTYPE.CartesianPose();
            tcp_pos.tran.z = -100;
            sw.Start();
            jakaAPI.linear_move(ref handle, ref tcp_pos, JKTYPE.MoveMode.INCR, true, 30);
            sw.Stop();
            Console.WriteLine("linear_move指令执行结束{0}s", sw.ElapsedTicks / (decimal)Stopwatch.Frequency);
            jakaAPI.destory_handler(ref handle);
        }

        /// <summary>
        ///机器人伺服关节运动servo_j
        ///使用该接口时需要先调用servo_move_enable(TRUE)开启伺服控制
        ///控制器的发送周期为8ms，建议用户发送周期也为8ms，网络环境较差的情况可以适当减小周期
        ///关节速度上限180deg/s
        ///本指令与joint_move有较大差别，joint_move的插补由控制器进行，servo_j需要预先进行轨迹规划。
        /// </summary>
        static void example_servo_j()
        {
            int handle = 0;
            //实例化机器人，将ip切换为自己的ip
            int result = jakaAPI.create_handler("192.168.2.160".ToCharArray(), ref handle);
            //机器人上电
            jakaAPI.power_on(ref handle);
            //机器人上使能
            jakaAPI.enable_robot(ref handle);
            //TRUE为进入伺服模式
            jakaAPI.servo_move_enable(ref handle,true);
            //定义并初始化关JointValue变量
            //定义并初始化关JointValue变量
            JKTYPE.JointValue joint_pos = new JKTYPE.JointValue();
            joint_pos.jVal = new double[] { -0.001, 0 * PI / 180, 0 * PI / 180, 0 * PI / 180, 0 * PI / 180, -0.001 };
            for (int i = 0; i < 100; i++)
            {
                //关节空间伺服运动，其中INCR代表增量运动
                jakaAPI.servo_j(ref handle ,ref joint_pos, JKTYPE.MoveMode.INCR);
                System.Threading.Thread.Sleep(6);
            }
            //FALSE为退出伺服模式
            jakaAPI.servo_move_enable(ref handle ,false);
            
        }

        /// <summary>
        ///机器人伺服笛卡尔空间运动servo_p
        ///使用该接口时需要先调用servo_move_enable(TRUE)开启伺服控制
        ///控制器的发送周期为8ms，建议用户发送周期也为8ms，网络环境较差的情况可以适当减小周期
        ///关节速度上限180deg/s，笛卡尔空间没有相对直观的限制，但应满足该关节速度限制
        ///本指令与linear_move有较大差别，linear_move的插补由控制器进行，servo_p需要预先进行轨迹规划。
        /// </summary>
        static void example_servo_p()//机器人伺服笛卡尔空间运动
        {
            int handle = 0;
            //实例化机器人，将ip切换为自己的ip
            int result = jakaAPI.create_handler("192.168.2.194".ToCharArray(), ref handle);
            //机器人上电
            jakaAPI.power_on(ref handle);
            //机器人上使能
            jakaAPI.enable_robot(ref handle);
            //TRUE为进入伺服模式
            jakaAPI.servo_move_enable(ref handle,true);
            //定义并初始化关CartesianPose变量
            JKTYPE.CartesianPose cart = new JKTYPE.CartesianPose();
            cart.tran.x = 0; cart.tran.y = 1; cart.tran.z = 0;
            cart.rpy.rx = 0; cart.rpy.ry = 0; cart.rpy.rz = 0;
            for (int i = 0; i < 100; i++)
            {
                //笛卡尔空间伺服运动，其中INCR代表增量运动
                jakaAPI.servo_p(ref handle ,ref cart, JKTYPE.MoveMode.INCR);
                System.Threading.Thread.Sleep(6);
            }
            //FALSE为退出伺服模式
            jakaAPI.servo_move_enable(ref handle ,false);
        }

        /// <summary>
        /// 设置和查询IO
        /// </summary>
        static void example_set_digital_optput()
        {
            bool DO2 = false;
            int handle = 0;
            //实例化机器人，将ip切换为自己的ip
            int result = jakaAPI.create_handler("192.168.2.160".ToCharArray(), ref handle);
            jakaAPI.power_on(ref handle);
            jakaAPI.enable_robot(ref handle);
            //查询do2的状态
            jakaAPI.get_digital_output(ref handle, JKTYPE.IOType.IO_CABINET, 2, ref DO2);
            Console.WriteLine("D03 = {0}\n", DO2);
            //io_cabinet是控制柜面板IO，2代表DO2，1对应要设置的DO值。
            jakaAPI.set_digital_output(ref handle, JKTYPE.IOType.IO_CABINET, 2, true);
            System.Threading.Thread.Sleep(1000);
            //查询do2的状态
            jakaAPI.get_digital_output(ref handle, JKTYPE.IOType.IO_CABINET, 2, ref DO2);
            Console.WriteLine("D03 = {0}\n", DO2);
            jakaAPI.destory_handler(ref handle);
        }
        /// <summary>
        /// 加载在app上编写好的程序，并进行过程控制
        /// </summary>
        static void example_program()
        {
            System.Text.StringBuilder name = new System.Text.StringBuilder();
            int handle = 0;
            int cur_line = 0;
            //实例化机器人，将ip切换为自己的ip
            int result = jakaAPI.create_handler("192.168.2.194".ToCharArray(), ref handle);
            JKTYPE.ProgramState pstatus = new JKTYPE.ProgramState();
            //机器人上电
            jakaAPI.power_on(ref handle);
            //机器人上使能
            jakaAPI.enable_robot(ref handle);
            //加载预先通过app编辑的名字叫simple的脚本
            jakaAPI.program_load(ref handle, "testc".ToCharArray());
            //获取已加载的程序名
            jakaAPI.get_loaded_program(ref handle, name);
            Console.WriteLine("Pro_name is:  {0}", name);
            //运行当前加载的程序
            jakaAPI.program_run(ref handle);
            System.Threading.Thread.Sleep(10000);
            //暂停当前运行的程序
            jakaAPI.program_pause(ref handle);
            //获取当前执行程序的行号
            jakaAPI.get_current_line(ref handle, ref cur_line);
            Console.WriteLine("cur_line is: {0}", cur_line);
            //获取当前程序状态
            jakaAPI.get_program_state(ref handle, ref pstatus);
            Console.WriteLine("pro_status is: {0}", pstatus);
            System.Threading.Thread.Sleep(2000);
            //继续运行当前程序
            jakaAPI.program_resume(ref handle);
            System.Threading.Thread.Sleep(10000);
            //终止当前程序
            jakaAPI.program_abort(ref handle);
            jakaAPI.destory_handler(ref handle);
        }

        /// <summary>
        /// 获取与设置机器人的运行速度
        /// </summary>
        static void example_rapidrate()
        {
            int handle = 0; 
            double rapid_rate = 0;
            //实例化机器人，将ip切换为自己的ip
            int result = jakaAPI.create_handler("192.168.2.160".ToCharArray(), ref handle);
            //机器人上电
            jakaAPI.power_on(ref handle);
            //机器人上使能
            jakaAPI.enable_robot(ref handle);
            jakaAPI.get_rapidrate(ref handle, ref rapid_rate);
            Console.WriteLine("rapid_rate is : {0}", rapid_rate);
            //修改程序运行时机器人运动速度
            jakaAPI.set_rapidrate(ref handle, 0.4);
            System.Threading.Thread.Sleep(100);
            jakaAPI.get_rapidrate(ref handle, ref rapid_rate);
            Console.WriteLine("rapid_rate is : {0}", rapid_rate);
            jakaAPI.destory_handler(ref handle);
        }

        /// <summary>
        /// 切换工具坐标系及获取与设置工具坐标系信息
        /// </summary>
        static void example_tool()
        {
            int id_ret = 0;
            int id_set = 0;
            int handle = 0;
            id_set = 2;
            JKTYPE.CartesianPose tcp_ret = new JKTYPE.CartesianPose();
            JKTYPE.CartesianPose tcp_set = new JKTYPE.CartesianPose();
            char[] name = new char[50]; 
            name = "test".ToCharArray();
            //实例化机器人，将ip切换为自己的ip
            int result = jakaAPI.create_handler("192.168.2.160".ToCharArray(), ref handle);
            //机器人上电
            jakaAPI.power_on( ref handle);
            //查询当前使用的工具ID
            jakaAPI.get_tool_id( ref handle,  ref id_ret);
            //获取当前使用的工具信息
            jakaAPI.get_tool_data( ref handle, id_ret,  ref tcp_ret);
            Console.WriteLine("id_using={0} \nx={1}, y={2}, z={3}\n", id_ret, tcp_ret.tran.x, tcp_ret.tran.y, tcp_ret.tran.y);
            Console.WriteLine("rx={0}, ry={1}, rz={2}\n", tcp_ret.rpy.rx, tcp_ret.rpy.ry, tcp_ret.rpy.rz);
            //初始化工具坐标
            tcp_set.tran.x = 0; tcp_set.tran.y = 0; tcp_set.tran.z = 10;
            tcp_set.rpy.rx = 120 * PI / 180; tcp_set.rpy.ry = 90 * PI / 180; tcp_set.rpy.rz = -90 * PI / 180;
            //设置工具信息
            jakaAPI.set_tool_data( ref handle, id_set,  ref tcp_set, name);
            //切换当前使用的工具坐标
            jakaAPI.set_tool_id( ref handle, id_set);
            System.Threading.Thread.Sleep(1000);
            //查询当前使用的工具ID
            jakaAPI.get_tool_id( ref handle,  ref id_ret);
            //获取设置的工具信息
            jakaAPI.get_tool_data(ref handle, id_ret, ref tcp_ret);
            Console.WriteLine("id_using={0} \nx={1}, y={2}, z={3}\n", id_ret, tcp_ret.tran.x, tcp_ret.tran.y, tcp_ret.tran.y);
            Console.WriteLine("rx={0}, ry={1}, rz={2}\n", tcp_ret.rpy.rx, tcp_ret.rpy.ry, tcp_ret.rpy.rz);
            jakaAPI.destory_handler(ref handle);
        }
        /// <summary>
        /// 切换用户坐标系及获取与设置用户坐标系信息
        /// </summary>
        public static void example_user_frame()
        {
            int id_ret = 0;
            int id_set = 2;
            int handle = 0;
            JKTYPE.CartesianPose tcp_ret = new JKTYPE.CartesianPose();
            JKTYPE.CartesianPose tcp_set = new JKTYPE.CartesianPose();
            char[] name = new char[50];
            name = "test".ToCharArray();
            //实例化机器人，将ip切换为自己的ip
            int result = jakaAPI.create_handler("192.168.226.132".ToCharArray(), ref handle);
            //机器人上电
            jakaAPI.power_on(ref handle);
            //查询当前使用的工具ID
            jakaAPI.get_user_frame_id(ref handle, ref id_ret);
            //获取当前使用的工具信息
            jakaAPI.get_user_frame_data(ref handle, id_ret, ref tcp_ret);
            Console.WriteLine("id_using={0} \nx={1}, y={2}, z={3}\n", id_ret, tcp_ret.tran.x, tcp_ret.tran.y, tcp_ret.tran.y);
            Console.WriteLine("rx={0}, ry={1}, rz={2}\n", tcp_ret.rpy.rx, tcp_ret.rpy.ry, tcp_ret.rpy.rz);
            //初始化工具坐标
            tcp_set.tran.x = 0; tcp_set.tran.y = 0; tcp_set.tran.z = 10;
            tcp_set.rpy.rx = 120 * PI / 180; tcp_set.rpy.ry = 90 * PI / 180; tcp_set.rpy.rz = -90 * PI / 180;
            //设置工具信息
            jakaAPI.set_user_frame_data(ref handle, id_set, ref tcp_set, name);
            //切换当前使用的工具坐标
            jakaAPI.set_user_frame_id(ref handle, id_set);
            System.Threading.Thread.Sleep(1000);
            //查询当前使用的工具ID
            jakaAPI.get_user_frame_id(ref handle, ref id_ret);
            //获取当前使用的工具信息
            jakaAPI.get_user_frame_data(ref handle, id_ret, ref tcp_ret);
            Console.WriteLine("id_using={0} \nx={1}, y={2}, z={3}\n", id_ret, tcp_ret.tran.x, tcp_ret.tran.y, tcp_ret.tran.y);
            Console.WriteLine("rx={0}, ry={1}, rz={2}\n", tcp_ret.rpy.rx, tcp_ret.rpy.ry, tcp_ret.rpy.rz);
            jakaAPI.destory_handler(ref handle);
        }
        /// <summary>
        /// 进入拖拽模式，直到获得输入
        /// </summary>
        static void example_drag()
        {
            bool in_drag = true;
            int handle = 0;
            //实例化机器人，将ip切换为自己的ip
            int result = jakaAPI.create_handler("192.168.2.160".ToCharArray(), ref handle);
            //机器人上电
            jakaAPI.power_on( ref handle);
            //机器人上使能
            jakaAPI.enable_robot( ref handle);
            //确认机器人是否在拖拽模式下
            jakaAPI.is_in_drag_mode( ref handle, ref in_drag);
            Console.WriteLine("in_drag is : {0}", in_drag);
            //使能拖拽模式
            jakaAPI.drag_mode_enable( ref handle, true);
            System.Threading.Thread.Sleep(1000);
            jakaAPI.is_in_drag_mode( ref handle, ref in_drag);
            Console.WriteLine("in_drag is : {0}", in_drag);
            Console.WriteLine("input any word to disable dragmode");
            Console.Read();
            //去使能拖拽模式
            jakaAPI.drag_mode_enable(ref handle, false);
            System.Threading.Thread.Sleep(1000);
            jakaAPI.is_in_drag_mode(ref handle, ref in_drag);
            Console.WriteLine("in_drag is : {0}", in_drag);
            jakaAPI.destory_handler(ref handle);
        }
        /// <summary>
        /// 获取机器人状态，(急停 上电 伺服使能)
        /// </summary>
        static void example_get_robot_state()
        {
            int handle = 0;
            //实例化机器人，将ip切换为自己的ip
            int result = jakaAPI.create_handler("192.168.2.160".ToCharArray(), ref handle);
            JKTYPE.RobotState state = new JKTYPE.RobotState();
            //机器人上电
            jakaAPI.power_on(ref handle);
            //机器人上使能
            jakaAPI.enable_robot(ref handle);
            //获取机器人状态(急停 上电 伺服使能)
            jakaAPI.get_robot_state(ref handle, ref state);
            Console.WriteLine("is e_stoped :{0} ", state.estoped);
            jakaAPI.destory_handler(ref handle);
        }
        /// <summary>
        /// 获取机器人tcp空间位姿
        /// </summary>
        static void example_get_tcp_position()
        {
            int handle = 0;
            JKTYPE.CartesianPose tcp_pos = new JKTYPE.CartesianPose();
            //实例化机器人，将ip切换为自己的ip
            int result = jakaAPI.create_handler("192.168.2.160".ToCharArray(), ref handle);
            //机器人上电
            jakaAPI.power_on(ref handle);
            //机器人上使能
            jakaAPI.enable_robot(ref handle);
            //获取工具末端位姿
            jakaAPI.get_tcp_position(ref handle, ref tcp_pos);
            Console.WriteLine("tcp_position is :{0} {1} {2} {3} {4} {5}", tcp_pos.tran.x, tcp_pos.tran.y, tcp_pos.tran.z, tcp_pos.rpy.rx, tcp_pos.rpy.ry, tcp_pos.rpy.rz);
            jakaAPI.destory_handler(ref handle);
        }
        /// <summary>
        /// 获取机器人关节空间关节角矩阵
        /// </summary>
        static void example_get_joint_position()
        {
            int handle = 0;
            JKTYPE.JointValue jot_pos = new JKTYPE.JointValue();
            //实例化机器人，将ip切换为自己的ip
            int result = jakaAPI.create_handler("192.168.2.160".ToCharArray(), ref handle);
            //机器人上电
            jakaAPI.power_on(ref handle);
            //机器人上使能
            jakaAPI.enable_robot(ref handle);
            //获取工具末端位姿
            jakaAPI.get_joint_position(ref handle, ref jot_pos);
            Console.WriteLine("tcp_position is :{0} {1} {2} {3} {4} {5}", jot_pos.jVal[0], jot_pos.jVal[1], jot_pos.jVal[2], jot_pos.jVal[3], jot_pos.jVal[4], jot_pos.jVal[5]);
            jakaAPI.destory_handler(ref handle);
        }
        /// <summary>
        /// 查询运动是否到位
        /// </summary>
        static void example_is_in_pos()
        {
            bool in_pos = false;
            int handle = 0;
            //实例化机器人，将ip切换为自己的ip
            int result = jakaAPI.create_handler("192.168.2.22".ToCharArray(), ref handle);
            //机器人上电
            jakaAPI.power_on(ref handle);
            //机器人上使能
            jakaAPI.enable_robot(ref handle);
            //定义并初始化关JointValue变量
            JKTYPE.JointValue joint_pos = new JKTYPE.JointValue();
            joint_pos.jVal = new double[] { 1, 1, 1, 1, 1, 1 };
            Console.WriteLine("joint_move指令执行开始");
            //阻塞运动到目标点位
            jakaAPI.joint_move(ref handle, ref joint_pos, JKTYPE.MoveMode.ABS, false, 1);
            System.Threading.Thread.Sleep(500);
            while (!in_pos)
            {
                //查询是否运动停止
                jakaAPI.is_in_pos(ref handle, ref in_pos);
                Console.WriteLine(" in_pos is :{0}", in_pos);
                System.Threading.Thread.Sleep(200);
            }
            jakaAPI.destory_handler(ref handle);
        }

        /// <summary>
        /// 碰撞保护状态查询及恢复
        /// </summary>
        static void example_collision_recover()
        {
            bool in_collision = false;
            int handle = 0;
            //实例化机器人，将ip切换为自己的ip
            int result = jakaAPI.create_handler("192.168.2.160".ToCharArray(), ref handle);
            //机器人上电
            jakaAPI.power_on(ref handle);
            //机器人上使能
            jakaAPI.enable_robot(ref handle);
            //查询是否处于碰撞保护状态
            jakaAPI.is_in_collision(ref handle, ref in_collision);
            if (in_collision)
            //如果处于碰撞保护模式，则从碰撞保护中恢复
            {
                jakaAPI.collision_recover(ref handle);
                Console.WriteLine("robot collision recover");
            }
            else
            {
                Console.WriteLine("robot is not collision");
            }
            jakaAPI.destory_handler(ref handle);
        }
        /// <summary>
        /// 碰撞等级的设置和查询
        /// </summary>
        static void  example_collision_level()
        {
            int level = 0 ;
            int handle = 0;
            //实例化机器人，将ip切换为自己的ip
            int result = jakaAPI.create_handler("192.168.2.160".ToCharArray(), ref handle);
            //机器人上电
            jakaAPI.power_on(ref handle);
            //机器人上使能
            jakaAPI.enable_robot(ref handle);
            //查询当前碰撞等级
            jakaAPI.get_collision_level(ref handle, ref level);
            Console.WriteLine(" collision level is :{0}", level);
            //设置碰撞等级，[0,5]，0为关闭碰撞，1为碰撞阈值25N，2为碰撞阈值50N，3为碰撞阈值75N，4为碰撞阈值100N，5为碰撞阈值125N，
            jakaAPI.set_collision_level(ref handle, 2);
            //查询当前碰撞等级
            jakaAPI.get_collision_level(ref handle, ref level);
            Console.WriteLine(" collision level is :{0}", level);
            jakaAPI.destory_handler(ref handle);
        }
        /// <summary>
        /// 力控传感器（额外配件）辨识负载
        /// </summary>
        static void example_sensor_payload()
        {
            Console.WriteLine("sensor in\n");
            JKTYPE.JointValue joint_pos= new JKTYPE.JointValue();
            JKTYPE.PayLoad pl = new JKTYPE.PayLoad(), pl_ret= new JKTYPE.PayLoad();
            int handle = 0;
            int ret = 0;
            //实例化机器人，将ip切换为自己的ip
            Console.WriteLine("login be\n");
            int result = jakaAPI.create_handler("10.5.5.100".ToCharArray(), ref handle);
            Console.WriteLine("login finish\n");
            //机器人上电
            jakaAPI.power_on(ref handle);
            //机器人上使能
            jakaAPI.enable_robot(ref handle);
            Console.WriteLine("enable finish\n");
            ret = jakaAPI.set_torsenosr_brand(ref handle, 2);//设置传感器品牌
            ret = jakaAPI.set_torque_sensor_mode(ref handle, 1);//打开力控传感器
            jakaAPI.get_joint_position(ref handle, ref joint_pos);
            joint_pos.jVal[3] += PI / 4;
            if (joint_pos.jVal[3] > 265 * PI / 180)
                joint_pos.jVal[3] -= PI / 2;
            joint_pos.jVal[4] += PI / 4;
            if (joint_pos.jVal[4] > 320 * PI / 180)
                joint_pos.jVal[4] -= PI / 2;
            joint_pos.jVal[5] += PI / 4;
            if (joint_pos.jVal[5] > 265 * PI / 180)
                joint_pos.jVal[5] -= PI / 2;
            //开始辨识传感器负载
            ret = jakaAPI.start_torq_sensor_payload_identify(ref handle, ref joint_pos);
            do
            {
                //查询传感器负载状态
                jakaAPI.get_torq_sensor_identify_staus(ref handle, ref ret);
                Console.WriteLine("{0}", ret);
                System.Threading.Thread.Sleep(1000);
            } while (1 == ret);
            //获取辨识结果
            ret = jakaAPI.get_torq_sensor_payload_identify_result(ref handle, ref pl);
            //设置传感器末端负载
            Console.WriteLine("payload: {0} {1} {2} {3}", pl.mass, pl.centroid.x, pl.centroid.y, pl.centroid.z);
            ret = jakaAPI.set_torq_sensor_tool_payload(ref handle, ref pl);
            System.Threading.Thread.Sleep(10000);
            //获取当前设置的传感器末端负载
            ret = jakaAPI.get_torq_sensor_tool_payload(ref handle, ref pl_ret);
            System.Threading.Thread.Sleep(10000);
            jakaAPI.destory_handler(ref handle);
        }
        /// <summary>
        /// 力控传感器（额外配件）导纳控制，z轴
        /// </summary>
        static void example_enable_admittance_ctrl()
        {
            int handle = 0;
            int ret;
            //实例化机器人，将ip切换为自己的ip
            int result = jakaAPI.create_handler("10.5.5.100".ToCharArray(), ref handle);
            //机器人上电
            jakaAPI.power_on(ref handle);
            //机器人上使能
            jakaAPI.enable_robot(ref handle);
            //品牌,力控传感器品牌询问服务人员
            jakaAPI.set_torsenosr_brand(ref handle, 2);
            //开启力控传感器
            jakaAPI.set_torque_sensor_mode(ref handle, 1);
            //初始化传感器
            jakaAPI.set_compliant_type(ref handle, 1, 1);
            Console.WriteLine("inint sensor comple\n");
            //设置柔顺控制参数，z轴向下5N恒力
            ret = jakaAPI.set_admit_ctrl_config(ref handle, 0, 0, 20, 5, 0, 0);//x轴
            ret = jakaAPI.set_admit_ctrl_config(ref handle, 1, 0, 20, 5, 0, 0);//y轴
            ret = jakaAPI.set_admit_ctrl_config(ref handle, 2, 3, 20, 5, 0, 0);//z轴
            ret = jakaAPI.set_admit_ctrl_config(ref handle, 3, 0, 20, 5, 0, 0);//rx
            ret = jakaAPI.set_admit_ctrl_config(ref handle, 4, 0, 20, 5, 0, 0);//ry
            ret = jakaAPI.set_admit_ctrl_config(ref handle, 5, 0, 20, 5, 0, 0);//rz
            //设置力控拖拽使能，1打开，0关闭
            ret = jakaAPI.enable_admittance_ctrl(ref handle, 1);
            Console.WriteLine("enable_admittance_ctrl open！\n");
            Console.WriteLine("input any word to quit:\n");
            ret = Console.Read();
            Console.WriteLine("quit!!");
            ret = jakaAPI.enable_admittance_ctrl(ref handle, 0);
            ret = jakaAPI.set_admit_ctrl_config(ref handle, 2, 0, 20, 5, 0, 0);
            jakaAPI.set_torque_sensor_mode(ref handle, 0);
            Console.WriteLine("close\n");
            jakaAPI.destory_handler(ref handle);
        }
        /// <summary>
        /// 运动学 逆解 已知tcp_pos, 求joint_pos
        /// </summary>
        static void example_kine_inverse()
        {
            int handle = 0;
            int ret;
            //实例化机器人，将ip切换为自己的ip
            int result = jakaAPI.create_handler("192.168.2.194".ToCharArray(), ref handle);
            //初始化参考点
            JKTYPE.JointValue ref_jpos = new JKTYPE.JointValue();
            ref_jpos.jVal = new double[] { 0.558, 0.872, 0.872, 0.349, 0.191, 0.191 };
            //初始化笛卡尔空间点坐标
            JKTYPE.CartesianPose tcp_pos = new JKTYPE.CartesianPose();
            tcp_pos.tran.x = 243.568; tcp_pos.tran.y = 164.064; tcp_pos.tran.z = 300.002;
            tcp_pos.rpy.rx = -1.81826; tcp_pos.rpy.ry = -0.834253; tcp_pos.rpy.rz = -2.30243;
            //初始化返回值
            JKTYPE.JointValue joint_pos = new JKTYPE.JointValue();
            joint_pos.jVal = new double[] { 0, 0, 0, 0, 0, 0 };
            //机器人逆解 已知tcp_pos, 求joint_pos
            ret = jakaAPI.kine_inverse(ref handle, ref ref_jpos, ref tcp_pos, ref joint_pos);
            Console.WriteLine(" {0}   kine_inverse:", ret);//若返回值为-4则逆解失败，更改参考点或数学上无解
            Console.WriteLine("{0} {1} {2} ", joint_pos.jVal[0], joint_pos.jVal[1] , joint_pos.jVal[2] );
            Console.WriteLine("{0} {1} {2} ", joint_pos.jVal[3] , joint_pos.jVal[4] , joint_pos.jVal[5] );
            jakaAPI.destory_handler(ref handle);
        }
        /// <summary>
        /// 机器人正解 已知joint_pos,求tcp_pos
        /// </summary>
        static void example_kine_forward()
        {
            int handle = 0;
            int ret;
            //实例化机器人，将ip切换为自己的ip
            int result = jakaAPI.create_handler("192.168.2.160".ToCharArray(), ref handle);
            //初始化笛卡尔空间点坐标
            JKTYPE.CartesianPose tcp_pos = new JKTYPE.CartesianPose();
            //初始化返回值
            JKTYPE.JointValue joint_pos = new JKTYPE.JointValue();
            joint_pos.jVal = new double[] { 0.558, 0.872, 0.872, 0.349, 0.191, 0.191 };
            ret = jakaAPI.kine_forward(ref handle, ref joint_pos, ref tcp_pos);
            Console.WriteLine("tcp_pos is :\n x:{0}  y:{1}  z:{2} rx:{3}  ry:{4}  rz:{5}", tcp_pos.tran.x, tcp_pos.tran.y, tcp_pos.tran.z, tcp_pos.rpy.rx, tcp_pos.rpy.ry, tcp_pos.rpy.rz);
            jakaAPI.destory_handler(ref handle);
        }
        /// <summary>
        /// 欧拉角->旋转矩阵->四元数
        /// </summary>
        static void example_rpy2rot_matr2quat()
        {
            int handle = 0;
            int ret;
            //实例化机器人，将ip切换为自己的ip
            int result = jakaAPI.create_handler("192.168.2.160".ToCharArray(), ref handle);
            //初始化欧拉角
            JKTYPE.Rpy rpy = new JKTYPE.Rpy();
            rpy.rx = -1.81826; rpy.ry = -0.834253; rpy.rz = -2.30243;
            //初始化旋转矩阵
            JKTYPE.RotMatrix rot_matrix = new JKTYPE.RotMatrix();
            rot_matrix.x.x = 0; rot_matrix.y.x = 0; rot_matrix.z.x = 0;
            rot_matrix.x.y = 0; rot_matrix.y.y = 0; rot_matrix.z.y = 0;
            rot_matrix.x.z = 0; rot_matrix.y.z = 0; rot_matrix.z.z = 0;
            //初始化四元数
            JKTYPE.Quaternion quat = new JKTYPE.Quaternion();
            quat.s = 0; quat.x = 0; quat.y = 0; quat.z = 0;
            //欧拉角到旋转矩阵
            ret = jakaAPI.rpy_to_rot_matrix(ref handle, ref rpy, ref rot_matrix);
            Console.WriteLine("     eul2rotm");
            Console.WriteLine("{0} {1} {2}", rot_matrix.x.x, rot_matrix.y.x, rot_matrix.z.x);
            Console.WriteLine("{0} {1} {2}", rot_matrix.x.y, rot_matrix.y.y, rot_matrix.z.y);
            Console.WriteLine("{0} {1} {2}", rot_matrix.x.z, rot_matrix.y.z, rot_matrix.z.z);
            //旋转矩阵--->四元数
            ret = jakaAPI.rot_matrix_to_quaternion(ref handle, ref rot_matrix, ref quat);
            Console.WriteLine(" {0}   rotm2quat:", ret);
            Console.WriteLine("{0} {1} {2} {3} ", quat.s, quat.x, quat.y, quat.z);
            jakaAPI.destory_handler(ref handle);
        }
        /// <summary>
        /// 四元数->旋转矩阵->欧拉角
        /// </summary>
        static void example_quat2rot_matr2rpy()
        {
            int handle = 0;
            int ret;
            //实例化机器人，将ip切换为自己的ip
            int result = jakaAPI.create_handler("192.168.2.160".ToCharArray(), ref handle);
            //初始化欧拉角
            JKTYPE.Rpy rpy = new JKTYPE.Rpy();
            rpy.rx = 0; rpy.ry = 0; rpy.rz = 0;
            //初始化旋转矩阵
            JKTYPE.RotMatrix rot_matrix = new JKTYPE.RotMatrix();
            rot_matrix.x.x = 0; rot_matrix.y.x = 0; rot_matrix.z.x = 0;
            rot_matrix.x.y = 0; rot_matrix.y.y = 0; rot_matrix.z.y = 0;
            rot_matrix.x.z = 0; rot_matrix.y.z = 0; rot_matrix.z.z = 0;
            //初始化四元数
            JKTYPE.Quaternion quat = new JKTYPE.Quaternion();
            quat.s = 0.0629; quat.x = 0.522886; quat.y = -0.5592; quat.z = 0.6453;
            //四元数-->旋转矩阵
            ret = jakaAPI.quaternion_to_rot_matrix(ref handle, ref quat, ref rot_matrix);
            Console.WriteLine(" {0}    quatl2rotm:", ret);
            Console.WriteLine("{0} {1} {2}", rot_matrix.x.x, rot_matrix.y.x, rot_matrix.z.x);
            Console.WriteLine("{0} {1} {2}", rot_matrix.x.y, rot_matrix.y.y, rot_matrix.z.y);
            Console.WriteLine("{0} {1} {2}", rot_matrix.x.z, rot_matrix.y.z, rot_matrix.z.z);
            //旋转矩阵--->欧拉角
            ret = jakaAPI.rot_matrix_to_rpy(ref handle, ref rot_matrix, ref rpy);
            Console.WriteLine(" {0}    rotm2eul:", ret);
            Console.WriteLine("{0} {1} {2} ", rpy.rx, rpy.ry, rpy.rz);
            jakaAPI.destory_handler(ref handle);
        }
        /// <summary>
        /// 错误处理函数挂接，多线程方式进行
        /// </summary>

        static void user_error_handle(int error_code)
        {
            Console.WriteLine("{0}", error_code);
            int a = 0;
            a = Console.Read();
            Console.WriteLine("{0}\n", a);
        }
        //注册
        static void example_set_err_handle()
        {
            int handle = 0;
            //实例化机器人，将ip切换为自己的ip
            int result = jakaAPI.create_handler("192.168.2.160".ToCharArray(), ref handle);
            //机器人上电
            jakaAPI.power_on(ref handle);
            //机器人上使能
            jakaAPI.enable_robot(ref handle);
            //设置用户异常回调函数
            jakaAPI.set_error_handler(ref handle ,user_error_handle);
            while (true)
            {
                System.Threading.Thread.Sleep(1000);
                Console.WriteLine("nothing happen");
            }
            jakaAPI.destory_handler(ref handle);
        }
        /// <summary>
        /// 获取与设置负载
        /// </summary>
        static void example_payload()
        {
            int handle = 0;
            int ret;
            //实例化机器人，将ip切换为自己的ip
            int result = jakaAPI.create_handler("192.168.2.160".ToCharArray(), ref handle);
            JKTYPE.PayLoad payloadret = new JKTYPE.PayLoad();
            payloadret.mass = 0;
            payloadret.centroid.x = 0; payloadret.centroid.y = 0; payloadret.centroid.z = 0;
            JKTYPE.PayLoad payload_set = new JKTYPE.PayLoad();
            //查询当前负载数据
            jakaAPI.get_payload(ref handle, ref payloadret);
            Console.WriteLine(" payload mass is : {0} kg", payloadret.mass);
            Console.WriteLine(" payload center of mass is \nx: {0}  y: {1} z: {2} ", payloadret.centroid.x, payloadret.centroid.y, payloadret.centroid.z);
            payload_set.mass = 1.0;
            //单位mm
            payload_set.centroid.x = 0; payload_set.centroid.y = 0; payload_set.centroid.z = 10;
            //设置当前负载数据
            jakaAPI.set_payload(ref handle, ref payload_set);
            //查询当前负载数据
            jakaAPI.get_payload(ref handle, ref payloadret);
            Console.WriteLine(" payload mass is : {0} kg", payloadret.mass);
            Console.WriteLine(" payload center of mass is \nx: {0}  y: {1} z: {2} ", payloadret.centroid.x, payloadret.centroid.y, payloadret.centroid.z);
            jakaAPI.destory_handler(ref handle);
        }
        /// <summary>
        /// 获取局域网内所有机器人的ip及名称
        /// </summary>
        static void example_get_controller_ip()
        {
            int handle = 0;
            int ret;
            //实例化机器人，将ip切换为自己的ip
            // int result = jakaAPI.create_handler("192.168.2.160".ToCharArray(), ref handle);
            StringBuilder ip_list = new StringBuilder("",3000);
            char[] controller_name1 = new char[10];
            controller_name1[0] = '\0';
            Console.WriteLine("start to get ip");
            //获取控制器ip
            ret = jakaAPI.get_controller_ip( controller_name1, ip_list);
            Console.WriteLine("ip list get :{0}", ret);
            Console.WriteLine(" ip_list is :\n {0}", ip_list);
            jakaAPI.destory_handler(ref handle);
        }
        /// <summary>
        /// 获取机器人状态信息24种
        /// </summary>
        static void example_get_robot_status()
        {
            int handle = 0;
            int ret = 0 ;
            JKTYPE.RobotStatus robstatus = new JKTYPE.RobotStatus();
            JKTYPE.ProgramState prostatus = new JKTYPE.ProgramState();
            //实例化机器人，将ip切换为自己的ip
            int result = jakaAPI.create_handler("192.168.2.194".ToCharArray(), ref handle);
            //机器人上电
            jakaAPI.power_on(ref handle);
            //机器人上使能
            jakaAPI.enable_robot(ref handle);
            while (true)
            {
                ret++;
                System.Threading.Thread.Sleep(1000);
                //获取机器人状态监测数据
                jakaAPI.get_robot_status(ref handle, ref robstatus);
                jakaAPI.get_program_state(ref handle, ref prostatus);
                Console.WriteLine("{1}rapidrate:{0}\n", robstatus.rapidrate, ret);
                Console.WriteLine("{1}rapidrate:{0}\n", prostatus, ret);
            }
            jakaAPI.disable_robot(ref handle);
            jakaAPI.power_off(ref handle);
            jakaAPI.destory_handler(ref handle);
        }
        /// <summary>
        /// 开启sdkdebug模式
        /// </summary>
        static void example_set_debug_mode()
        {
            int handle = 0;
            int ret = 0;
            //实例化机器人，将ip切换为自己的ip
            int result = jakaAPI.create_handler("192.168.2.160".ToCharArray(), ref handle);
            //开启调试模式
            jakaAPI.set_debug_mode(ref handle, true);
            Console.WriteLine("debug :true");
            //机器人上电
            jakaAPI.power_on(ref handle);
            //机器人上使能
            jakaAPI.enable_robot(ref handle);
            jakaAPI.destory_handler(ref handle);
        }
        /// <summary>
        /// 运动终止
        /// </summary>
        static void example_motion_abort()
        {
            int handle = 0;
            int ret = 0;
            //实例化机器人，将ip切换为自己的ip
            int result = jakaAPI.create_handler("192.168.2.160".ToCharArray(), ref handle);
            JKTYPE.JointValue joint_pos = new JKTYPE.JointValue();
            //机器人上电
            jakaAPI.power_on(ref handle);
            //机器人上使能
            jakaAPI.enable_robot(ref handle);
            //定义并初始化关JointValue变量
            Console.WriteLine("start_move");
            joint_pos.jVal = new double[] { 0 * PI / 180, 0 * PI / 180, 50 * PI / 180, 0 * PI / 180, 0 * PI / 180, 0 * PI / 180 };
            //关节空间运动，其中ABS代表绝对运动，TRUE代表指令是阻塞的，1代表速度为1rad/s  
            jakaAPI.joint_move(ref handle, ref joint_pos, JKTYPE.MoveMode.ABS, false, 1);
            System.Threading.Thread.Sleep(500);
            //运动0.5s后终止
            jakaAPI.motion_abort(ref handle);
            Console.WriteLine("stop_move");
            jakaAPI.destory_handler(ref handle);
        }
        /// <summary>  
        /// 轨迹复现  
        /// </summary>  
        static void example_traj_sample()
        {
            bool samp_stu = false;
            int handle = 0;
            int ret = 0;
            //实例化机器人，将ip切换为自己的ip  
            int result = jakaAPI.create_handler("192.168.2.52".ToCharArray(), ref handle);
            jakaAPI.set_debug_mode(ref handle, true);
            JKTYPE.JointValue joint_pos = new JKTYPE.JointValue();
            joint_pos.jVal = new double[] { 1, 1, 1, 1, 1, 1 };
            JKTYPE.JointValue joint_pos2 = new JKTYPE.JointValue();
            joint_pos2.jVal = new double[] { -1, 1, 1, 1, 1, 1 };
            //机器人上电  
            jakaAPI.power_on(ref handle);
            //机器人上使能  
            jakaAPI.enable_robot(ref handle);
            char[] name = new char[40];
            char[] trajname = new char[40];
            name = "testxx".ToCharArray();
            trajname = "track/testxx".ToCharArray();
            jakaAPI.joint_move(ref handle, ref joint_pos2, JKTYPE.MoveMode.ABS, true, 1);
            //开启轨迹复现数据采集开关  
            jakaAPI.set_traj_sample_mode(ref handle, true, name);
            //查询轨迹复现采集状态  
            jakaAPI.get_traj_sample_status(ref handle, ref samp_stu);
            //关节空间运动，其中ABS代表绝对运动，TRUE代表指令是阻塞的，1代表速度为1rad/s    
            jakaAPI.joint_move(ref handle, ref joint_pos, JKTYPE.MoveMode.ABS, true, 1);
            jakaAPI.joint_move(ref handle, ref joint_pos2, JKTYPE.MoveMode.ABS, true, 1);
            jakaAPI.set_traj_sample_mode(ref handle, false, name);
            System.Threading.Thread.Sleep(500);
            jakaAPI.generate_traj_exe_file(ref handle, name);
            System.Threading.Thread.Sleep(500);
            jakaAPI.program_load(ref handle, trajname);
            System.Threading.Thread.Sleep(100);
            jakaAPI.program_run(ref handle);
            jakaAPI.destory_handler(ref handle);
        }
        /// <summary>  
        /// 获取所有轨迹文件名 
        /// </summary>
        static void example_get_traj_existed_filename()
        {;
            JKTYPE.MultStrStorType traj_file =new JKTYPE.MultStrStorType();            
            int handle = 0;
            int ret = 0;
            //实例化机器人，将ip切换为自己的ip
            int result = jakaAPI.create_handler("192.168.2.160".ToCharArray(), ref handle);
            //查询当前轨迹文件名。
            jakaAPI.get_exist_traj_file_name(ref handle, ref traj_file);
            Console.WriteLine("file nums :{0}", traj_file.len);
            string ss = new string(traj_file.name);
            Console.WriteLine(ss);
            jakaAPI.destory_handler(ref handle);
        }
        /// <summary>  
        /// 圆弧运动  
        /// </summary>
        static void example_circle_move()
        {
            JKTYPE.OptionalCond opt = new JKTYPE.OptionalCond();
            JKTYPE.CartesianPose end_p = new JKTYPE.CartesianPose(), mid_p = new JKTYPE.CartesianPose();
            end_p.tran.x = -200; end_p.tran.y = 400; end_p.tran.z = 400;
            end_p.rpy.rx = -90 * PI / 180; end_p.rpy.ry = 0 * PI / 180; end_p.rpy.rz = 0 * PI / 180;
            mid_p.tran.x = -300; mid_p.tran.y = 400; mid_p.tran.z = 500;
            mid_p.rpy.rx = -90 * PI / 180; mid_p.rpy.ry = 0 * PI / 180; mid_p.rpy.rz = 0 * PI / 180;
            int handle = 0;
            int ret = 0;
            //实例化机器人，将ip切换为自己的ip
            int result = jakaAPI.create_handler("192.168.2.160".ToCharArray(), ref handle);
            //机器人上电
            jakaAPI.power_on(ref handle);
            //机器人上使能
            jakaAPI.enable_robot(ref handle);
            //定义并初始化关JointValue变量
            JKTYPE.JointValue joint_pos = new JKTYPE.JointValue();
            joint_pos.jVal = new double[] { 85.76 * PI / 180, -6.207 * PI / 180, 111.269 * PI / 180, 74.938 * PI / 180, 94.24 * PI / 180, 0 * PI / 180 };
            //关节空间运动，其中ABS代表绝对运动，TRUE代表指令是阻塞的，1代表速度为1rad/s  
            jakaAPI.joint_move(ref handle, ref joint_pos, JKTYPE.MoveMode.ABS, true, 1);
            //圆弧运动，其中ABS代表绝对运动，TRUE代表指令是阻塞的，20代表直线速度为20mm/s，1代表加速度，0.1代表机器人终点误差，opt为可选参数。 
            jakaAPI.circular_move(ref handle, ref end_p, ref mid_p, JKTYPE.MoveMode.ABS, true, 20, 1, 0.1, ref opt);
        }
        /// <summary>  
        /// 禁用滤波器  
        /// </summary>
        static void example_servo_use_none_filter()
        {
            int ret;
            int handle = 0;
            //实例化机器人，将ip切换为自己的ip
            int result = jakaAPI.create_handler("192.168.2.160".ToCharArray(), ref handle);
            //机器人上电
            jakaAPI.power_on(ref handle);
            //机器人上使能
            jakaAPI.enable_robot(ref handle);
            ret = jakaAPI.servo_move_use_none_filter(ref handle);
        }
        /// <summary>  
        /// 关节一阶低通滤波  
        /// </summary>
        static void example_servo_use_joint_LPF()
        {
            int ret;
            int handle = 0;
            //实例化机器人，将ip切换为自己的ip
            int result = jakaAPI.create_handler("192.168.2.160".ToCharArray(), ref handle);
            //机器人上电
            jakaAPI.power_on(ref handle);
            //机器人上使能
            jakaAPI.enable_robot(ref handle);
            //servo模式下关节空间一阶低通滤波,截止频率0.5Hz
            ret = jakaAPI.servo_move_use_joint_LPF(ref handle, 0.5);
        }
        /// <summary>  
        /// 关节非线性 
        /// </summary>
        static void example_servo_use_joint_NLF()
        {
            int ret;
            int handle = 0;
            //实例化机器人，将ip切换为自己的ip
            int result = jakaAPI.create_handler("192.168.2.160".ToCharArray(), ref handle);
            //机器人上电
            jakaAPI.power_on(ref handle);
            //机器人上使能
            jakaAPI.enable_robot(ref handle);
            //servo模式下关节空间非线性滤波
            ret = jakaAPI.servo_move_use_joint_NLF(ref handle, 2, 2, 4);
        }
        /// <summary>  
        /// 笛卡尔空间非线性滤波 
        /// </summary>
        static void example_servo_use_carte_NLF()
        {
            int handle = 0;
            int ret = 0;
            //实例化机器人，将ip切换为自己的ip
            int result = jakaAPI.create_handler("192.168.2.160".ToCharArray(), ref handle);
            //机器人上电
            jakaAPI.power_on(ref handle);
            //机器人上使能
            jakaAPI.enable_robot(ref handle);
            //servo模式下笛卡尔空间非线性滤波
            ret = jakaAPI.servo_move_use_carte_NLF(ref handle, 2, 2, 4, 2, 2, 4);
        }
        /// <summary>  
        /// 关节空间多阶均值滤波 
        /// </summary>
        static void example_servo_use_joint_MMF()
        {
            int handle = 0;
            int ret = 0;
            //实例化机器人，将ip切换为自己的ip
            int result = jakaAPI.create_handler("192.168.2.160".ToCharArray(), ref handle);
            //机器人上电
            jakaAPI.power_on(ref handle);
            //机器人上使能
            jakaAPI.enable_robot(ref handle);
            //servo模式下关节空间多阶均值滤波
            ret = jakaAPI.servo_move_use_joint_MMF(ref handle, 200, 2, 4, 2);
        }
        /// <summary>  
        /// 速度前瞻 
        /// </summary>
        static void example_speed_foresight()
        {
            int handle = 0;
            int ret = 0;
            //实例化机器人，将ip切换为自己的ip
            int result = jakaAPI.create_handler("192.168.2.160".ToCharArray(), ref handle);
            //机器人上电
            jakaAPI.power_on(ref handle);
            //机器人上使能
            jakaAPI.enable_robot(ref handle);
            //servo模式下速度前瞻
            ret = jakaAPI.servo_speed_foresight(ref handle, 200, 2);
        }

        static void example_torque_sensor_comm()
        {
            int ret;
            byte[] ip_ret = new byte[20];
            int type_ret = 0;
            int port_ret = 0;
            int handle = 0;
            //实例化机器人，将ip切换为自己的ip
            int result = jakaAPI.create_handler("192.168.2.102".ToCharArray(), ref handle);
            //机器人上电f
            jakaAPI.power_on(ref handle);
            //机器人上使能
            jakaAPI.enable_robot(ref handle);
            //获取力控通讯参数
            ret = jakaAPI.get_torque_sensor_comm(ref handle, ref type_ret, ref ip_ret, ref port_ret);
            string strGet = System.Text.Encoding.Default.GetString(ip_ret, 0, 20);
            Console.WriteLine("ip:{0}\n port:{1}", ip_ret, port_ret);
        }
        /// <summary>  
        /// 设置机器人状态robotstatus更新频率，若不设置，则默认尽可能快 
        /// </summary>
        static void example_set_status_data_updata_interval()
        {
            float milisec = 1000;
            int ret;
            int handle = 0;
            //实例化机器人，将ip切换为自己的ip
            int result = jakaAPI.create_handler("192.168.2.160".ToCharArray(), ref handle);
            //机器人上电
            jakaAPI.power_on(ref handle);
            //机器人上使能
            jakaAPI.enable_robot(ref handle);
            //设置状态自动更新时间
            ret = jakaAPI.set_status_data_update_time_interval(ref handle,milisec);
            Console.WriteLine("ret:{0}",ret);
            while (true)
            {
                System.Threading.Thread.Sleep(100000);
            }
        }
        static void test_linear_move()
        {
            int i = 0;
            int ret = 0;
            int handle = 0;
            //实例化机器人，将ip切换为自己的ip
            int result = jakaAPI.create_handler("192.168.2.194".ToCharArray(), ref handle);
            ret = jakaAPI.set_status_data_update_time_interval(ref handle, 0);
            jakaAPI.power_on(ref handle);
            jakaAPI.enable_robot(ref handle);
            JKTYPE.CartesianPose tcp_pos = new JKTYPE.CartesianPose();
            JKTYPE.OptionalCond option_cond = new JKTYPE.OptionalCond();
            //获取当前tcp位置
            jakaAPI.get_tcp_position(ref handle, ref tcp_pos);
            while (true)
            {
                tcp_pos.tran.x = tcp_pos.tran.x + 10;
                Console.WriteLine("linear_move指令执行开始");
                //移动到当前点x偏置10
                ret = jakaAPI.linear_move_extend(ref handle, ref tcp_pos, JKTYPE.MoveMode.ABS, false, 30, 200, 0, ref option_cond);
                Console.WriteLine("{0}", ret);
                //移动到当前点2
                tcp_pos.tran.x = tcp_pos.tran.x - 10;
                ret = jakaAPI.linear_move_extend(ref handle, ref tcp_pos, JKTYPE.MoveMode.ABS, false, 30, 200, 0, ref option_cond);
                Console.WriteLine("{0} i= {1}", ret,i);
                i++;
            }
            
            jakaAPI.destory_handler(ref handle);
        }
        static void test_linear_move_extend()
        {
            int ret = 0;
            int handle = 0;
            Stopwatch sw = new Stopwatch();//计时器
            Console.WriteLine(sw.ElapsedTicks / (decimal)Stopwatch.Frequency);
            //实例化机器人，将ip切换为自己的ip
            int result = jakaAPI.create_handler("192.168.2.194".ToCharArray(), ref handle);
            jakaAPI.power_on(ref handle);
            jakaAPI.enable_robot(ref handle);
            Console.WriteLine("linear_move指令执行开始");
            JKTYPE.CartesianPose tcp_pos = new JKTYPE.CartesianPose();
            jakaAPI.get_tcp_position(ref handle,ref tcp_pos);
            tcp_pos.tran.x = 0;            tcp_pos.tran.y = 0;          tcp_pos.tran.z = 0;
            JKTYPE.CartesianPose fone = new JKTYPE.CartesianPose();
            fone = tcp_pos;
            fone.tran.x = 30;            fone.tran.y = 0;
            JKTYPE.CartesianPose ftwo = new JKTYPE.CartesianPose();
            ftwo = tcp_pos;
            ftwo.tran.x = 30;
            ftwo.tran.y = ftwo.tran.y + 30;

            JKTYPE.CartesianPose fthree = new JKTYPE.CartesianPose();
            fthree = tcp_pos;
            fthree.tran.x = fthree.tran.x + 30;
            fthree.tran.y = 30;

            JKTYPE.CartesianPose ffour = new JKTYPE.CartesianPose();
            ffour = tcp_pos;
            ffour.tran.x = ffour.tran.x + 30;

            JKTYPE.CartesianPose one = new JKTYPE.CartesianPose();
            one = tcp_pos;
            one.tran.x = 45;           one.tran.y = 80;
            JKTYPE.CartesianPose two = new JKTYPE.CartesianPose();
            two = one;
            two.tran.x = 30;            two.tran.y = 95;
            JKTYPE.CartesianPose three = new JKTYPE.CartesianPose();
            three = one;
            three.tran.x = 45; three.tran.y = 110;
            JKTYPE.CartesianPose four = new JKTYPE.CartesianPose();
            four = one;
            four.tran.x = 60;
            four.tran.y = 95;
            JKTYPE.OptionalCond option_cond = new JKTYPE.OptionalCond();

            ret = jakaAPI.linear_move_extend(ref handle, ref tcp_pos, JKTYPE.MoveMode.ABS, true, 30, 200, 0, ref option_cond);
            
            
            ret = jakaAPI.linear_move_extend(ref handle, ref fone, JKTYPE.MoveMode.ABS, true, 10, 200, 0, ref option_cond);
            ret = jakaAPI.linear_move_extend(ref handle, ref ftwo, JKTYPE.MoveMode.ABS, true, 30, 200, 0, ref option_cond);
            ret = jakaAPI.linear_move_extend(ref handle, ref fthree, JKTYPE.MoveMode.ABS, true, 30, 200, 0, ref option_cond);
            ret = jakaAPI.linear_move_extend(ref handle, ref ffour, JKTYPE.MoveMode.ABS, true, 30, 200, 0, ref option_cond);
            Console.WriteLine("1{0}kill", ret);
            four.tran.z = 20;
            ret = jakaAPI.linear_move_extend(ref handle, ref ffour, JKTYPE.MoveMode.ABS, true, 30, 200, 0, ref option_cond);


            ret = jakaAPI.linear_move_extend(ref handle, ref one, JKTYPE.MoveMode.ABS, false, 10, 200, 5, ref option_cond);
            ret = jakaAPI.linear_move_extend(ref handle, ref two, JKTYPE.MoveMode.ABS, false, 10, 200, 5, ref option_cond);
            ret = jakaAPI.linear_move_extend(ref handle, ref three, JKTYPE.MoveMode.ABS, false, 10, 200, 5, ref option_cond);
            ret = jakaAPI.linear_move_extend(ref handle, ref four, JKTYPE.MoveMode.ABS, false, 10, 200, 5, ref option_cond);
            JKTYPE.RobotStatus status = new JKTYPE.RobotStatus();
            while (true)
            {
                jakaAPI.get_robot_status(ref handle, ref status);
                if (status.inpos == 1)
                {
                    break;
                }
            }
            tcp_pos.tran.x = tcp_pos.tran.x - 50;
            ret = jakaAPI.linear_move_extend(ref handle, ref tcp_pos, JKTYPE.MoveMode.ABS, true, 30, 200, 0, ref option_cond);
            jakaAPI.destory_handler(ref handle);
        }
        static void Main(string[] args)
        {
            Console.WriteLine("main start\n");
            ///tested///
            //example_jog();
            //example_joint_move();
            //example_linear_move();
            //example_set_digital_optput();
            //example_program();
            //example_rapidrate();
            //example_tool();
            //example_user_frame();
            //example_drag();
            //example_get_robot_state();
            //example_get_tcp_position();
            //example_get_joint_position();
            //example_is_in_pos();
            //example_sensor_payload();
            //example_collision_recover();
            //example_collision_level();
            //example_kine_inverse();
            //example_kine_forward();
            //example_rpy2rot_matr2quat();
            //example_quat2rot_matr2rpy();
            //example_set_err_handle();
            //example_payload();
            //example_set_debug_mode();
            //example_traj_sample();
            //example_enable_admittance_ctrl();
            //example_servo_j();
            //example_servo_p();
            //example_get_traj_existed_filename();
            //example_set_status_data_updata_interval();
            //test_linear_move();
            //test_linear_move_extend();
            ///err///
            //example_get_controller_ip();//失败
            //example_get_robot_status();
            //example_torque_sensor_comm();//失败

            int handle = 0;
            //实例化机器人，将ip切换为自己的ip
            int result;
            Console.WriteLine("start");
            Console.WriteLine("create");
            result = jakaAPI.create_handler("172.30.1.205".ToCharArray(), ref handle);
            //机器人上电
            result = jakaAPI.power_on(ref handle);
            Console.WriteLine("ret= {0}\n", result);
            //机器人上使能
            jakaAPI.enable_robot(ref handle);
            Console.WriteLine("ret= {0}\n", result);
            JKTYPE.RobotStatus status = new JKTYPE.RobotStatus();
            while (true)
            {
                jakaAPI.get_robot_status(ref handle, ref status);
                if (status.inpos == 1)
                {
                    break;
                }
            }
            jakaAPI.disable_robot(ref handle);
            Console.WriteLine("ret= {0}\n", result);
            result = jakaAPI.power_off(ref handle);
            Console.WriteLine("ret= {0}\n", result);
            result = jakaAPI.destory_handler(ref handle);
        }
    }
}
