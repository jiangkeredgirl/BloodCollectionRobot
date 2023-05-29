#include "DeviceStateHandler.h"
#include "../include/LogWrapper.h"
#include "../Controller.h"
#include "DeviceTemplateHandler.h"

#if 0
int DeviceStateHandler::RegisterStateMachine(int systemdevice_state, IDeviceStateHandler* statemachine)
{
	int error_code = 1;
	do
	{
		if (statemachine == nullptr)
		{
			LOG_ERROR("state_machine == nullptr");
			break;
		}
		if (m_statemachine.count(systemdevice_state))
		{
			LOG_WARN("this state machine haved registered, systemdevice_state = {}", systemdevice_state, DeviceStateStr(systemdevice_state));
		}
		m_statemachine[systemdevice_state] = statemachine;
		m_statemachine_func[statemachine][DEVICE_TYPE_SYSTEM]     = [statemachine](const shared_ptr<DeviceStateEvent>& state_event)->int {  return statemachine->SystemDeviceHandle(state_event); };
		m_statemachine_func[statemachine][DEVICE_TYPE_ARMPLATE]   = std::bind(&IDeviceStateHandler::ArmPlateDeviceHandle,   statemachine, std::placeholders::_1);
		m_statemachine_func[statemachine][DEVICE_TYPE_ROBOTARM]   = std::bind(&IDeviceStateHandler::RobotArmDeviceHandle,   statemachine, std::placeholders::_1);
		m_statemachine_func[statemachine][DEVICE_TYPE_ULTRASOUND] = std::bind(&IDeviceStateHandler::UltrasoundDeviceHandle, statemachine, std::placeholders::_1);		
        m_statemachine_func[statemachine][DEVICE_TYPE_SYRINGE]    = std::bind(&IDeviceStateHandler::SyringeDeviceHandle,    statemachine, std::placeholders::_1);
		error_code = 0;
	} while (false);
	return error_code;
}

int DeviceStateHandler::DeviceStateHandle(const shared_ptr<DeviceStateEvent>& state_event)
{
	int error_code = BLOODROBOT_ERRORCODE_UNKNOWN;
	do
	{
		if (state_event == nullptr)
		{
			LOG_ERROR("state_event == nullptr");
			break;
		}
		int system_state = Controller::instance().GetSystemState();
		if (m_statemachine.count(system_state) == 0)
		{
			LOG_ERROR("m_statemachine.count(system_state) == 0");
			break;
		}
		IDeviceStateHandler* statemachine = m_statemachine[system_state];
		if (statemachine == nullptr)
		{
			LOG_ERROR("statemachine == nullptr");
			break;
		}
		if (m_statemachine_func.count(statemachine) == 0)
		{
			LOG_ERROR("m_state_machine_func.count(machine) == 0");
			break;
		}
		if (m_statemachine_func[statemachine].count(state_event->device_value.device_type) == 0)
		{
			LOG_ERROR("m_statemachine_func[statemachine].count(state_event->device_value.device_type) == 0");
			break;
		}
		DeviceStateEventF state_handle = m_statemachine_func[statemachine][state_event->device_value.device_type];
		if (state_handle == nullptr)
		{
			LOG_ERROR("state_handle == nullptr");
			break;
		}
		error_code = state_handle(state_event);
	} while (false);	
	return error_code;
}
#endif

int DeviceStateHandler::RegisterStateMachine(int systemdevice_state, IDeviceStateHandler* statemachine)
{
	return DeviceTemplateHandler<IDeviceStateHandler, DeviceStateEvent, DeviceStateEventF>::instance().RegisterStateMachine(systemdevice_state, statemachine);
}

int DeviceStateHandler::DeviceStateHandle(const shared_ptr<DeviceStateEvent>& state_event)
{
	return DeviceTemplateHandler<IDeviceStateHandler, DeviceStateEvent, DeviceStateEventF>::instance().DeviceHandle(state_event);
}
