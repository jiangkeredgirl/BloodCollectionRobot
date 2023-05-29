#include "DeviceOperaHandler.h"
#include "../include/LogWrapper.h"
#include "../Controller.h"
#include "DeviceTemplateHandler.h"

int DeviceOperaHandler::RegisterStateMachine(int systemdevice_state, IDeviceOperaHandler* statemachine)
{
	return DeviceTemplateHandler<IDeviceOperaHandler, DeviceOperaEvent, DeviceOperaEventF>::instance().RegisterStateMachine(systemdevice_state, statemachine);
}

int DeviceOperaHandler::DeviceOperaHandle(const shared_ptr<DeviceOperaEvent>& opera_event) 
{
	return DeviceTemplateHandler<IDeviceOperaHandler, DeviceOperaEvent, DeviceOperaEventF>::instance().DeviceHandle(opera_event);
}