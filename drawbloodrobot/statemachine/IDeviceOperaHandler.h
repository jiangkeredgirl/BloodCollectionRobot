#pragma once
/*********************************************************************
 * \file   IDeviceOperaHandler.h
 * \brief  设备操作事件处理接口文件，一种设备一个接口. 
 * \author 蒋珂
 * \date   2023.05.27   
 *********************************************************************/
#include "../include/devicedefine.h"
#include "../include/eventdefine.h"
#include <memory>
using namespace std;

class IDeviceOperaHandler
{
public:
	virtual int SystemDeviceHandle(const shared_ptr<DeviceOperaEvent>& opera_event) = 0;
	virtual int ArmPlateDeviceHandle(const shared_ptr<DeviceOperaEvent>& opera_event) = 0;
	virtual int RobotArmDeviceHandle(const shared_ptr<DeviceOperaEvent>& opera_event) = 0;
	virtual int UltrasoundDeviceHandle(const shared_ptr<DeviceOperaEvent>& opera_event) = 0;
	virtual int SyringeDeviceHandle(const shared_ptr<DeviceOperaEvent>& opera_event) = 0;
};
