#pragma once
/*********************************************************************
 * \file   ControllerUIAdapter.h
 * \brief  逻辑代码Controller类和UI界面类SystemDeviceUI的交互接口，Adapter设计模式
 * 
 * \author 蒋珂
 * \date   2023.05.14   
 *********************************************************************/
#include <QObject>
#include "./include/devicedefine.h"
#include "./include/eventdefine.h"

/**
 * 事件传给ui的信号定义，只能在ControllerUIAdapter类头文件调用. 
 */
#define SIGNAL_EVENT_TO_UI(DEVICE_UI_NAME) \
    int Signal##DEVICE_UI_NAME(const shared_ptr<DeviceStateEvent>& state_event); \
    int Signal##DEVICE_UI_NAME(const shared_ptr<DeviceOperaEvent>& opera_event); \
    int Signal##DEVICE_UI_NAME(const shared_ptr<DeviceErrorEvent>& error_event);

 /**
  * 事件传给ui的信号槽连接，此函数有固定调用位置：ui模块的构造函数里.
  */
#define CONNECT_EVENT_TO_UI(DEVICE_UI_NAME) \
connect(&ControllerUIAdapter::instance() \
    , QOverload<const shared_ptr<DeviceStateEvent>& >::of(&ControllerUIAdapter::Signal##DEVICE_UI_NAME) \
    , this \
    , QOverload<const shared_ptr<DeviceStateEvent>& >::of(&##DEVICE_UI_NAME::SlotNotifyUI)); \
connect(&ControllerUIAdapter::instance() \
    , QOverload<const shared_ptr<DeviceOperaEvent>& >::of(&ControllerUIAdapter::Signal##DEVICE_UI_NAME) \
    , this \
    , QOverload<const shared_ptr<DeviceOperaEvent>& >::of(&##DEVICE_UI_NAME::SlotNotifyUI)); \
connect(&ControllerUIAdapter::instance() \
    , QOverload<const shared_ptr<DeviceErrorEvent>& >::of(&ControllerUIAdapter::Signal##DEVICE_UI_NAME) \
    , this \
    , QOverload<const shared_ptr<DeviceErrorEvent>& >::of(&##DEVICE_UI_NAME::SlotNotifyUI));

/**
 * 将成员函数和事件绑定. 
 */
#define BIND_STATE_EVENT_TO_UI(DEVICE_UI_NAME) std::bind((int(ControllerUIAdapter::*)(const shared_ptr<DeviceStateEvent>&))& ControllerUIAdapter::Notify##DEVICE_UI_NAME, this, std::placeholders::_1);
#define BIND_ERROR_EVENT_TO_UI(DEVICE_UI_NAME) std::bind((int(ControllerUIAdapter::*)(const shared_ptr<DeviceErrorEvent>&))& ControllerUIAdapter::Notify##DEVICE_UI_NAME, this, std::placeholders::_1);
#define BIND_OPERA_EVENT_TO_UI(DEVICE_UI_NAME) std::bind((int(ControllerUIAdapter::*)(const shared_ptr<DeviceOperaEvent>&))& ControllerUIAdapter::Notify##DEVICE_UI_NAME, this, std::placeholders::_1);


class ControllerUIAdapter  : public QObject
{
	Q_OBJECT

private:
	ControllerUIAdapter(QObject *parent = nullptr);
	~ControllerUIAdapter();

public:
    static ControllerUIAdapter& instance()
    {
        static ControllerUIAdapter uiadapter;
        return uiadapter;
    }

public:
    int CreateDevices();    // 创建设备
    int DestroyDevices();   // 退出设备
   
public:
    // 通知ui的接口
    int NotifyUI(const shared_ptr<DeviceStateEvent>& state_event);
    int NotifyUI(const shared_ptr<DeviceOperaEvent>& opera_event);
    int NotifyUI(const shared_ptr<DeviceErrorEvent>& error_event);

private:
    int NotifySystemDeviceUI(const shared_ptr<DeviceStateEvent>& state_event);
    int NotifySystemDeviceUI(const shared_ptr<DeviceOperaEvent>& opera_event);
    int NotifySystemDeviceUI(const shared_ptr<DeviceErrorEvent>& error_event);

    int NotifyArmPlateDeviceUI(const shared_ptr<DeviceStateEvent>& state_event);
    int NotifyArmPlateDeviceUI(const shared_ptr<DeviceOperaEvent>& opera_event);
    int NotifyArmPlateDeviceUI(const shared_ptr<DeviceErrorEvent>& error_event);

    int NotifyRobotArmDeviceUI(const shared_ptr<DeviceStateEvent>& state_event);
    int NotifyRobotArmDeviceUI(const shared_ptr<DeviceOperaEvent>& opera_event);
    int NotifyRobotArmDeviceUI(const shared_ptr<DeviceErrorEvent>& error_event);

    int NotifySyringeDeviceUI(const shared_ptr<DeviceStateEvent>& state_event);
    int NotifySyringeDeviceUI(const shared_ptr<DeviceOperaEvent>& opera_event);
    int NotifySyringeDeviceUI(const shared_ptr<DeviceErrorEvent>& error_event);

    int NotifyUltrasoundDeviceUI(const shared_ptr<DeviceStateEvent>& state_event);
    int NotifyUltrasoundDeviceUI(const shared_ptr<DeviceOperaEvent>& opera_event);
    int NotifyUltrasoundDeviceUI(const shared_ptr<DeviceErrorEvent>& error_event);

signals:
    /// 将事件发送给每个ui模块的信号
    SIGNAL_EVENT_TO_UI(SystemDeviceUI)
    SIGNAL_EVENT_TO_UI(ArmPlateDeviceUI)
    SIGNAL_EVENT_TO_UI(RobotArmDeviceUI)
    SIGNAL_EVENT_TO_UI(UltrasoundDeviceUI)
    SIGNAL_EVENT_TO_UI(SyringeDeviceUI)

private:
    /// 根据设备类型对应不同的notifyui函数
    map<int/*device type*/, DeviceEvent> m_device_notifyui;

};
