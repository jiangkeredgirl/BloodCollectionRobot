#pragma once
/*********************************************************************
 * \file   ISystemDevice.h
 * \brief  采血机器人系统设备
 *
 * \author 蒋珂
 * \date   2023.05.14
 *********************************************************************/

#include "./IDevice.h"

class ISystemDevice : public IDevice
{
public:
	virtual int SetManual() = 0;     // 设置手动模式
	// 紧急停止，作为医疗设备，时刻检查系统状态，有任何不稳定，将会自动立即停止工作
	// 此函数将人工紧急停止设备
	virtual int UrgentStop() = 0;
	// 设置状态，状态的变化会影响状态机的调用
	virtual int SetSystemState(int state) = 0;
	// 所有设备是否正常
	virtual bool DevicesIsNormal() = 0;

};

#ifdef __cplusplus
extern "C" {
#endif
	ISystemDevice* NewSystemDevice(int device_num, DeviceEvent device_event);
	//typedef ISystemDevice* (*NewSystemDeviceFun)(int device_count, DeviceEvent device_event);
	void DeleteSystemDevice(ISystemDevice* device);
	//typedef void(*DeleteSystemDeviceFun)(ISystemDevice* device);
#ifdef __cplusplus
}
#endif
