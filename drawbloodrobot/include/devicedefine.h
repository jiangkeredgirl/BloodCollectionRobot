#pragma once
/*****************************************************************//**
 * \file   devicedefine.h
 * \brief  采血机器人系统的设备定义（由多个子设备组合成采血机器人）
 *
 * \author 蒋珂
 * \date   2023.05.08
 *********************************************************************/
#include <vector>
#include <map>
#include <iostream>
#include <string>
#include "errorcode.h"
using namespace std;

/// 设备类型
enum E_DEVICE_TYPE
{
	DEVICE_TYPE_UNKNOWN,       //< 未知设备
	DEVICE_TYPE_SYSTEM,        //< 系统设备,整个机器人系统
	DEVICE_TYPE_ARMPLATE,      //< 固定手臂的采血台
	DEVICE_TYPE_ROBOTARM,      //< 机械臂
	DEVICE_TYPE_ULTRASOUND,    //< 超声波	
	DEVICE_TYPE_SYRINGE,       //< 注射器，采血，注射   
	DEVICE_TYPE_END            //< enum 结束标记
};

/// 设备状态
enum E_DEVICE_STATE
{
	DEVICE_STATE_UNKNOWN,       //< 未知状态
	DEVICE_STATE_ABNORMAL,      //< 异常
	DEVICE_STATE_NORMAL,        //< 正常，机械臂、超声波等设备开机前、开机	
	DEVICE_STATE_STANDBY,       //< 待机，机械臂、超声波等设备已经启动、等待指令
	DEVICE_STATE_RUNNING,       //< 运行(这个状态，先保留, 和【待机】这个状态差不多，了解更多需求后，决定是否启用）
	DEVICE_STATE_WORKING,       //< 工作中，比如机械臂在运动，超声波在扫描，注射器在抽血
	DEVICE_STATE_MANUAL,        //< 人工干预(这个状态，先保留, 需要人工操作，比如人工扎针）
	DEVICE_STATE_URGENTSTOP,    //< 紧急停止(这个状态，先保留, 需要紧急停止设备）
	DEVICE_STATE_END            //< enum 结束标记
};

/// 系统设备编号（针对多个设备）
enum E_SYSTEMDEVICE_NUM
{
	SYSTEMDEVICE_NUM_0 = 0,    //<  设备只有1个
	SYSTEMDEVICE_NUM_MAX = 1
};

/// 系统设备状态
enum E_SYSTEMDEVICE_STATE
{
	//< 定义设备自己的状态，无特别状态
};

/// 系统设备操作
enum E_SYSTEMDEVICE_OPERA
{
	SYSTEMDEVICE_OPERA_UNKNOWN,       //< 未知操作
	SYSTEMDEVICE_OPERA_BOOT,          //< 启动
	SYSTEMDEVICE_OPERA_SHUTDOWN,      //< 关机
	SYSTEMDEVICE_OPERA_MANUAL,        //< 人工干预
	SYSTEMDEVICE_OPERA_URGENTSTOP,    //< 紧急停止
	SYSTEMDEVICE_OPERA_END            //< enum 结束标记
};

enum E_SYSTEMDEVICE_ERROR
{
	SYSTEMDEVICE_ERROR_BOOT = BLOODROBOT_ERROR_SYSTEMDEVICE_BOOT
};

/// 固定手臂的采血台
enum E_ARMPLATEDEVICE_NUM
{
	ARMPLATEDEVICE_NUM_0 = 0,    //<  设备只有1个
	ARMPLATEDEVICE_NUM_MAX = 1
};

enum E_ARMPLATEDEVICE_STATE
{
	//< 定义设备自己的状态，无特别状态
};

enum E_ARMPLATEDEVICE_OPERA
{
	ARMPLATEDEVICE_OPERA_UNKNOWN = SYSTEMDEVICE_OPERA_END + 1,         //< 未知操作
	ARMPLATEDEVICE_OPERA_ARMFIXED,        //< 固定手臂
	ARMPLATEDEVICE_OPERA_ARMUNFIXED,      //< 松开手臂
	ARMPLATEDEVICE_OPERA_BAND,            //< 手臂轧带
	ARMPLATEDEVICE_OPERA_LOOSEBAND,       //< 手臂松开轧带
	ARMPLATEDEVICE_OPERA_END              //< enum 结束标记
};

enum E_ARMPLATEDEVICE_ERROR
{
	ARMPLATEDEVICE_ERROR_BOOT      = BLOODROBOT_ERROR_ARMPLATEDEVICE_BOOT,         //< 采血台设备启动错误
	ARMPLATEDEVICE_ERROR_BAND      = BLOODROBOT_ERROR_ARMPLATEDEVICE_BAND,         //< 采血台设备扎带错误
	ARMPLATEDEVICE_ERROR_LOOSEBAND = BLOODROBOT_ERROR_ARMPLATEDEVICE_LOOSEBAND     //< 采血台设备松扎带错误
};


/// 超声波
enum E_ULTRASOUNDDEVICE_NUM
{
	ULTRASOUNDDEVICE_NUM_0 = 0,    //<  设备只有1个
	ULTRASOUNDDEVICE_NUM_MAX = 1
};

enum E_ULTRASOUNDDEVICE_STATE
{
	//< 定义设备自己的状态，无特别状态
};

enum E_ULTRASOUNDDEVICE_OPERA
{
	ULTRASOUNDDEVICE_OPERA_UNKNOWN = ARMPLATEDEVICE_OPERA_END + 1,         //< 未知操作
	ULTRASOUNDDEVICE_OPERA_SCAN,              //< 扫描
	ULTRASOUNDDEVICE_OPERA_SCANCOMPLETE,      //< 扫描结果
	ULTRASOUNDDEVICE_OPERA_END                //< enum 结束标记
};

enum E_ULTRASOUNDDEVICE_ERROR
{
	ULTRASOUNDDEVICE_ERROR_BOOT = BLOODROBOT_ERROR_ULTRASOUNDDEVICE_BOOT,      //< 超声波启动错误
	ULTRASOUNDDEVICE_ERROR_SCAN = BLOODROBOT_ERROR_ULTRASOUNDDEVICE_SCAN       //< 超声波扫描错误
};


/// 机械臂
enum E_ROBOTARMDEVICE_NUM
{
	ROBOTARMDEVICE_NUM_0 = 0,    //<  设备只有1个
	ROBOTARMDEVICE_NUM_MAX = 1
};

enum E_ROBOTARMDEVICE_STATE
{
	//< 定义设备自己的状态，无特别状态
};

enum E_ROBOTARMDEVICE_OPERA
{
	ROBOTARMDEVICE_OPERA_UNKNOWN = ULTRASOUNDDEVICE_OPERA_END + 1,         //< 未知操作
	ROBOTARMDEVICE_OPERA_NEEDLEPOS,              //< 针尖位置	
	ROBOTARMDEVICE_OPERA_END                     //< enum 结束标记
};

enum E_ROBOTARMDEVICE_ERROR
{
	ROBOTARMDEVICE_ERROR_BOOT  = BLOODROBOT_ERROR_ROBOTARMDEVICE_BOOT,      //< 机械臂启动错误
	ROBOTARMDEVICE_ERROR_JOINT = BLOODROBOT_ERROR_ROBOTARMDEVICE_JOINT      //< 机械臂关节错误
};

/// 注射器
enum E_SYRINGEDEVICE_NUM
{
	SYRINGEDEVICE_NUM_0 = 0,    //<  设备只有1个
	SYRINGEDEVICE_NUM_MAX = 1
};

enum E_SYRINGEDEVICE_STATE
{
	//< 定义设备自己的状态，无特别状态
};

enum E_SYRINGEDEVICE_OPERA
{
	SYRINGEDEVICE_OPERA_UNKNOWN = ROBOTARMDEVICE_OPERA_END + 1,         //< 未知操作
	SYRINGEDEVICE_OPERA_PUMP,                   //< 注射器抽取血液	
	SYRINGEDEVICE_OPERA_PUMPPOS,                //< 注射器抽取血液当前位置	
	SYRINGEDEVICE_OPERA_END                     //< enum 结束标记
};

enum E_SYRINGEDEVICE_ERROR
{
	SYRINGEDEVICE_ERROR_BOOT = BLOODROBOT_ERROR_SYRINGEDEVICE_BOOT,      //< 注射器启动错误
	SYRINGEDEVICE_ERROR_PUMP = BLOODROBOT_ERROR_SYRINGEDEVICE_PUMP       //< 注射器抽血错误
};



/// 设备信息
struct DeviceValue
{
public:
	string device_name;          //< 设备名
	int device_type  = 0;        //< 设备类型
	int device_num   = 0;        //< 设备序号
	int device_state = 0;        //< 设备当前状态
	int device_opera = 0;        //< 设备当前操作
	int error_level  = 0;        //< 设备错误等级
	int error_code   = 0;        //< 设备错误码
public:
	DeviceValue()
	{
	}
	DeviceValue(const DeviceValue& other)
	{
		this->operator=(other);
	}
	DeviceValue& operator = (const DeviceValue& other)
	{
		device_name   = other.device_name;
		device_type   = other.device_type;
		device_num    = other.device_num;
		device_state  = other.device_state;
		error_level   = other.error_level;
		error_code    = other.error_code;
		return *this;
	}
};


/// 系统设备信息
struct SystemDeviceValue : public DeviceValue
{

};

/// 采血台设备信息
struct ArmPlateDeviceValue : public DeviceValue
{

};

/// 超声波设备信息
struct UltraSoundDeviceValue : public DeviceValue
{

};

struct RobotArmDevicePos
{
	double x = 0;
	double y = 0;
	double z = 0;
};
/// 机械臂设备信息
struct RobotArmDeviceValue : public DeviceValue
{
	RobotArmDevicePos pos; // 机械臂尖端位置
};

/// 注射器设备信息
struct SyringeDeviceValue : public DeviceValue
{

};