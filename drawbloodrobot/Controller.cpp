#include "Controller.h"
#include "ControllerUIAdapter.h"
#include "./statemachine/DeviceErrorHandler.h"
#include "./statemachine/DeviceErrorHandlerAbnormal.h"
#include "./statemachine/DeviceErrorHandlerNormal.h"
#include "./statemachine/DeviceOperaHandler.h"
#include "./statemachine/DeviceOperaHandlerAbnormal.h"
#include "./statemachine/DeviceOperaHandlerNormal.h"
#include "./statemachine/DeviceStateHandler.h"
#include "./statemachine/DeviceStateHandlerAbnormal.h"
#include "./statemachine/DeviceStateHandlerNormal.h"


int Controller::CreateDevices()
{
	LOG_INFO("CreateDevices");

	InitStatMachine();

	m_deviceevent.error_event = std::bind(&Controller::DeviceErrorEventReceiver, this, std::placeholders::_1);
	m_deviceevent.opera_event = std::bind(&Controller::DeviceOperaEventReceiver, this, std::placeholders::_1);
	m_deviceevent.state_event = std::bind(&Controller::DeviceStateEventReceiver, this, std::placeholders::_1);

	m_systemdevice = NewSystemDevice(SYSTEMDEVICE_NUM_0, m_deviceevent);
	
	/// 启动数据处理线程,开始处理所有事件，包括状态变化、操作、错误
	m_eventdata.Open([this](const shared_ptr<BloodRobotEvent>& event)->int {  return EventDistribute(event); });
	SetSystemState(DEVICE_STATE_NORMAL);
	if (m_systemdevice)
	{
		m_systemdevice->Open();
	}
	
	return 0;
}

int Controller::DestroyDevices()
{
	if (m_systemdevice)
	{
		m_systemdevice->Close();
		m_eventdata.Close();
		DeleteSystemDevice(m_systemdevice);
	}	

	return 0;
}

int Controller::AutoSetSystemState()
{
	bool alldevices_isnormal = DevicesIsNormal();
	if (alldevices_isnormal)
	{
		if (GetSystemState() == DEVICE_STATE_ABNORMAL)
		{
			SetSystemState(DEVICE_STATE_NORMAL);
		}
	}
	else
	{
		if (GetSystemState() != DEVICE_STATE_ABNORMAL)
		{
			SetSystemState(DEVICE_STATE_ABNORMAL);
		}
	}
	return 0;
}

int Controller::SetSystemState(int systemdevice_state)
{
	int errorcode = 0;
	if (m_systemdevice)
	{
		errorcode = m_systemdevice->SetSystemState(systemdevice_state);
	}
	return errorcode;
}

int Controller::GetSystemState()
{
	int systemstate = DEVICE_STATE_UNKNOWN;
	if (m_systemdevice)
	{
		systemstate = m_systemdevice->GetDeviceValue().device_state;
	}
	return systemstate;
}

bool Controller::DevicesIsNormal()
{
	bool all_normal = false;
	if (m_systemdevice)
	{
		all_normal = m_systemdevice->DevicesIsNormal();
	}
	return all_normal;
}

int Controller::InitStatMachine()
{
	/// 注册状态机
	DeviceStateHandler::instance().RegisterStateMachine(DEVICE_STATE_ABNORMAL,   &DeviceStateHandlerAbnormal::instance());
	DeviceStateHandler::instance().RegisterStateMachine(DEVICE_STATE_NORMAL,     &DeviceStateHandlerNormal::instance());
	DeviceStateHandler::instance().RegisterStateMachine(DEVICE_STATE_STANDBY,    &DeviceStateHandlerNormal::instance());
	DeviceStateHandler::instance().RegisterStateMachine(DEVICE_STATE_RUNNING,    &DeviceStateHandlerNormal::instance());
	DeviceStateHandler::instance().RegisterStateMachine(DEVICE_STATE_WORKING,    &DeviceStateHandlerNormal::instance());
	DeviceStateHandler::instance().RegisterStateMachine(DEVICE_STATE_MANUAL,     &DeviceStateHandlerNormal::instance());
	DeviceStateHandler::instance().RegisterStateMachine(DEVICE_STATE_URGENTSTOP, &DeviceStateHandlerNormal::instance());

	DeviceOperaHandler::instance().RegisterStateMachine(DEVICE_STATE_ABNORMAL,   &DeviceOperaHandlerAbnormal::instance());
	DeviceOperaHandler::instance().RegisterStateMachine(DEVICE_STATE_NORMAL,     &DeviceOperaHandlerNormal::instance());
	DeviceOperaHandler::instance().RegisterStateMachine(DEVICE_STATE_STANDBY,    &DeviceOperaHandlerNormal::instance());
	DeviceOperaHandler::instance().RegisterStateMachine(DEVICE_STATE_RUNNING,    &DeviceOperaHandlerNormal::instance());
	DeviceOperaHandler::instance().RegisterStateMachine(DEVICE_STATE_WORKING,    &DeviceOperaHandlerNormal::instance());
	DeviceOperaHandler::instance().RegisterStateMachine(DEVICE_STATE_MANUAL,     &DeviceOperaHandlerNormal::instance());
	DeviceOperaHandler::instance().RegisterStateMachine(DEVICE_STATE_URGENTSTOP, &DeviceOperaHandlerNormal::instance());
	
	DeviceErrorHandler::instance().RegisterStateMachine(DEVICE_STATE_ABNORMAL,   &DeviceErrorHandlerAbnormal::instance());
	DeviceErrorHandler::instance().RegisterStateMachine(DEVICE_STATE_NORMAL,     &DeviceErrorHandlerNormal::instance());
	DeviceErrorHandler::instance().RegisterStateMachine(DEVICE_STATE_STANDBY,    &DeviceErrorHandlerNormal::instance());
	DeviceErrorHandler::instance().RegisterStateMachine(DEVICE_STATE_RUNNING,    &DeviceErrorHandlerNormal::instance());
	DeviceErrorHandler::instance().RegisterStateMachine(DEVICE_STATE_WORKING,    &DeviceErrorHandlerNormal::instance());
	DeviceErrorHandler::instance().RegisterStateMachine(DEVICE_STATE_MANUAL,     &DeviceErrorHandlerNormal::instance());
	DeviceErrorHandler::instance().RegisterStateMachine(DEVICE_STATE_URGENTSTOP, &DeviceErrorHandlerNormal::instance());

	return 0;
}

int Controller::DeviceStateEventReceiver(const shared_ptr<DeviceStateEvent>& state_event)
{
	EventQueuePush(state_event);
	return 0;
}

int Controller::DeviceOperaEventReceiver(const shared_ptr<DeviceOperaEvent>& opera_event)
{
	EventQueuePush(opera_event);
	return 0;
}

int Controller::DeviceErrorEventReceiver(const shared_ptr<DeviceErrorEvent>& error_event)
{
	EventQueuePush(error_event);
	return 0;
}

int Controller::EventQueuePush(const shared_ptr<BloodRobotEvent>& event)
{
	int errorcode = m_eventdata.Producer(event);
	if (errorcode)
	{
		LOG_ERROR("Producer failed,  consumer thread no run");
	}
	if (m_eventdata.GetDataListSize() > 100)
	{
		LOG_WARN("queue data size > 100, size={}, data processing is too slow", m_eventdata.GetDataListSize());
	}
	return 0;
}

int Controller::EventDistribute(const shared_ptr<BloodRobotEvent>& event)
{
	switch (event->event_type)
	{
	case BLOODROBOT_EVENT_TYPE_STATE:
	{
		DeviceStateHandler::instance().DeviceStateHandle(reinterpret_cast<const shared_ptr<DeviceStateEvent>&>(event));
		break;
	}
	case BLOODROBOT_EVENT_TYPE_OPERA:
	{
		DeviceOperaHandler::instance().DeviceOperaHandle(reinterpret_cast<const shared_ptr<DeviceOperaEvent>&>(event));
		break;
	}
	case BLOODROBOT_EVENT_TYPE_ERROR:
	{
		DeviceErrorHandler::instance().DeviceErrorHandle(reinterpret_cast<const shared_ptr<DeviceErrorEvent>&>(event));
		break;
	}
	default:
		LOG_ERROR("event type error, cannot recognize event type={}", event->event_type);
		break;
	}
	return 0;
}

int Controller::NotifyUI(const shared_ptr<DeviceStateEvent>& state_event)
{
	ControllerUIAdapter::instance().NotifyUI(state_event);
	return 0;
}

int Controller::NotifyUI(const shared_ptr<DeviceOperaEvent>& opera_event)
{
	ControllerUIAdapter::instance().NotifyUI(opera_event);
	return 0;
}

int Controller::NotifyUI(const shared_ptr<DeviceErrorEvent>& error_event)
{
	ControllerUIAdapter::instance().NotifyUI(error_event);
	return 0;
}
