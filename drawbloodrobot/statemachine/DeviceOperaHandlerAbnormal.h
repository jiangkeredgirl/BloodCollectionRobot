#pragma once
/*********************************************************************
 * \file   DeviceOperaHandlerAbnormal.h
 * \brief  状态机是异常状态，设备的操作处理. 
 * \author 蒋珂
 * \date   2023.05.27   
 *********************************************************************/
#include "IDeviceOperaHandler.h"
#include <memory>
using namespace std;

class DeviceOperaHandlerAbnormal : public IDeviceOperaHandler
{

public:
	static DeviceOperaHandlerAbnormal& instance()
	{
		static DeviceOperaHandlerAbnormal handler;
		return handler;
	}

public:
	virtual int SystemDeviceHandle(const shared_ptr<DeviceOperaEvent>& opera_event) override;
	virtual int ArmPlateDeviceHandle(const shared_ptr<DeviceOperaEvent>& opera_event) override;
	virtual int RobotArmDeviceHandle(const shared_ptr<DeviceOperaEvent>& opera_event) override;
	virtual int UltrasoundDeviceHandle(const shared_ptr<DeviceOperaEvent>& opera_event) override;
	virtual int SyringeDeviceHandle(const shared_ptr<DeviceOperaEvent>& opera_event) override;


};

