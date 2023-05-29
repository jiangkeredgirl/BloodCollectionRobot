#pragma once
/*********************************************************************
 * \file   DeviceErrorHandler.h
 * \brief  设备错误处理类，是状态机的入口.
 * \author 蒋珂
 * \date   2023.05.27
 *********************************************************************/
#include "IDeviceErrorHandler.h"
#include <memory>
#include <map>
using namespace std;

class DeviceErrorHandler
{

public:
	static DeviceErrorHandler& instance()
	{
		static DeviceErrorHandler handler;
		return handler;
	}

public:
	int RegisterStateMachine(int systemdevice_state, IDeviceErrorHandler* statemachine);
	int DeviceErrorHandle(const shared_ptr<DeviceErrorEvent>& error_event);
};