#pragma once
/*********************************************************************
 * \file   RobotArmDeviceUI.h
 * \brief  RobotArmDevice对应的ui显示. 
 * \author 蒋珂
 * \date   2023.05.28   
 *********************************************************************/
#include <QWidget>
#include "ui_RobotArmDeviceUI.h"
#include "./include/qtstandard.h"
#include "DeviceUI.h"

class RobotArmDeviceUI : public DeviceUI
{
	Q_OBJECT

public:
	RobotArmDeviceUI(QWidget *parent = nullptr);
	~RobotArmDeviceUI();

private:
	/// 初始化ui界面
	virtual int SetupUi(QWidget* hostwidget) override;

private:
	Ui::RobotArmDeviceUIClass ui;
};
