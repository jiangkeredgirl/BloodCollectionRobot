#pragma once
/*****************************************************************//**
 * \file   IUltrasoundDevice.h
 * \brief  超声波设备
 * 
 * \author 蒋珂
 * \date   2023.05.14   
 *********************************************************************/

#include "./IDevice.h"

class IUltrasoundDevice : public IDevice
{
    //扩展自己设备的接口函数
public:
    virtual int ScanBlood() = 0;  // 扫描血管

};

#ifdef __cplusplus
extern "C" {
#endif
	IUltrasoundDevice* NewUltrasoundDevice(int device_num, DeviceEvent device_event);
	void DeleteUltrasoundDevice(IUltrasoundDevice* device);
	IUltrasoundDevice* NewUltrasoundDeviceSim(int device_num, DeviceEvent device_event);
	void DeleteUltrasoundDeviceSim(IUltrasoundDevice* device);
#ifdef __cplusplus
}
#endif
