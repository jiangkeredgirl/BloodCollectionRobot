#pragma once
/*********************************************************************
 * \file   IDeviceErrorHandler.h
 * \brief  设备错误处理接口文件，每种设备一个错误处理接口. 
 * \author 蒋珂
 * \date   2023.05.27   
 *********************************************************************/
#include "../include/devicedefine.h"
#include "../include/eventdefine.h"
#include <memory>
using namespace std;

class IDeviceErrorHandler
{
public:
	virtual ~IDeviceErrorHandler() = 0 {};
	/// 状态机设备维护：一个设备对应一个函数，设备的增加、修改、删除，增删改以下函数
	virtual int SystemDeviceHandle(const shared_ptr<DeviceErrorEvent>& error_event) = 0;
	virtual int ArmPlateDeviceHandle(const shared_ptr<DeviceErrorEvent>& error_event) = 0;
	virtual int RobotArmDeviceHandle(const shared_ptr<DeviceErrorEvent>& error_event) = 0;
	virtual int UltrasoundDeviceHandle(const shared_ptr<DeviceErrorEvent>& error_event) = 0;
	virtual int SyringeDeviceHandle(const shared_ptr<DeviceErrorEvent>& error_event) = 0;	
};

