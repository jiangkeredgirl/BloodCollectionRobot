#pragma once
/*****************************************************************//**
 * \file   numbermeaning.h
 * \brief  将一些数字，宏定义转换成有意义字符串，在log里方便阅读
 *
 * \author 蒋珂
 * \date   2023.05.08
 *********************************************************************/
#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <strstream>
using namespace std;

// 输出枚举
#define STR_ENUM(name, value)        return ((string(#name) + ":" + #value));
#define STR_ENUM_CASE(name, value, ...)   case value: return ((string(#name) + ":" + #value + string(__VA_ARGS__)));break;


inline string DeviceTypeStr(int dvice_type)
{
	switch (dvice_type)
	{
		STR_ENUM_CASE(dvice_type, DEVICE_TYPE_UNKNOWN);
		STR_ENUM_CASE(dvice_type, DEVICE_TYPE_SYSTEM);
		STR_ENUM_CASE(dvice_type, DEVICE_TYPE_ARMPLATE);
		STR_ENUM_CASE(dvice_type, DEVICE_TYPE_ULTRASOUND);
		STR_ENUM_CASE(dvice_type, DEVICE_TYPE_ROBOTARM);
		STR_ENUM_CASE(dvice_type, DEVICE_TYPE_SYRINGE);
	default:
		return("warn:dvice_type:" + to_string(dvice_type) + " unknown");
		break;
	}
	return "";
}

inline string DeviceStateStr(int device_state)
{
	switch (device_state)
	{
		STR_ENUM_CASE(device_state, DEVICE_STATE_UNKNOWN);
		STR_ENUM_CASE(device_state, DEVICE_STATE_NORMAL);
		STR_ENUM_CASE(device_state, DEVICE_STATE_ABNORMAL);
		STR_ENUM_CASE(device_state, DEVICE_STATE_STANDBY);
		STR_ENUM_CASE(device_state, DEVICE_STATE_RUNNING);
		STR_ENUM_CASE(device_state, DEVICE_STATE_WORKING);
		STR_ENUM_CASE(device_state, DEVICE_STATE_MANUAL);
		STR_ENUM_CASE(device_state, DEVICE_STATE_URGENTSTOP);
		STR_ENUM_CASE(device_state, DEVICE_STATE_END);
	default:
		return("warn:device_state:" + to_string(device_state) + " unknown");
		break;
	}
	return "";
}

inline string DeviceOperaStr(int device_opera)
{
	switch (device_opera)
	{
		STR_ENUM_CASE(device_opera, SYSTEMDEVICE_OPERA_UNKNOWN);
		STR_ENUM_CASE(device_opera, SYSTEMDEVICE_OPERA_BOOT);
		STR_ENUM_CASE(device_opera, SYSTEMDEVICE_OPERA_SHUTDOWN);
		STR_ENUM_CASE(device_opera, SYSTEMDEVICE_OPERA_MANUAL);
		STR_ENUM_CASE(device_opera, SYSTEMDEVICE_OPERA_URGENTSTOP);
		STR_ENUM_CASE(device_opera, SYSTEMDEVICE_OPERA_END);
		STR_ENUM_CASE(device_opera, ARMPLATEDEVICE_OPERA_UNKNOWN);
		STR_ENUM_CASE(device_opera, ARMPLATEDEVICE_OPERA_ARMFIXED);
		STR_ENUM_CASE(device_opera, ARMPLATEDEVICE_OPERA_ARMUNFIXED);
		STR_ENUM_CASE(device_opera, ARMPLATEDEVICE_OPERA_BAND);
		STR_ENUM_CASE(device_opera, ARMPLATEDEVICE_OPERA_LOOSEBAND);
		STR_ENUM_CASE(device_opera, ARMPLATEDEVICE_OPERA_END);
		STR_ENUM_CASE(device_opera, ULTRASOUNDDEVICE_OPERA_UNKNOWN);
		STR_ENUM_CASE(device_opera, ULTRASOUNDDEVICE_OPERA_SCAN);
		STR_ENUM_CASE(device_opera, ULTRASOUNDDEVICE_OPERA_SCANCOMPLETE);
		STR_ENUM_CASE(device_opera, ULTRASOUNDDEVICE_OPERA_END);
		STR_ENUM_CASE(device_opera, ROBOTARMDEVICE_OPERA_UNKNOWN);
		STR_ENUM_CASE(device_opera, ROBOTARMDEVICE_OPERA_NEEDLEPOS);
		STR_ENUM_CASE(device_opera, ROBOTARMDEVICE_OPERA_END);
		STR_ENUM_CASE(device_opera, SYRINGEDEVICE_OPERA_UNKNOWN);
		STR_ENUM_CASE(device_opera, SYRINGEDEVICE_OPERA_PUMP);
		STR_ENUM_CASE(device_opera, SYRINGEDEVICE_OPERA_PUMPPOS);
		STR_ENUM_CASE(device_opera, SYRINGEDEVICE_OPERA_END);
	default:
		return("warn:device_opera:" + to_string(device_opera) + " unknown");
		break;
	}
	return "";
}

inline string DeviceNumStr(int device_type, int device_num)
{
	switch (device_type)
	{
	default:
		return "device_num:" + to_string(device_num);
		break;
	}
	return "";
}

inline string EventTypeStr(int event_type)
{
	switch (event_type)
	{
		STR_ENUM_CASE(event_type, BLOODROBOT_EVENT_TYPE_UNKNOWN);
		STR_ENUM_CASE(event_type, BLOODROBOT_EVENT_TYPE_STATE);
		STR_ENUM_CASE(event_type, BLOODROBOT_EVENT_TYPE_OPERA);
		STR_ENUM_CASE(event_type, BLOODROBOT_EVENT_TYPE_ERROR);
	default:
		return("warn:event_type:" + to_string(event_type) + " unknown");
		break;
	}
	return "";
}


inline string ErrorLevelStr(int error_level)
{
	switch (error_level)
	{
		STR_ENUM_CASE(error_level, ERROR_LEVEL_NONE);
		STR_ENUM_CASE(error_level, ERROR_LEVEL_WARN);
		STR_ENUM_CASE(error_level, ERROR_LEVEL_COMMON);
		STR_ENUM_CASE(error_level, ERROR_LEVEL_FATAL);
	default:
		return("warn:error_level:" + to_string(error_level) + " unknown");
		break;
	}
	return "";
}

inline string ErrorCodeStr(int error_code)
{
	switch (error_code)
	{
		STR_ENUM_CASE(error_code, BLOODROBOT_ERRORCODE_OK);
		STR_ENUM_CASE(error_code, BLOODROBOT_ERRORCODE_UNKNOWN);
		STR_ENUM_CASE(error_code, BLOODROBOT_ERROR_SYSTEMDEVICE_BOOT);
		STR_ENUM_CASE(error_code, BLOODROBOT_ERROR_ARMPLATEDEVICE_BOOT);
		STR_ENUM_CASE(error_code, BLOODROBOT_ERROR_ARMPLATEDEVICE_BAND);
		STR_ENUM_CASE(error_code, BLOODROBOT_ERROR_ARMPLATEDEVICE_LOOSEBAND);
		STR_ENUM_CASE(error_code, BLOODROBOT_ERROR_ULTRASOUNDDEVICE_BOOT);
		STR_ENUM_CASE(error_code, BLOODROBOT_ERROR_ULTRASOUNDDEVICE_SCAN);
		STR_ENUM_CASE(error_code, BLOODROBOT_ERROR_ROBOTARMDEVICE_BOOT);
		STR_ENUM_CASE(error_code, BLOODROBOT_ERROR_ROBOTARMDEVICE_JOINT);
		STR_ENUM_CASE(error_code, BLOODROBOT_ERROR_SYRINGEDEVICE_BOOT);
		STR_ENUM_CASE(error_code, BLOODROBOT_ERROR_SYRINGEDEVICE_PUMP);
	default:
		return("warn:error_code:" + to_string(error_code) + " unknown");
		break;
	}
	return "";
}

inline string DeviceValueStr(const DeviceValue& device_value)
{
	string ss("device_value:\n");
	ss = ss + "device_name:" + device_value.device_name + "\n";
	ss = ss + DeviceTypeStr(device_value.device_type) + "\n";
	ss = ss + DeviceNumStr(device_value.device_type, device_value.device_num) + "\n";
	ss = ss + DeviceStateStr(device_value.device_state) + "\n";
	ss = ss + ErrorLevelStr(device_value.error_level) + "\n";
	ss = ss + ErrorCodeStr(device_value.error_code);
	return ss;
}


