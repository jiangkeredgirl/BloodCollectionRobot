#pragma once
/*********************************************************************
 * \file   SystemDeviceUI.h
 * \brief  主界面显示采血机器人系统的状态、操作、错误信息. 
 * \author 蒋珂
 * \date   2023.05.23   
 *********************************************************************/
#include <QDialog>
#include "ui_SystemDeviceUI.h"
#include "./include/devicedefine.h"
#include "./include/eventdefine.h"
#include "./include/qtstandard.h"
#include "ArmPlateDeviceUI.h"
#include "RobotArmDeviceUI.h"
#include "UltraSoundDeviceUI.h"
#include "SyringeDeviceUI.h"
#include "DeviceUI.h"

class SystemDeviceUI : public DeviceUI
{
	Q_OBJECT

public:
	SystemDeviceUI(QWidget *parent = nullptr);
	~SystemDeviceUI();

private:
	int CreateDevices();    // 创建设备
	int DestroyDevices();   // 退出设备

protected:
	void closeEvent(QCloseEvent*) override;
	void showEvent(QShowEvent*) override;

public slots:
	virtual int SlotNotifyUI(const shared_ptr<DeviceStateEvent>& state_event) override;
	virtual int SlotNotifyUI(const shared_ptr<DeviceOperaEvent>& opera_event) override;
	virtual int SlotNotifyUI(const shared_ptr<DeviceErrorEvent>& error_event) override;

private:
	/// 初始化ui界面
	virtual int SetupUi(QWidget* hostwidget) override;

private:
	bool m_firstshow = true; // 界面第一次显示标识

	/// 每个设备对应一个ui模块	
	ArmPlateDeviceUI*   m_armplatedevice = nullptr;                 //< 采血台
	RobotArmDeviceUI*   m_robotarmdevice = nullptr;                 //< 机械臂    
	UltrasoundDeviceUI* m_ultradevice    = nullptr;                 //< 超声波
	SyringeDeviceUI*    m_syringedevice  = nullptr;                 //< 注射器

private:
	Ui::SystemDeviceUIClass ui;
};
