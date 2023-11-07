/**
  ****************************(C) COPYRIGHT 2023 POLARBEAR****************************
  * @file       Balance_Controler.c/h
  * @brief      北极熊的平衡车车底盘控制器
  * @note       

*********  *********  *              *      *********  ********   *********      *     *********
*       *  *       *  *             * *     *       *  *       *  *             * *    *       *
*       *  *       *  *            *   *    *       *  *       *  *            *   *   *       *
*       *  *       *  *           *     *   *       *  *       *  *           *     *  *       *
*********  *       *  *          *********  *********  ********   *********  ********* *********
*          *       *  *          *       *  * *        *       *  *          *       * * *
*          *       *  *          *       *  *   *      *       *  *          *       * *   *
*          *       *  *          *       *  *     *    *       *  *          *       * *     *
*          *********  *********  *       *  *       *  ********   *********  *       * *       *


(9*9)

  ****************************(C) COPYRIGHT 2023 POLARBEAR****************************
  */
#ifndef BALANCE_CONTROLER_H
#define BALANCE_CONTROLER_H

#include "struct_typedef.h"
#include "./Drives/MI_motor_drive.h"
//导入轮腿模型
#include "./leg_model/JointPos.h"
#include "./leg_model/LegConv.h"
#include "./leg_model/LegPos.h"
#include "./leg_model/LegSpd.h"
#include "./leg_model/LQR_K.h"
#include "./leg_model/PID.h"


/* Useful constants.  */
#define MAXFLOAT	3.40282347e+38F
#define M_E		2.7182818284590452354
#define M_LOG2E		1.4426950408889634074
#define M_LOG10E	0.43429448190325182765
#define M_LN2		_M_LN2
#define M_LN10		2.30258509299404568402
#define M_PI		3.14159265358979323846
#define M_TWOPI         (M_PI * 2.0)
#define M_PI_2		1.57079632679489661923
#define M_PI_4		0.78539816339744830962
#define M_3PI_4		2.3561944901923448370E0
#define M_SQRTPI        1.77245385090551602792981
#define M_1_PI		0.31830988618379067154
#define M_2_PI		0.63661977236758134308
#define M_2_SQRTPI	1.12837916709551257390
#define M_SQRT2		1.41421356237309504880
#define M_SQRT1_2	0.70710678118654752440
#define M_LN2LO         1.9082149292705877000E-10
#define M_LN2HI         6.9314718036912381649E-1
#define M_SQRT3	1.73205080756887719000
#define M_IVLN10        0.43429448190325182765 /* 1 / log(10) */
#define M_LOG2_E        _M_LN2
#define M_INVLN2        1.4426950408889633870E0  /* 1 / log(2) */

#define REDUCTION_RATIO_2006 0.027777777777777776 //2006减速比(1:36)
#define WHEEL_RADIUS 0.0425 //m，车轮半径
#define LEG_MASS 0.12368    //kg，腿部质量

#define WHEEL_CAN hcan2


/** @brief      底盘IMU数据结构体
  * @note       
  */
typedef struct 
{
    float yaw, pitch, roll; // rad
    float yawSpd, pitchSpd, rollSpd; // rad/s
    float xAccel,yAccel,zAccel; // m/s^2
} Chassis_IMU_t;


/** @brief      电机结构体
  * @note       leftJoint[0]:左前关节电机, leftJoint[1]:左后关节电机, leftWheel:左车轮电机
  *             rightJoint[0]:右前关节电机, rightJoint[1]:右后关节电机, rightWheel:右车轮电机
  */
typedef struct 
{
    MI_Motor_s* MI_Motor;  // 小米电机对象
    float speed;           // rad/s
    float angle;           // rad 关节与机体水平正方向的夹角
    float offset_angle;    // rad 
    float initial_angle;   // rad 初始状态下电机反馈的角度
    float vertical_angle;  // rad 关节朝向机体竖直正方向的反馈角度
    float horizontal_angle;// rad 关节朝向机体水平正方向的反馈角度
    float target_angle;    // rad 关节与机体水平正方向的目标夹角
    float upper_limit_angle,lower_limit_angle;// rad
    float voltage, max_voltage; // V
    float torque, torque_ratio; // Nm, voltage = torque / torque_ratio
    float dir;				   // 1 or -1
    float rx_torque;  // Nm 反馈力矩
}Motor_s;


/** @brief      腿部姿态结构体
  * @note       无
  */
typedef struct 
{
    float angle, length;   // rad, m
    float dAngle, dLength; // rad/s, m/s
    float ddLength;       // m/s^2
}Leg_Pos_t;


/** @brief      状态变量结构体
  * @note       无
  */
typedef struct 
{
    float theta, dTheta;
    float x, dx;
    float phi, dPhi;
    float leg_length, dLegLength;
} State_Var_s; 


/** @brief      目标量结构体
  * @note       无
  */
typedef struct 
{
    float position;	 // m
    float speed_cmd; // m/s 期望达到的目标前进速度
    float speed;     // m/s 实际控制的目标前进速度（加入积分项消除静差）
    float speed_integral; // m/s 速度积分项
    float yaw_speed_cmd; // rad/s
    float yaw_speed; // rad/s 目标转动速度
    float yaw;	 // rad
    float pitch; // rad
    float roll;  // rad
    float leg_length; // m
    float leg_angle;  // rad
} Target_s;


/** @brief      触地检测数据结构体
  * @note       无
  */
typedef struct 
{
    float left_support_force, right_support_force;
    bool_t is_touching_ground, is_slipping;
    uint32_t last_touching_ground_time;
} Ground_Detector_s;


/** @brief      限制量结构体
  * @note       无
  */
typedef struct 
{
    float leg_angle_min;
    float leg_angle_max;
    float leg_length_min;
    float leg_length_max;
    float pitch_max;
    float roll_max;
} Limit_Value_t;


/** @brief      机器人状态枚举量
  * @note       无
  */
typedef enum 
{
    RobotState_OFF,
    RobotState_MotorZeroing,
    RobotState_LegExtension,
    RobotState_Balance,
} Robot_State_e;


/** @brief      控制模式
  * @note       无
  */
typedef enum 
{
    No_Control,
    Location_Control,
    Torque_Control,
} CyberGear_Control_State_e;

//外用变量
extern MI_Motor_s MI_Motor[5];
extern Motor_s left_joint[2], right_joint[2], left_wheel, right_wheel; //六个电机对象

//外用函数
void SetRobotState(Robot_State_e state);
void SetCyberGearMechPositionToZero();


const Chassis_IMU_t* GetChassisIMUPoint();
const Target_s* GetTargetPoint();
const Leg_Pos_t *GetLegPosPoint(uint8_t leg);
Robot_State_e GetRobotState();
const State_Var_s *GetStateVarPoint();


void InitBalanceControler();
void DataUpdate(
        Chassis_IMU_t* p_chassis_IMU,
        float speed, float yaw_delta, float pitch_delta, float roll_delta, float length_delta
        );
void ControlBalanceChassis(CyberGear_Control_State_e CyberGear_control_state);
void BalanceControlerCalc();



#endif