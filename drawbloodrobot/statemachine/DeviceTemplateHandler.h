#pragma once
/*********************************************************************
 * \file   DeviceTemplateHandler.h
 * \brief  设备状态、操作、错误事件处理模板，由于这3种（状态、操作、错误）处理逻辑完全一样，只是类型不一样.
 * \author 蒋珂
 * \date   2023.05.27
 *********************************************************************/

#include <memory>
#include <map>
using namespace std;

template<class IDeviceHandler, class DeviceEvent, class DeviceEventF>
class DeviceTemplateHandler
{

public:
	static DeviceTemplateHandler& instance()
	{
		static DeviceTemplateHandler handler;
		return handler;
	}

public:
	int RegisterStateMachine(int systemdevice_state, IDeviceHandler* statemachine)
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
			m_statemachine_func[statemachine][DEVICE_TYPE_SYSTEM]     = [statemachine](const shared_ptr<DeviceEvent>& state_event)->int {  return statemachine->SystemDeviceHandle(state_event); };
			m_statemachine_func[statemachine][DEVICE_TYPE_ARMPLATE]   = std::bind(&IDeviceHandler::ArmPlateDeviceHandle,   statemachine, std::placeholders::_1);
			m_statemachine_func[statemachine][DEVICE_TYPE_ROBOTARM]   = std::bind(&IDeviceHandler::RobotArmDeviceHandle,   statemachine, std::placeholders::_1);
			m_statemachine_func[statemachine][DEVICE_TYPE_ULTRASOUND] = std::bind(&IDeviceHandler::UltrasoundDeviceHandle, statemachine, std::placeholders::_1);
			m_statemachine_func[statemachine][DEVICE_TYPE_SYRINGE]    = std::bind(&IDeviceHandler::SyringeDeviceHandle,    statemachine, std::placeholders::_1);
			error_code = 0;
		} while (false);
		return error_code;
	}
	int DeviceHandle(const shared_ptr<DeviceEvent>& device_event)
	{
		int error_code = BLOODROBOT_ERRORCODE_UNKNOWN;
		do
		{
			if (device_event == nullptr)
			{
				LOG_ERROR("device_event == nullptr");
				break;
			}
			int system_state = Controller::instance().GetSystemState();
			if (m_statemachine.count(system_state) == 0)
			{
				LOG_ERROR("m_statemachine.count(system_state) == 0");
				break;
			}
			IDeviceHandler* statemachine = m_statemachine[system_state];
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
			if (m_statemachine_func[statemachine].count(device_event->device_value.device_type) == 0)
			{
				LOG_ERROR("m_statemachine_func[statemachine].count(device_event->device_value.device_type) == 0");
				break;
			}
			DeviceEventF event_handle = m_statemachine_func[statemachine][device_event->device_value.device_type];
			if (event_handle == nullptr)
			{
				LOG_ERROR("event_handle == nullptr");
				break;
			}
			error_code = event_handle(device_event);
		} while (false);
		return error_code;
	}

private:
	map<int/*systemdevice_state*/, IDeviceHandler*/*statemachine*/>         m_statemachine;
	map<IDeviceHandler*, map<int/*device type*/, DeviceEventF/*func*/>>     m_statemachine_func;
};

