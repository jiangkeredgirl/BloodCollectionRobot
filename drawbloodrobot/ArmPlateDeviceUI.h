#pragma once
/*********************************************************************
 * \file   ArmPlateDeviceUI.h
 * \brief  ArmPlateDevice对应的UI显示. 
 * \author 蒋珂
 * \date   2023.05.28   
 *********************************************************************/

#include <QWidget>
#include "ui_ArmPlateDeviceUI.h"
#include "./include/qtstandard.h"
#include "DeviceUI.h"

class ArmPlateDeviceUI : public DeviceUI
{
	Q_OBJECT

public:
	ArmPlateDeviceUI(QWidget *parent = nullptr);
	~ArmPlateDeviceUI();

private:
	/// 初始化ui界面
	virtual int SetupUi(QWidget* hostwidget) override;

private:
	Ui::ArmPlateDeviceUIClass ui;
};
