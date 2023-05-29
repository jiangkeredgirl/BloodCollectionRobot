#pragma once
/*********************************************************************
 * \file   errorcode.h
 * \brief  整个系统的错误码定义
 *
 * \author 蒋珂
 * \date   2023.05.08
 *********************************************************************/
#include <map>
using namespace std;

 // 错误等级

enum E_BLOODROBOT_ERROR_LEVEL
{
	ERROR_LEVEL_NONE,     //< 没有错误	
	ERROR_LEVEL_WARN,     //< 警告类错误
	ERROR_LEVEL_COMMON,   //< 一般错误
	ERROR_LEVEL_FATAL,    //< 严重错误
};


/// error_code  0-100 reserver
#define BLOODROBOT_ERRORCODE_OK                            0
#define BLOODROBOT_ERRORCODE_UNKNOWN                       1

/// system device error 100-199
#define BLOODROBOT_ERROR_SYSTEMDEVICE_BOOT                 100  // 系统设备启动错误
/// armplate device error 200-299
#define BLOODROBOT_ERROR_ARMPLATEDEVICE_BOOT               200  // 采血台设备启动错误
#define BLOODROBOT_ERROR_ARMPLATEDEVICE_BAND               201  // 采血台设备扎带错误
#define BLOODROBOT_ERROR_ARMPLATEDEVICE_LOOSEBAND          202  // 采血台设备松扎带错误
/// robot arm device error 300-399
#define BLOODROBOT_ERROR_ROBOTARMDEVICE_BOOT               300  // 机械臂启动错误
#define BLOODROBOT_ERROR_ROBOTARMDEVICE_JOINT              301  // 机械臂关节错误
/// ultrasound device error 400-499
#define BLOODROBOT_ERROR_ULTRASOUNDDEVICE_BOOT             400  // 超声波启动错误
#define BLOODROBOT_ERROR_ULTRASOUNDDEVICE_SCAN             401  // 超声波扫描错误
/// syringe dvice  error 500-599
#define BLOODROBOT_ERROR_SYRINGEDEVICE_BOOT                500  // 注射器启动错误
#define BLOODROBOT_ERROR_SYRINGEDEVICE_PUMP                501  // 注射器抽血错误

/// 定义错误码的错误等级
const map<int, int> g_erorr_code_level = {
	{BLOODROBOT_ERROR_SYSTEMDEVICE_BOOT,         ERROR_LEVEL_COMMON}
	,{BLOODROBOT_ERROR_ARMPLATEDEVICE_BOOT,      ERROR_LEVEL_COMMON}
	,{BLOODROBOT_ERROR_ARMPLATEDEVICE_BAND,      ERROR_LEVEL_COMMON}
	,{BLOODROBOT_ERROR_ARMPLATEDEVICE_LOOSEBAND, ERROR_LEVEL_COMMON}
	,{BLOODROBOT_ERROR_ULTRASOUNDDEVICE_BOOT,    ERROR_LEVEL_COMMON}
	,{BLOODROBOT_ERROR_ULTRASOUNDDEVICE_SCAN,    ERROR_LEVEL_COMMON}
	,{BLOODROBOT_ERROR_ROBOTARMDEVICE_BOOT,      ERROR_LEVEL_COMMON}
	,{BLOODROBOT_ERROR_ROBOTARMDEVICE_JOINT,     ERROR_LEVEL_COMMON}
	,{BLOODROBOT_ERROR_SYRINGEDEVICE_BOOT,       ERROR_LEVEL_COMMON}
	,{BLOODROBOT_ERROR_SYRINGEDEVICE_PUMP,       ERROR_LEVEL_COMMON}
};

inline int GetErrorLevel(int error_code)
{
	if (g_erorr_code_level.count(error_code))
	{
		return g_erorr_code_level.find(error_code)->second;
	}
	return ERROR_LEVEL_NONE;
}
