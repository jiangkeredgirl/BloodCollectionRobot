#pragma once
/*********************************************************************
 * \file   Controller.h
 * \brief  系统逻辑控制
 *
 * \author 蒋珂
 * \date   2023.05.14
 *********************************************************************/

#include "SystemDevice.h"
#include "./include/ProducerConsumerTemplate.h"


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
	/**
	* 创建设备.
	* \return  保留
	*/
	int CreateDevices(); 
	/**
     * 释放设备.
     * \return  保留
     */
	int DestroyDevices(); 
	/**
    * 自动设置系统状态，当任何一个设备异常时，系统状态变成异常状态.
    * \return  保留
    */
	int AutoSetSystemState();

private:
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
	ISystemDevice* m_systemdevice     = nullptr;  //< 系统
	DeviceEvent    m_deviceevent;
#if 0
	list<shared_ptr<BloodRobotEvent>> m_event_list;                //< 事件列表
	mutex                             m_event_list_mutex;          //< 列表mutex，防止list crash
	thread                            m_event_thread;              //< 事件列表线程，异步处理事件      
	mutex                             m_event_thread_mutex;        //< 线程mutex，配合condition用
	condition_variable                m_event_thread_condition;    //< 线程condition，线程通知  
	bool                              m_event_thread_kill = false; //< 线程kill标记，退出程序前kill线程
#endif
	ProducerConsumerTemplate<BloodRobotEvent> m_eventdata;	

};
