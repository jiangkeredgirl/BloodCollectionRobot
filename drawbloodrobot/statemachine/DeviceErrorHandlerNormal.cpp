#include "DeviceErrorHandlerNormal.h"
#include "../Controller.h"


int DeviceErrorHandlerNormal::SystemDeviceHandle(const shared_ptr<DeviceErrorEvent>& error_event)
{
	Controller::instance().NotifyUI(error_event);
	return 0;
}

int DeviceErrorHandlerNormal::ArmPlateDeviceHandle(const shared_ptr<DeviceErrorEvent>& error_event)
{
	Controller::instance().NotifyUI(error_event);
	return 0;
}

int DeviceErrorHandlerNormal::RobotArmDeviceHandle(const shared_ptr<DeviceErrorEvent>& error_event)
{
	Controller::instance().NotifyUI(error_event);
	return 0;
}

int DeviceErrorHandlerNormal::UltrasoundDeviceHandle(const shared_ptr<DeviceErrorEvent>& error_event)
{
	Controller::instance().NotifyUI(error_event);
	return 0;
}

int DeviceErrorHandlerNormal::SyringeDeviceHandle(const shared_ptr<DeviceErrorEvent>& error_event)
{
	Controller::instance().NotifyUI(error_event);
	return 0;
}