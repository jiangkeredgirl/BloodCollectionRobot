#pragma once
/*********************************************************************
 * \file   IRobotArmDevice.h
 * \brief  机械臂设备
 *
 * \author 蒋珂
 * \date   2023.05.14
 *********************************************************************/

#include "./IDevice.h"

class IRobotArmDevice : public IDevice
{
	//扩展自己设备的接口函数
public:
	virtual int MovePos(RobotArmDevicePos dest_pos) = 0;  // 控制机械臂

};

#ifdef __cplusplus
extern "C" {
#endif
	IRobotArmDevice* NewRobotArmDevice(int device_num, DeviceEvent device_event);
	//typedef IRobotArmDevice* (*NewRobotArmDeviceFun)(int device_num, DeviceEvent device_event);
	void DeleteRobotArmDevice(IRobotArmDevice* device);
	//typedef void(*DeleteRobotArmDeviceFun)(IRobotArmDevice* device);
#ifdef __cplusplus
}
#endif
