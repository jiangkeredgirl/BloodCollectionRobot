#include "ControllerUIAdapter.h"
#include "Controller.h"
#include "./include/LogWrapper.h"
#include <functional>


ControllerUIAdapter::ControllerUIAdapter(QObject *parent)
	: QObject(parent)
{
	qRegisterMetaType<shared_ptr<DeviceStateEvent>>("shared_ptr<DeviceStateEvent>");
	qRegisterMetaType<shared_ptr<DeviceOperaEvent>>("shared_ptr<DeviceOperaEvent>");
	qRegisterMetaType<shared_ptr<DeviceErrorEvent>>("shared_ptr<DeviceErrorEvent>");
 
	m_device_notifyui[DEVICE_TYPE_SYSTEM].state_event = BIND_STATE_EVENT_TO_UI(SystemDeviceUI);
	m_device_notifyui[DEVICE_TYPE_SYSTEM].error_event = BIND_ERROR_EVENT_TO_UI(SystemDeviceUI);
	m_device_notifyui[DEVICE_TYPE_SYSTEM].opera_event = BIND_OPERA_EVENT_TO_UI(SystemDeviceUI);

	m_device_notifyui[DEVICE_TYPE_ARMPLATE].state_event = BIND_STATE_EVENT_TO_UI(ArmPlateDeviceUI);
	m_device_notifyui[DEVICE_TYPE_ARMPLATE].error_event = BIND_ERROR_EVENT_TO_UI(ArmPlateDeviceUI);
	m_device_notifyui[DEVICE_TYPE_ARMPLATE].opera_event = BIND_OPERA_EVENT_TO_UI(ArmPlateDeviceUI);

	m_device_notifyui[DEVICE_TYPE_ROBOTARM].state_event = BIND_STATE_EVENT_TO_UI(RobotArmDeviceUI);
	m_device_notifyui[DEVICE_TYPE_ROBOTARM].error_event = BIND_ERROR_EVENT_TO_UI(RobotArmDeviceUI);
	m_device_notifyui[DEVICE_TYPE_ROBOTARM].opera_event = BIND_OPERA_EVENT_TO_UI(RobotArmDeviceUI);

	m_device_notifyui[DEVICE_TYPE_ULTRASOUND].state_event = BIND_STATE_EVENT_TO_UI(UltrasoundDeviceUI);
	m_device_notifyui[DEVICE_TYPE_ULTRASOUND].error_event = BIND_ERROR_EVENT_TO_UI(UltrasoundDeviceUI);
	m_device_notifyui[DEVICE_TYPE_ULTRASOUND].opera_event = BIND_OPERA_EVENT_TO_UI(UltrasoundDeviceUI);

	m_device_notifyui[DEVICE_TYPE_SYRINGE].state_event = BIND_STATE_EVENT_TO_UI(SyringeDeviceUI);
	m_device_notifyui[DEVICE_TYPE_SYRINGE].error_event = BIND_ERROR_EVENT_TO_UI(SyringeDeviceUI);
	m_device_notifyui[DEVICE_TYPE_SYRINGE].opera_event = BIND_OPERA_EVENT_TO_UI(SyringeDeviceUI);
	
}

ControllerUIAdapter::~ControllerUIAdapter()
{}

int ControllerUIAdapter::CreateDevices()
{
	return Controller::instance().CreateDevices();
}

int ControllerUIAdapter::DestroyDevices()
{
	return Controller::instance().DestroyDevices();
}


int ControllerUIAdapter::NotifyUI(const shared_ptr<DeviceStateEvent>& state_event)
{
	int error_code = 1;
	if (state_event)
	{
		if (m_device_notifyui.count(state_event->device_value.device_type))
		{
			error_code = m_device_notifyui.find(state_event->device_value.device_type)->second.state_event(state_event);
		}
		else
		{
			LOG_ERROR("undefine device type:{}", DeviceTypeStr(state_event->device_value.device_type));
		}
	}
	return error_code;
}

int ControllerUIAdapter::NotifyUI(const shared_ptr<DeviceOperaEvent>& opera_event)
{
	int error_code = 1;
	if (opera_event)
	{
		if (m_device_notifyui.count(opera_event->device_value.device_type))
		{
			error_code = m_device_notifyui.find(opera_event->device_value.device_type)->second.opera_event(opera_event);
		}
		else
		{
			LOG_ERROR("undefine device type:{}", DeviceTypeStr(opera_event->device_value.device_type));
		}
	}
	return error_code;
}

int ControllerUIAdapter::NotifyUI(const shared_ptr<DeviceErrorEvent>& error_event)
{
	int error_code = 1;
	if (error_event)
	{
		if (m_device_notifyui.count(error_event->device_value.device_type))
		{
			error_code = m_device_notifyui.find(error_event->device_value.device_type)->second.error_event(error_event);
		}
		else
		{
			LOG_ERROR("undefine device type:{}", DeviceTypeStr(error_event->device_value.device_type));
		}
	}
	return error_code;
}

int ControllerUIAdapter::NotifySystemDeviceUI(const shared_ptr<DeviceStateEvent>& state_event)
{
	emit SignalSystemDeviceUI(state_event);
	return 0;
}
int ControllerUIAdapter::NotifySystemDeviceUI(const shared_ptr<DeviceOperaEvent>& opera_event)
{
	emit SignalSystemDeviceUI(opera_event);
	return 0;
}
int ControllerUIAdapter::NotifySystemDeviceUI(const shared_ptr<DeviceErrorEvent>& error_event)
{
	emit SignalSystemDeviceUI(error_event);
	return 0;
}

int ControllerUIAdapter::NotifyArmPlateDeviceUI(const shared_ptr<DeviceStateEvent>& state_event)
{
	emit SignalArmPlateDeviceUI(state_event);
	return 0;
}
int ControllerUIAdapter::NotifyArmPlateDeviceUI(const shared_ptr<DeviceOperaEvent>& opera_event)
{
	emit SignalArmPlateDeviceUI(opera_event);
	return 0;
}
int ControllerUIAdapter::NotifyArmPlateDeviceUI(const shared_ptr<DeviceErrorEvent>& error_event)
{
	emit SignalArmPlateDeviceUI(error_event);
	return 0;
}

int ControllerUIAdapter::NotifyRobotArmDeviceUI(const shared_ptr<DeviceStateEvent>& state_event)
{
	emit SignalRobotArmDeviceUI(state_event);
	return 0;
}
int ControllerUIAdapter::NotifyRobotArmDeviceUI(const shared_ptr<DeviceOperaEvent>& opera_event)
{
	emit SignalRobotArmDeviceUI(opera_event);
	return 0;
}
int ControllerUIAdapter::NotifyRobotArmDeviceUI(const shared_ptr<DeviceErrorEvent>& error_event)
{
	emit SignalRobotArmDeviceUI(error_event);
	return 0;
}

int ControllerUIAdapter::NotifySyringeDeviceUI(const shared_ptr<DeviceStateEvent>& state_event)
{
	emit SignalSyringeDeviceUI(state_event);
	return 0;
}
int ControllerUIAdapter::NotifySyringeDeviceUI(const shared_ptr<DeviceOperaEvent>& opera_event)
{
	emit SignalSyringeDeviceUI(opera_event);
	return 0;
}
int ControllerUIAdapter::NotifySyringeDeviceUI(const shared_ptr<DeviceErrorEvent>& error_event)
{
	emit SignalSyringeDeviceUI(error_event);
	return 0;
}

int ControllerUIAdapter::NotifyUltrasoundDeviceUI(const shared_ptr<DeviceStateEvent>& state_event)
{
	emit SignalUltrasoundDeviceUI(state_event);
	return 0;
}
int ControllerUIAdapter::NotifyUltrasoundDeviceUI(const shared_ptr<DeviceOperaEvent>& opera_event)
{
	emit SignalUltrasoundDeviceUI(opera_event);
	return 0;
}
int ControllerUIAdapter::NotifyUltrasoundDeviceUI(const shared_ptr<DeviceErrorEvent>& error_event)
{
	emit SignalUltrasoundDeviceUI(error_event);
	return 0;
}
