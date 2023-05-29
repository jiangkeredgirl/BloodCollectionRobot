#include "DeviceErrorHandlerAbnormal.h"
#include "../Controller.h"


int DeviceErrorHandlerAbnormal::SystemDeviceHandle(const shared_ptr<DeviceErrorEvent>& error_event)
{
	Controller::instance().NotifyUI(error_event);
	return 0;
}

int DeviceErrorHandlerAbnormal::ArmPlateDeviceHandle(const shared_ptr<DeviceErrorEvent>& error_event)
{
	Controller::instance().NotifyUI(error_event);
	return 0;
}

int DeviceErrorHandlerAbnormal::RobotArmDeviceHandle(const shared_ptr<DeviceErrorEvent>& error_event)
{
	Controller::instance().NotifyUI(error_event);
	return 0;
}

int DeviceErrorHandlerAbnormal::UltrasoundDeviceHandle(const shared_ptr<DeviceErrorEvent>& error_event)
{
	Controller::instance().NotifyUI(error_event);
	return 0;
}

int DeviceErrorHandlerAbnormal::SyringeDeviceHandle(const shared_ptr<DeviceErrorEvent>& error_event)
{
	Controller::instance().NotifyUI(error_event);
	return 0;
}