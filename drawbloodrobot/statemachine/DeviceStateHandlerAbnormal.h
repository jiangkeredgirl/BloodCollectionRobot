#pragma once
/*********************************************************************
 * \file   DeviceStateNormalHandler.h
 * \brief  状态机是异常状态，设备的状态变化处理.
 * \author 蒋珂
 * \date   2023.05.27
 *********************************************************************/
#include "IDeviceStateHandler.h"

class DeviceStateHandlerAbnormal :	public IDeviceStateHandler
{

public:
	static DeviceStateHandlerAbnormal& instance()
	{
		static DeviceStateHandlerAbnormal handler;
		return handler;
	}

public:
	virtual int SystemDeviceHandle(const shared_ptr<DeviceStateEvent>& state) override;
	virtual int ArmPlateDeviceHandle(const shared_ptr<DeviceStateEvent>& state) override;
	virtual int RobotArmDeviceHandle(const shared_ptr<DeviceStateEvent>& state) override;
	virtual int UltrasoundDeviceHandle(const shared_ptr<DeviceStateEvent>& state) override;
	virtual int SyringeDeviceHandle(const shared_ptr<DeviceStateEvent>& state) override;	
};

