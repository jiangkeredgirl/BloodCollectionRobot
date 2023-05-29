#include "DeviceOperaHandlerNormal.h"
#include "../Controller.h"


int DeviceOperaHandlerNormal::SystemDeviceHandle(const shared_ptr<DeviceOperaEvent>& opera_event)
{
	Controller::instance().NotifyUI(opera_event);
	return 0;
}

int DeviceOperaHandlerNormal::ArmPlateDeviceHandle(const shared_ptr<DeviceOperaEvent>& opera_event)
{
	Controller::instance().NotifyUI(opera_event);
	return 0;
}

int DeviceOperaHandlerNormal::RobotArmDeviceHandle(const shared_ptr<DeviceOperaEvent>& opera_event)
{
	Controller::instance().NotifyUI(opera_event);
	return 0;
}

int DeviceOperaHandlerNormal::UltrasoundDeviceHandle(const shared_ptr<DeviceOperaEvent>& opera_event)
{
	Controller::instance().NotifyUI(opera_event);
	return 0;
}

int DeviceOperaHandlerNormal::SyringeDeviceHandle(const shared_ptr<DeviceOperaEvent>& opera_event)
{
	Controller::instance().NotifyUI(opera_event);
	return 0;
}