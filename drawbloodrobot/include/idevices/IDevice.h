#pragma once
/*****************************************************************//**
 * \file   IDevice.h
 * \brief  设备接口
 *
 * \author 蒋珂
 * \date   2023.05.14
 *********************************************************************/

#include <string>
#include <functional>
#include <memory>
using namespace std;
#include "../devicedefine.h"
#include "../eventdefine.h"


class IDevice
{
public:
	virtual ~IDevice() = 0 {};
	virtual int Open() = 0;
	virtual int Close() = 0;
	virtual const DeviceValue& GetDeviceValue() = 0;   // 设备的值包括编号、状态、错误码
};

