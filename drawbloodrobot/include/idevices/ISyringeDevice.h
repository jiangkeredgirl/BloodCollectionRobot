#pragma once
/*********************************************************************
 * \file   ISyringeDevice.h
 * \brief  注射器设备
 *
 * \author 蒋珂
 * \date   2023.05.14
 *********************************************************************/


#include "./IDevice.h"

class ISyringeDevice : public IDevice
{
	//扩展自己设备的接口函数
public:
	virtual int PumpBlood() = 0;   // 抽血
};

#ifdef __cplusplus
extern "C" {
#endif
	ISyringeDevice* NewSyringeDevice(int device_num, DeviceEvent device_event);
	//typedef ISyringeDevice* (*NewSyringeDeviceFun)(int device_num, DeviceEvent device_event);
	void DeleteSyringeDevice(ISyringeDevice* device);
	//typedef void(*DeleteSyringeDeviceFun)(ISyringeDevice* device);
#ifdef __cplusplus
}
#endif
