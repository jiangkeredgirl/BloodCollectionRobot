#include "DeviceOperaHandlerAbnormal.h"
#include "../Controller.h"


int DeviceOperaHandlerAbnormal::SystemDeviceHandle(const shared_ptr<DeviceOperaEvent>& opera_event)
{
	Controller::instance().NotifyUI(opera_event);
	return 0;
}

int DeviceOperaHandlerAbnormal::ArmPlateDeviceHandle(const shared_ptr<DeviceOperaEvent>& opera_event)
{
	Controller::instance().NotifyUI(opera_event);
	return 0;
}

int DeviceOperaHandlerAbnormal::RobotArmDeviceHandle(const shared_ptr<DeviceOperaEvent>& opera_event)
{
	Controller::instance().NotifyUI(opera_event);
	return 0;
}

int DeviceOperaHandlerAbnormal::UltrasoundDeviceHandle(const shared_ptr<DeviceOperaEvent>& opera_event)
{
	Controller::instance().NotifyUI(opera_event);
	return 0;
}

int DeviceOperaHandlerAbnormal::SyringeDeviceHandle(const shared_ptr<DeviceOperaEvent>& opera_event)
{
	Controller::instance().NotifyUI(opera_event);
	return 0;
}