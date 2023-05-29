#include "DeviceStateHandlerAbnormal.h"
#include "../Controller.h"


int DeviceStateHandlerAbnormal::SystemDeviceHandle(const shared_ptr<DeviceStateEvent>& state_event)
{
	Controller::instance().NotifyUI(state_event);
	return 0;
}

int DeviceStateHandlerAbnormal::ArmPlateDeviceHandle(const shared_ptr<DeviceStateEvent>& state_event)
{
	Controller::instance().NotifyUI(state_event);
	Controller::instance().AutoSetSystemState();
	return 0;
}

int DeviceStateHandlerAbnormal::RobotArmDeviceHandle(const shared_ptr<DeviceStateEvent>& state_event)
{
	Controller::instance().NotifyUI(state_event);
	Controller::instance().AutoSetSystemState();
	return 0;
}

int DeviceStateHandlerAbnormal::UltrasoundDeviceHandle(const shared_ptr<DeviceStateEvent>& state_event)
{
	Controller::instance().NotifyUI(state_event);
	Controller::instance().AutoSetSystemState();
	return 0;
}

int DeviceStateHandlerAbnormal::SyringeDeviceHandle(const shared_ptr<DeviceStateEvent>& state)
{
	Controller::instance().NotifyUI(state);
	Controller::instance().AutoSetSystemState();
	return 0;
}



