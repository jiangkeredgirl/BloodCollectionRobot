#pragma once
/*********************************************************************
 * \file   DeviceErrorHandlerAbnormal.h
 * \brief  状态机是异常状态，设备的错误处理.
 * \author 蒋珂
 * \date   2023.05.27
 *********************************************************************/
#include "IDeviceErrorHandler.h"
#include <memory>
using namespace std;

class DeviceErrorHandlerAbnormal : public IDeviceErrorHandler
{

public:
	static DeviceErrorHandlerAbnormal& instance()
	{
		static DeviceErrorHandlerAbnormal handler;
		return handler;
	}

public:
	virtual int SystemDeviceHandle(const shared_ptr<DeviceErrorEvent>& error_event) override;
	virtual int ArmPlateDeviceHandle(const shared_ptr<DeviceErrorEvent>& error_event) override;
	virtual int RobotArmDeviceHandle(const shared_ptr<DeviceErrorEvent>& error_event) override;
	virtual int UltrasoundDeviceHandle(const shared_ptr<DeviceErrorEvent>& error_event) override;
	virtual int SyringeDeviceHandle(const shared_ptr<DeviceErrorEvent>& error_event) override;
};