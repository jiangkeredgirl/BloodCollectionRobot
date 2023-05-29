#include "SystemDevice.h"


SystemDevice::SystemDevice(int device_num, DeviceEvent device_event)
{
    m_devicevalue.device_type = DEVICE_TYPE_SYSTEM;
    m_devicevalue.device_name = "SystemDevice";
    m_devicevalue.device_num  = device_num;
    m_deviceevent             = device_event;
}

SystemDevice::~SystemDevice()
{

}

int SystemDevice::Open()
{
    return 0;
}

int SystemDevice::Close()
{
    return 0;
}

const DeviceValue& SystemDevice::GetDeviceValue()
{
    return m_devicevalue;
}

int  SystemDevice::SetManual()
{
    return 0;
}

int SystemDevice::UrgentStop()
{
    return 0;
}

int SystemDevice::SetSystemState(int state)
{
    int errorcode = SetState(state);
    return errorcode;
}

int SystemDevice::CheckError()
{
    return 0;
}

int SystemDevice::SetError(int error_code, bool clear)
{
    do
    {
        if (clear) //< 清除错误
        {
            if (error_code != m_devicevalue.error_code) //< 清除错误码和当前错误码不一致
            {
                break;
            }
            shared_ptr<DeviceErrorEvent> event(new DeviceErrorEvent());
            event->device_value = m_devicevalue;
            event->error_level = m_devicevalue.error_level;
            event->error_code = m_devicevalue.error_code;
            event->error_clear = clear;
            if (m_deviceevent.error_event)
            {
                LOG_ERROR("generate event:{}", event->EventStr());
                m_deviceevent.error_event(event);
            }
            int new_error_code = CheckError();
            /// 没有新的错误
            if (new_error_code == BLOODROBOT_ERRORCODE_OK)
            {
                m_devicevalue.error_level = ERROR_LEVEL_NONE;
                m_devicevalue.error_code = BLOODROBOT_ERRORCODE_OK;
                SetState(DEVICE_STATE_NORMAL);
            }
            else
            {
                /// 新错误
                SetError(new_error_code, false);
            }
        }
        else /// 产生新错误
        {
            if (error_code == m_devicevalue.error_code) //< 新错误码和当前错误码一致
            {
                break;
            }
            /// 当前已有错误，有2种处理方式，1）不处理新错误，2）将当前错误清除，产生新错误,系统设备用方式2
#if 0
            /// 方式1
            if (BLOODROBOT_ERRORCODE_OK != m_devicevalue.error_code)
            {
                break;
            }
#endif
            /// 方式2 将当前错误清除
            if (BLOODROBOT_ERRORCODE_OK != m_devicevalue.error_code)
            {
                shared_ptr<DeviceErrorEvent> event(new DeviceErrorEvent());
                event->device_value = m_devicevalue;
                event->error_level = m_devicevalue.error_level;
                event->error_code = m_devicevalue.error_code;
                event->error_clear = true;
                if (m_deviceevent.error_event)
                {
                    LOG_ERROR("generate event:{}", event->EventStr());
                    m_deviceevent.error_event(event);
                }
            }
            m_devicevalue.error_code = error_code;
            m_devicevalue.error_level = GetErrorLevel(error_code);
            shared_ptr<DeviceErrorEvent> event(new DeviceErrorEvent());
            event->device_value = m_devicevalue;
            event->error_level = m_devicevalue.error_level;
            event->error_code = m_devicevalue.error_code;
            event->error_clear = clear;
            if (m_deviceevent.error_event)
            {
                LOG_ERROR("generate event:{}", event->EventStr());
                m_deviceevent.error_event(event);
            }
            SetState(DEVICE_STATE_ABNORMAL);
        }

    } while (0);
    return 0;
}

int SystemDevice::SetState(int state)
{
    if (state != m_devicevalue.device_state)
    {
        shared_ptr<DeviceStateEvent> event(new DeviceStateEvent());
        event->device_value = m_devicevalue;
        event->old_state = m_devicevalue.device_state;
        event->new_state = state;
        m_devicevalue.device_state = state;
        if (m_deviceevent.state_event)
        {
            LOG_ERROR("generate event:{}", event->EventStr());
            m_deviceevent.state_event(event);
        }
    }
    return 0;
}

int SystemDevice::SetOpera(int opera)
{
    return 0;
}


ISystemDevice* NewSystemDevice(int device_num, DeviceEvent device_event)
{
    return new SystemDevice(device_num, device_event);
}

void DeleteSystemDevice(ISystemDevice* device)
{
    if (device)
    {
        delete dynamic_cast<SystemDevice*>(device);
        //device = nullptr;
    }
}
