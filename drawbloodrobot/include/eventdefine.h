#pragma once
/*****************************************************************//**
 * \file   eventdefine.h
 * \brief  整个软件系统由事件驱动，此文件定义事件
 *
 * \author 蒋珂
 * \date   2023.05.08
 *********************************************************************/
#include <vector>
#include <map>
#include <iostream>
#include <string>
using namespace std;
#include "errorcode.h"
#include "devicedefine.h"
#include "LogWrapper.h"


/// 采血机器人事件类型，状态，操作，错误 3种
enum E_BLOODROBOT_EVENT_TYPE
{
	BLOODROBOT_EVENT_TYPE_UNKNOWN,  //< 未知事件类型
	BLOODROBOT_EVENT_TYPE_STATE,    //< 状态事件类型
	BLOODROBOT_EVENT_TYPE_OPERA,    //< 操作事件类型
	BLOODROBOT_EVENT_TYPE_ERROR     //< 错误事件类型
};

#include "numbermeaning.h"


/// 事件基类，所有的事件继承自该类
struct BloodRobotEvent
{
	int event_type = BLOODROBOT_EVENT_TYPE_UNKNOWN;
	string event_name = "BloodRobotEvent";
	int64_t event_time = GetNowDateTimeStamp();
	vector<pair<string/*router_name*/, int64_t/*router_time*/>>  event_router_time;
	DeviceValue device_value;
	BloodRobotEvent()
	{

	}
	virtual ~BloodRobotEvent() = 0
	{

	}
	virtual string EventStr() const
	{
		string str_router_time("");
		if (!event_router_time.empty())
		{
			str_router_time = ", route time:";
			for (auto item_time : event_router_time)
			{
				str_router_time += item_time.first + ":" + GetTimeString(item_time.second);
			}
		}

		return EventTypeStr(event_type)
			+ ", event_name:" + event_name
			+ ", event_time:" + GetTimeString(event_time)
			+ str_router_time
			+ ", " + DeviceValueStr(device_value);
	}
};

// 状态改变事件
struct DeviceStateEvent : public BloodRobotEvent
{
	int old_state = 0;
	int new_state = 0;
	DeviceStateEvent()
	{
		event_type = BLOODROBOT_EVENT_TYPE_STATE;
		//event_name = "DeviceStateEvent";
		event_name = typeid(*this).name();
	}
	virtual ~DeviceStateEvent()
	{

	}
	virtual string EventStr() const  override
	{
		return BloodRobotEvent::EventStr()
			+ ", old_state:" + DeviceStateStr(old_state)
			+ ", new_state:" + DeviceStateStr(new_state);
	}
};


// 操作事件
struct DeviceOperaEvent : public BloodRobotEvent
{
	int opera_code = 0;
	bool is_complete = false;
	DeviceOperaEvent()
	{
		event_type = BLOODROBOT_EVENT_TYPE_OPERA;
		event_name = typeid(*this).name();
	}
	virtual ~DeviceOperaEvent()
	{

	}
	virtual string EventStr() const  override
	{
		return BloodRobotEvent::EventStr()
			+ ", " + DeviceOperaStr(opera_code)
			+ ", is_complete:" + to_string(is_complete);
	}
};

struct SystemDeviceOperaEvent : public DeviceOperaEvent
{
	SystemDeviceOperaEvent()
	{
		event_name = typeid(*this).name();
	}
};


// 设备错误事件
struct DeviceErrorEvent : public BloodRobotEvent
{
	int error_level = 0;       // 错误等级
	int error_code = 0;       // 错误码
	bool error_clear = false;   // 错误是否清除
	DeviceErrorEvent()
	{
		event_type = BLOODROBOT_EVENT_TYPE_ERROR;
		event_name = typeid(*this).name();
	}
	virtual ~DeviceErrorEvent()
	{

	}
	virtual string EventStr() const  override
	{
		return BloodRobotEvent::EventStr()
			+ ", " + ErrorLevelStr(error_level)
			+ ", " + ErrorCodeStr(error_code)
			+ ", error_clear:" + to_string(error_clear);
	}
};


typedef std::function<int(const shared_ptr<DeviceStateEvent>& state_event)> DeviceStateEventF;
typedef std::function<int(const shared_ptr<DeviceOperaEvent>& opera_event)> DeviceOperaEventF;
typedef std::function<int(const shared_ptr<DeviceErrorEvent>& error_event)> DeviceErrorEventF;

struct DeviceEvent
{
	DeviceStateEventF state_event = nullptr;
	DeviceOperaEventF opera_event = nullptr;
	DeviceErrorEventF error_event = nullptr;
};

