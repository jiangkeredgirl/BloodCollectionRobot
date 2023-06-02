#pragma once
/*********************************************************************
 * \file   IArmPlateDevice.h
 * \brief  采血台设备接口
 *
 * \author 蒋珂
 * \date   2023.05.14
 *********************************************************************/

#include "./IDevice.h"

class IArmPlateDevice : public IDevice
{
	//扩展自己设备的接口函数
public:
	virtual int ArmBand() = 0;  // 手臂轧带
	virtual int ArmLooseBand() = 0;  // 手臂松开轧带

};

#ifdef __cplusplus
extern "C" {
#endif
	IArmPlateDevice* NewArmPlateDevice(int device_num, DeviceEvent device_event);
	void DeleteArmPlateDevice(IArmPlateDevice* device);
	IArmPlateDevice* NewArmPlateDeviceSim(int device_num, DeviceEvent device_event);
	void DeleteArmPlateDeviceSim(IArmPlateDevice* device);
#ifdef __cplusplus
}
#endif

