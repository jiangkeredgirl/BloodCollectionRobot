#pragma once
/*********************************************************************
 * \file   Controller.h
 * \brief  系统逻辑控制
 *
 * \author 蒋珂
 * \date   2023.05.14
 *********************************************************************/

#include "./include/idevices/IDevice.h"
#include "./include/idevices/ISystemDevice.h"
#include "./include/idevices/IArmPlateDevice.h"
#include "./include/idevices/IRobotArmDevice.h"
#include "./include/idevices/IUltrasoundDevice.h"
#include "./include/idevices/ISyringeDevice.h"
#include "SimuDevicesPanel.h"
#include "ArmPlateDeviceSim.h"
#include "RobotArmDeviceSim.h"
#include "SyringeDeviceSim.h"
#include "UltrasoundDeviceSim.h"
#include "SystemDevice.h"
#include "./include/ProducerConsumerTemplate.h"

 /// 是否使用设备模拟器
#define USE_SIMU_PLATE      1  //< 使用模拟采血台设备
#define USE_SIMU_ARM        1  //< 使用模拟机械臂设备
#define USE_SIMU_ULTRA      1  //< 使用模拟超声波设备
#define USE_SIMU_SYRING     1  //< 使用模拟注射器设备

class Controller
{
private:
	Controller() {};
	~Controller() {};

public:
	static Controller& instance()
	{
		static Controller controller;
		return controller;
	}

public:
	int CreateDevices();    // 创建设备
	int DestroyDevices();   // 退出设备
	/**
    * 自动设置系统状态，当任何一个设备异常时，系统状态变成异常状态.
    * \return  保留
    */
	int AutoSetSystemState();
private:
	int CreateSimDevices();  // 创建模拟设备
	int DestroySimDevices(); // 删除模拟设备
	int OpenDevices();       // 开启设备
	int CloseDevices();      // 关闭设备
	int SetSystemState(int systemdevice_state);
public:
	/**
	 * 获取系统状态，系统状态即是系统设备状态.
	 * \return 系统设备状态
	 */
	int GetSystemState();
	bool DevicesIsNormal();

private:
	// 事件处理相关函数
	/**
	 * 初始化状态机，所有事件的处理是以状态机模式在调用.
	 * \return 系统设备状态
	 */
	int InitStatMachine();
	int DeviceStateEventReceiver(const shared_ptr<DeviceStateEvent>& state_event);
	int DeviceOperaEventReceiver(const shared_ptr<DeviceOperaEvent>& opera_event);
	int DeviceErrorEventReceiver(const shared_ptr<DeviceErrorEvent>& error_event);
	int EventQueuePush(const shared_ptr<BloodRobotEvent>& event);
	int EventDistribute(const shared_ptr<BloodRobotEvent>& event);

public:
	// 通知ui的接口
	int NotifyUI(const shared_ptr<DeviceStateEvent>& state_event);
	int NotifyUI(const shared_ptr<DeviceOperaEvent>& opera_event);
	int NotifyUI(const shared_ptr<DeviceErrorEvent>& error_event);

private:
	/// 事件队列线程run，已封装到ProducerConsumerTemplate模板类
	//int EventQueueThreadRun();


private:
	ISystemDevice* m_systemdevice     = nullptr;                 //< 系统
	IArmPlateDevice* m_armplatedevice = nullptr;                 //< 采血台
	IRobotArmDevice* m_robotarmdevice = nullptr;                 //< 机械臂    
	IUltrasoundDevice* m_ultradevice  = nullptr;                 //< 超声波
	ISyringeDevice* m_syringedevice   = nullptr;                 //< 注射器
	DeviceEvent        m_deviceevent;
#if 0
	list<shared_ptr<BloodRobotEvent>> m_event_list;                //< 事件列表
	mutex                             m_event_list_mutex;          //< 列表mutex，防止list crash
	thread                            m_event_thread;              //< 事件列表线程，异步处理事件      
	mutex                             m_event_thread_mutex;        //< 线程mutex，配合condition用
	condition_variable                m_event_thread_condition;    //< 线程condition，线程通知  
	bool                              m_event_thread_kill = false; //< 线程kill标记，退出程序前kill线程
#endif
	ProducerConsumerTemplate<BloodRobotEvent> m_eventdata;

	SimuDevicesPanel* m_simupanel = nullptr;                       ///< 设备模拟器面板

};

