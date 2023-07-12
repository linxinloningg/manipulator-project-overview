using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Text;
using jkType;

namespace jakaApi
{
	public delegate void CallBackFuncType(int error_code);
	public class jakaAPI
	{
		[DllImport("jakaAPI.dll", EntryPoint = "get_controller_ip", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int get_controller_ip(char[] controller_name, StringBuilder ip);
		[DllImport("jakaAPI.dll", EntryPoint = "create_handler", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int create_handler(char[] ip, ref int handle);
		[DllImport("jakaAPI.dll", EntryPoint = "destory_handler", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int destory_handler(ref int handle);
		[DllImport("jakaAPI.dll", EntryPoint = "power_on", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int power_on(ref int handle);
		[DllImport("jakaAPI.dll", EntryPoint = "power_off", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int power_off(ref int handle);
		[DllImport("jakaAPI.dll", EntryPoint = "shut_down", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int shut_down(ref int handle);

		[DllImport("jakaAPI.dll", EntryPoint = "enable_robot", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int enable_robot(ref int handle);
		[DllImport("jakaAPI.dll", EntryPoint = "disable_robot", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int disable_robot(ref int handle);
		[DllImport("jakaAPI.dll", EntryPoint = "jog", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]

		public static extern int jog(ref int handle, int aj_num, JKTYPE.MoveMode move_mode, JKTYPE.CoordType coord_type, double vel_cmd, double pos_cmd);
		[DllImport("jakaAPI.dll", EntryPoint = "jog_stop", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]

		public static extern int jog_stop(ref int handle, int num);
		[DllImport("jakaAPI.dll", EntryPoint = "joint_move", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int joint_move(ref int handle, ref JKTYPE.JointValue joint_pos, JKTYPE.MoveMode move_mode, bool is_block, double speed);

		[DllImport("jakaAPI.dll", EntryPoint = "linear_move", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]

		public static extern int linear_move(ref int handle, ref JKTYPE.CartesianPose end_pos, JKTYPE.MoveMode move_mode, bool is_block, double speed);
		[DllImport("jakaAPI.dll", EntryPoint = "servo_move_enable", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]

		public static extern int servo_move_enable(ref int handle, bool enable);
		[DllImport("jakaAPI.dll", EntryPoint = "servo_j", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]

		public static extern int servo_j(ref int handle, ref JKTYPE.JointValue joint_pos, JKTYPE.MoveMode move_mode);
		[DllImport("jakaAPI.dll", EntryPoint = "servo_j_extend", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]

		public static extern int servo_j_extend(ref int handle, ref JKTYPE.JointValue joint_pos, JKTYPE.MoveMode move_mode, int step_num);
		[DllImport("jakaAPI.dll", EntryPoint = "servo_p", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]

		public static extern int servo_p(ref int handle, ref JKTYPE.CartesianPose cartesian_pose, JKTYPE.MoveMode move_mode);
		[DllImport("jakaAPI.dll", EntryPoint = "servo_p_extend", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]

		public static extern int servo_p_extend(ref int handle, ref JKTYPE.CartesianPose cartesian_pose, JKTYPE.MoveMode move_mode, int step_num);
		[DllImport("jakaAPI.dll", EntryPoint = "set_digital_output", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int set_digital_output(ref int handle, JKTYPE.IOType type, int index, bool value);
		[DllImport("jakaAPI.dll", EntryPoint = "set_analog_output", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]

		public static extern int set_analog_output(ref int handle, JKTYPE.IOType type, int index, float value);
		[DllImport("jakaAPI.dll", EntryPoint = "get_digital_input", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int get_digital_input(ref int handle, JKTYPE.IOType type, int index, ref bool result);
		[DllImport("jakaAPI.dll", EntryPoint = "get_digital_output", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]

		public static extern int get_digital_output(ref int handle, JKTYPE.IOType type, int index, ref bool result);
		[DllImport("jakaAPI.dll", EntryPoint = "get_analog_input", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]

		public static extern int get_analog_input(ref int handle, JKTYPE.IOType type, int index, ref float result);
		[DllImport("jakaAPI.dll", EntryPoint = "get_analog_output", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int get_analog_output(ref int handle, JKTYPE.IOType type, int index, ref float result);
		[DllImport("jakaAPI.dll", EntryPoint = "is_extio_running", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]

		public static extern int is_extio_running(ref int handle, ref bool is_running);
		[DllImport("jakaAPI.dll", EntryPoint = "program_run", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]

		public static extern int program_run(ref int handle);
		[DllImport("jakaAPI.dll", EntryPoint = "program_pause", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]

		public static extern int program_pause(ref int handle);
		[DllImport("jakaAPI.dll", EntryPoint = "program_resume", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]

		public static extern int program_resume(ref int handle);
		[DllImport("jakaAPI.dll", EntryPoint = "program_abort", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]

		public static extern int program_abort(ref int handle);
		[DllImport("jakaAPI.dll", EntryPoint = "program_load", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]

		public static extern int program_load(ref int handle, char[] file);
		[DllImport("jakaAPI.dll", EntryPoint = "get_loaded_program", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]

		public static extern int get_loaded_program(ref int handle, StringBuilder file);
		[DllImport("jakaAPI.dll", EntryPoint = "get_current_line", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]

		public static extern int get_current_line(ref int handle, ref int curr_line);
		[DllImport("jakaAPI.dll", EntryPoint = "get_program_state", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]

		public static extern int get_program_state(ref int handle, ref JKTYPE.ProgramState status);
		[DllImport("jakaAPI.dll", EntryPoint = "set_rapidrate", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]

		public static extern int set_rapidrate(ref int handle, double rapid_rate);
		[DllImport("jakaAPI.dll", EntryPoint = "get_rapidrate", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]

		public static extern int get_rapidrate(ref int handle, ref double rapid_rate);
		[DllImport("jakaAPI.dll", EntryPoint = "set_tool_data", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]

		public static extern int set_tool_data(ref int handle, int id, ref JKTYPE.CartesianPose tcp, char[] name);
		[DllImport("jakaAPI.dll", EntryPoint = "get_tool_data", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]

		public static extern int get_tool_data(ref int handle, int id, ref JKTYPE.CartesianPose tcp);
		[DllImport("jakaAPI.dll", EntryPoint = "set_tool_id", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]

		public static extern int set_tool_id(ref int handle, int id);
		[DllImport("jakaAPI.dll", EntryPoint = "get_tool_id", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]

		public static extern int get_tool_id(ref int handle, ref int id);
		[DllImport("jakaAPI.dll", EntryPoint = "set_user_frame_data", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]

		public static extern int set_user_frame_data(ref int handle, int id, ref JKTYPE.CartesianPose user_frame, char[] name);
		[DllImport("jakaAPI.dll", EntryPoint = "get_user_frame_data", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]

		public static extern int get_user_frame_data(ref int handle, int id, ref JKTYPE.CartesianPose user_frame);
		[DllImport("jakaAPI.dll", EntryPoint = "set_user_frame_id", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]

		public static extern int set_user_frame_id(ref int handle, int id);
		[DllImport("jakaAPI.dll", EntryPoint = "get_user_frame_id", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]

		public static extern int get_user_frame_id(ref int handle, ref int id);
		[DllImport("jakaAPI.dll", EntryPoint = "drag_mode_enable", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]

		public static extern int drag_mode_enable(ref int handle, bool enable);
		[DllImport("jakaAPI.dll", EntryPoint = "is_in_drag_mode", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]

		public static extern int is_in_drag_mode(ref int handle, ref bool in_drag);
		[DllImport("jakaAPI.dll", EntryPoint = "get_robot_state", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]

		public static extern int get_robot_state(ref int handle, ref JKTYPE.RobotState state);
		[DllImport("jakaAPI.dll", EntryPoint = "get_tcp_position", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]

		public static extern int get_tcp_position(ref int handle, ref JKTYPE.CartesianPose tcp_position);
		[DllImport("jakaAPI.dll", EntryPoint = "get_joint_position", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]

		public static extern int get_joint_position(ref int handle, ref JKTYPE.JointValue joint_position);
		[DllImport("jakaAPI.dll", EntryPoint = "is_in_collision", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]

		public static extern int is_in_collision(ref int handle, ref bool in_collision);
		[DllImport("jakaAPI.dll", EntryPoint = "is_on_limit", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]

		public static extern int is_on_limit(ref int handle, ref bool on_limit);
		[DllImport("jakaAPI.dll", EntryPoint = "is_in_pos", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]

		public static extern int is_in_pos(ref int handle, ref bool in_pos);
		[DllImport("jakaAPI.dll", EntryPoint = "collision_recover", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]

		public static extern int collision_recover(ref int handle);
		[DllImport("jakaAPI.dll", EntryPoint = "set_collision_level", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]

		public static extern int set_collision_level(ref int handle, int level);
		[DllImport("jakaAPI.dll", EntryPoint = "get_collision_level", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int get_collision_level(ref int handle, ref int level);
		[DllImport("jakaAPI.dll", EntryPoint = "kine_inverse", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]

		public static extern int kine_inverse(ref int handle, ref JKTYPE.JointValue ref_pos, ref JKTYPE.CartesianPose cartesian_pose, ref JKTYPE.JointValue joint_pos);
		[DllImport("jakaAPI.dll", EntryPoint = "kine_forward", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]

		public static extern int kine_forward(ref int handle, ref JKTYPE.JointValue joint_pos, ref JKTYPE.CartesianPose cartesian_pose);
		[DllImport("jakaAPI.dll", EntryPoint = "rpy_to_rot_matrix", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]

		public static extern int rpy_to_rot_matrix(ref int handle, ref JKTYPE.Rpy rpy, ref JKTYPE.RotMatrix rot_matrix);
		[DllImport("jakaAPI.dll", EntryPoint = "rot_matrix_to_rpy", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]

		public static extern int rot_matrix_to_rpy(ref int handle, ref JKTYPE.RotMatrix rot_matrix, ref JKTYPE.Rpy rpy);
		[DllImport("jakaAPI.dll", EntryPoint = "quaternion_to_rot_matrix", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]

		public static extern int quaternion_to_rot_matrix(ref int handle, ref JKTYPE.Quaternion quaternion, ref JKTYPE.RotMatrix rot_matrix);
		[DllImport("jakaAPI.dll", EntryPoint = "rot_matrix_to_quaternion", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]

		public static extern int rot_matrix_to_quaternion(ref int handle, ref JKTYPE.RotMatrix rot_matrix, ref JKTYPE.Quaternion quaternion);
		[DllImport("jakaAPI.dll", EntryPoint = "torque_control_enable", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]

		public static extern int torque_control_enable(ref int handle, bool enable);
		[DllImport("jakaAPI.dll", EntryPoint = "torque_feedforward", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]

		public static extern int torque_feedforward(ref int handle, JKTYPE.TorqueValue tor_val, int grv_flag);
		[DllImport("jakaAPI.dll", EntryPoint = "set_payload", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]

		public static extern int set_payload(ref int handle, ref JKTYPE.PayLoad payload);
		[DllImport("jakaAPI.dll", EntryPoint = "get_payload", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]

		public static extern int get_payload(ref int handle, ref JKTYPE.PayLoad payload);
		[DllImport("jakaAPI.dll", EntryPoint = "set_error_handler", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int set_error_handler(ref int i, CallBackFuncType func);
		[DllImport("jakaAPI.dll", EntryPoint = "get_sdk_version", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int get_sdk_version(ref int i, StringBuilder version);
		[DllImport("jakaAPI.dll", EntryPoint = "get_robot_status", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int get_robot_status(ref int i, ref JKTYPE.RobotStatus status);
		[DllImport("jakaAPI.dll", EntryPoint = "motion_abort", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int motion_abort(ref int i);
		[DllImport("jakaAPI.dll", EntryPoint = "set_errorcode_file_path", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int set_errorcode_file_path(ref int i, StringBuilder path);
		[DllImport("jakaAPI.dll", EntryPoint = "get_last_error", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int get_last_error(ref int i, ref JKTYPE.ErrorCode code);
		[DllImport("jakaAPI.dll", EntryPoint = "set_debug_mode", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int set_debug_mode(ref int i, bool mode);
		[DllImport("jakaAPI.dll", EntryPoint = "set_traj_config", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int set_traj_config(ref int i, ref JKTYPE.TrajTrackPara para);
		[DllImport("jakaAPI.dll", EntryPoint = "get_traj_config", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int get_traj_config(ref int i, ref JKTYPE.TrajTrackPara para);
		[DllImport("jakaAPI.dll", EntryPoint = "set_traj_sample_mode", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int set_traj_sample_mode(ref int i, bool mode, char[] filename);
		[DllImport("jakaAPI.dll", EntryPoint = "get_traj_sample_status", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int get_traj_sample_status(ref int i, ref bool sample_statuse);
		[DllImport("jakaAPI.dll", EntryPoint = "get_exist_traj_file_name", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int get_exist_traj_file_name(ref int i, ref JKTYPE.MultStrStorType filename);
		[DllImport("jakaAPI.dll", EntryPoint = "rename_traj_file_name", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int rename_traj_file_name(ref int i, ref char[] src, ref char[] dest);
		[DllImport("jakaAPI.dll", EntryPoint = "remove_traj_file", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int remove_traj_file(ref int i, ref char[] filename);
		[DllImport("jakaAPI.dll", EntryPoint = "generate_traj_exe_file", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int generate_traj_exe_file(ref int i, char[] filename);
		[DllImport("jakaAPI.dll", EntryPoint = "joint_move_extend", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int joint_move_extend(ref int i, ref JKTYPE.JointValue joint_pos, JKTYPE.MoveMode move_mode, bool is_block, double speed, double acc, double tol, ref JKTYPE.OptionalCond option_cond);
		[DllImport("jakaAPI.dll", EntryPoint = "linear_move_extend", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int linear_move_extend(ref int i, ref JKTYPE.CartesianPose cart_pos, JKTYPE.MoveMode move_mode, bool is_block, double speed, double acc, double tol, ref JKTYPE.OptionalCond option_cond);
		[DllImport("jakaAPI.dll", EntryPoint = "circular_move", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int circular_move(ref int i, ref JKTYPE.CartesianPose end_pos, ref JKTYPE.CartesianPose mid_pos, JKTYPE.MoveMode move_mode, bool is_block, double speed, double acc, double tol, ref JKTYPE.OptionalCond option_cond);
		[DllImport("jakaAPI.dll", EntryPoint = "servo_move_use_none_filter", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int servo_move_use_none_filter(ref int i);
		[DllImport("jakaAPI.dll", EntryPoint = "servo_move_use_joint_LPF", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int servo_move_use_joint_LPF(ref int i, double cutoffFreq);
		[DllImport("jakaAPI.dll", EntryPoint = "servo_move_use_joint_NLF", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int servo_move_use_joint_NLF(ref int i, double max_vr, double max_ar, double max_jr);
		[DllImport("jakaAPI.dll", EntryPoint = "servo_move_use_carte_NLF", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int servo_move_use_carte_NLF(ref int i, double max_vp, double max_ap, double max_jp, double max_vr, double max_ar, double max_jr);
		[DllImport("jakaAPI.dll", EntryPoint = "servo_move_use_joint_MMF", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int servo_move_use_joint_MMF(ref int i, int max_buf, double kp, double kv, double ka);
		[DllImport("jakaAPI.dll", EntryPoint = "servo_speed_foresight", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int servo_speed_foresight(ref int i, int max_buf, double kp);
		[DllImport("jakaAPI.dll", EntryPoint = "set_SDK_filepath", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int set_SDK_filepath(ref int i, ref char[] filepath);
		[DllImport("jakaAPI.dll", EntryPoint = "set_torsenosr_brand", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int set_torsenosr_brand(ref int i, int sensor_brand);
		[DllImport("jakaAPI.dll", EntryPoint = "get_torsenosr_brand", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int get_torsenosr_brand(ref int i, ref int sensor_brand);
		[DllImport("jakaAPI.dll", EntryPoint = "set_torque_sensor_mode", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int set_torque_sensor_mode(ref int i, int sensor_mode);
		[DllImport("jakaAPI.dll", EntryPoint = "set_admit_ctrl_config", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int set_admit_ctrl_config(ref int i, int axis, int opt, int ftUser, int ftConstant, int ftNnormalTrack, int ftReboundFK);
		[DllImport("jakaAPI.dll", EntryPoint = "start_torq_sensor_payload_identify", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int start_torq_sensor_payload_identify(ref int i, ref JKTYPE.JointValue joint_pos);
		[DllImport("jakaAPI.dll", EntryPoint = "get_torq_sensor_identify_staus", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int get_torq_sensor_identify_staus(ref int i, ref int identify_status);
		[DllImport("jakaAPI.dll", EntryPoint = "get_torq_sensor_payload_identify_result", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int get_torq_sensor_payload_identify_result(ref int i, ref JKTYPE.PayLoad payload);
		[DllImport("jakaAPI.dll", EntryPoint = "set_torq_sensor_tool_payload", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int set_torq_sensor_tool_payload(ref int i, ref JKTYPE.PayLoad payload);
		[DllImport("jakaAPI.dll", EntryPoint = "get_torq_sensor_tool_payload", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int get_torq_sensor_tool_payload(ref int i, ref JKTYPE.PayLoad payload);
		[DllImport("jakaAPI.dll", EntryPoint = "enable_admittance_ctrl", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int enable_admittance_ctrl(ref int i, int enable_flag);
		[DllImport("jakaAPI.dll", EntryPoint = "set_compliant_type", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int set_compliant_type(ref int i, int sensor_compensation, int compliance_type);
		[DllImport("jakaAPI.dll", EntryPoint = "get_compliant_type", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int get_compliant_type(ref int i, ref int sensor_compensation, ref int compliance_type);
		[DllImport("jakaAPI.dll", EntryPoint = "clear_error", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int clear_error(ref int i);
		[DllImport("jakaAPI.dll", EntryPoint = "get_admit_ctrl_config", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int get_admit_ctrl_config(ref int i, ref JKTYPE.RobotAdmitCtrl admit_ctrl_cfg);
		[DllImport("jakaAPI.dll", EntryPoint = "set_torque_sensor_comm", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int set_torque_sensor_comm(ref int i, int type, ref char[] ip_addr, int port);
		[DllImport("jakaAPI.dll", EntryPoint = "get_torque_sensor_comm", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int get_torque_sensor_comm(ref int i, ref int type, ref byte[] ip_addr, ref int port);

		[DllImport("jakaAPI.dll", EntryPoint = "disable_force_control", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int disable_force_control(ref int i);
		[DllImport("jakaAPI.dll", EntryPoint = "set_vel_compliant_ctrl", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int set_vel_compliant_ctrl(ref int i, ref JKTYPE.VelCom vel);
		[DllImport("jakaAPI.dll", EntryPoint = "set_compliance_condition", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int set_compliance_condition(ref int i, ref JKTYPE.FTxyz ft);
		[DllImport("jakaAPI.dll", EntryPoint = "set_network_exception_handle", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int set_network_exception_handle(ref int i, float millisecond, JKTYPE.ProcessType mnt);
		[DllImport("jakaAPI.dll", EntryPoint = "set_status_data_update_time_interval", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int set_status_data_update_time_interval(ref int i, float millisecond);
		[DllImport("jakaAPI.dll", EntryPoint = "set_ft_ctrl_frame", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int set_ft_ctrl_frame(ref int i, int ftFrame);
		[DllImport("jakaAPI.dll", EntryPoint = "get_ft_ctrl_frame", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int get_ft_ctrl_frame(ref int i,ref int ftFrame);
		[DllImport("jakaAPI.dll", EntryPoint = "get_dh_param", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int get_ft_ctrl_frame(ref int i,ref JKTYPE.DHParam offset);
		[DllImport("jakaAPI.dll", EntryPoint = "set_tio_vout_param", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int set_ft_ctrl_frame(ref int i, int vout_enable,int vout_vol);
		[DllImport("jakaAPI.dll", EntryPoint = "get_tio_vout_param", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int get_ft_ctrl_frame(ref int i,ref int vout_enable,ref int vout_vol);
		[DllImport("jakaAPI.dll", EntryPoint = "set_block_wait_timeout", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int set_ft_ctrl_frame(ref int i, float seconds);
		[DllImport("jakaAPI.dll", EntryPoint = "set_torque_sensor_filter", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int set_torque_sensor_filter(ref int i, float torque_sensor_filter);
		[DllImport("jakaAPI.dll", EntryPoint = "get_torque_sensor_filter", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int get_torque_sensor_filter(ref int i, ref float torque_sensor_filter);
		[DllImport("jakaAPI.dll", EntryPoint = "set_torque_sensor_filter", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int set_torque_sensor_soft_limit(ref int i, jkType.JKTYPE.FTxyz torque_sensor_soft_limit);
		[DllImport("jakaAPI.dll", EntryPoint = "get_torque_sensor_soft_limit", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int get_torque_sensor_soft_limit(ref int i, ref jkType.JKTYPE.FTxyz torque_sensor_soft_limit);

		[DllImport("jakaAPI.dll", EntryPoint = "init_ftp_client", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int init_ftp_client(ref int i);
		[DllImport("jakaAPI.dll", EntryPoint = "close_ftp_client", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int close_ftp_client(ref int i);
		[DllImport("jakaAPI.dll", EntryPoint = "download_file", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int download_file(ref int i,ref char local,ref char remote, int opt);
		[DllImport("jakaAPI.dll", EntryPoint = "upload_file", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int upload_file(ref int i, ref char local, ref char remote, int opt);
		[DllImport("jakaAPI.dll", EntryPoint = "del_ftp_file", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int del_ftp_file(ref int i, ref char remote, int opt);
		[DllImport("jakaAPI.dll", EntryPoint = "rename_ftp_file", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int rename_ftp_file(ref int i, ref char remote, ref char des, int opt);
		[DllImport("jakaAPI.dll", EntryPoint = "get_ftp_dir", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
		public static extern int get_ftp_dir(ref int i,char[] remote, int type, StringBuilder ret );
	}
}
