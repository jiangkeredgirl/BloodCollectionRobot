#pragma once
/*********************************************************************
 * \file   DeviceOperaHandler.h
 * \brief  设备操作处理类，是状态机的入口.
 * \author 蒋珂
 * \date   2023.05.27
 *********************************************************************/
#include "IDeviceOperaHandler.h"
#include <memory>
#include <map>
using namespace std;

class DeviceOperaHandler
{

public:
	static DeviceOperaHandler& instance()
	{
		static DeviceOperaHandler handler;
		return handler;
	}

public:
	int RegisterStateMachine(int systemdevice_state, IDeviceOperaHandler* statemachine);
	int DeviceOperaHandle(const shared_ptr<DeviceOperaEvent>& opera_event);
};