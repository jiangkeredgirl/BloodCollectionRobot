#include "DeviceErrorHandler.h"
#include "../include/LogWrapper.h"
#include "../Controller.h"
#include "DeviceTemplateHandler.h"

int DeviceErrorHandler::RegisterStateMachine(int systemdevice_state, IDeviceErrorHandler* statemachine)
{
	return DeviceTemplateHandler<IDeviceErrorHandler, DeviceErrorEvent, DeviceErrorEventF>::instance().RegisterStateMachine(systemdevice_state, statemachine);
}

int DeviceErrorHandler::DeviceErrorHandle(const shared_ptr<DeviceErrorEvent>& error_event)
{
	return DeviceTemplateHandler<IDeviceErrorHandler, DeviceErrorEvent, DeviceErrorEventF>::instance().DeviceHandle(error_event);
}