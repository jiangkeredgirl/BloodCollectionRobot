#pragma once
/*********************************************************************
 * \file   DeviceStateHandler.h
 * \brief  设备状态变化处理类，是状态机的入口. 
 * \author 蒋珂
 * \date   2023.05.27   
 *********************************************************************/
#include "IDeviceStateHandler.h"
#include <memory>
#include <map>
using namespace std;

class DeviceStateHandler
{

public:
	static DeviceStateHandler& instance()
	{
		static DeviceStateHandler handler;
		return handler;
	}

public:
	int RegisterStateMachine(int systemdevice_state, IDeviceStateHandler* statemachine);
	int DeviceStateHandle(const shared_ptr<DeviceStateEvent>& state_event);	

#if 0
private:
	map<int/*systemdevice_state*/, IDeviceStateHandler*/*statemachine*/>     m_statemachine;
	map<IDeviceStateHandler*
		, map<int/*device type*/, DeviceStateEventF/*func*/>>     m_statemachine_func;
#endif
};

