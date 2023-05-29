#include "DeviceStateHandlerNormal.h"
#include "../Controller.h"


int DeviceStateHandlerNormal::SystemDeviceHandle(const shared_ptr<DeviceStateEvent>& state_event)
{
	Controller::instance().NotifyUI(state_event);
	return 0;
}

int DeviceStateHandlerNormal::ArmPlateDeviceHandle(const shared_ptr<DeviceStateEvent>& state_event)
{
	Controller::instance().NotifyUI(state_event);
	Controller::instance().AutoSetSystemState();
	return 0;
}

int DeviceStateHandlerNormal::RobotArmDeviceHandle(const shared_ptr<DeviceStateEvent>& state_event)
{
	Controller::instance().NotifyUI(state_event);
	Controller::instance().AutoSetSystemState();
	return 0;
}

int DeviceStateHandlerNormal::UltrasoundDeviceHandle(const shared_ptr<DeviceStateEvent>& state_event)
{
	Controller::instance().NotifyUI(state_event);
	Controller::instance().AutoSetSystemState();
	return 0;
}

int DeviceStateHandlerNormal::SyringeDeviceHandle(const shared_ptr<DeviceStateEvent>& state_event)
{
	Controller::instance().NotifyUI(state_event);
	Controller::instance().AutoSetSystemState();
	return 0;
}