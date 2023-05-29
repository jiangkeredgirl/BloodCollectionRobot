#pragma once
/*********************************************************************
 * \file   SyringeDeviceUI.h
 * \brief  SyringeDevice设备对应的ui显示. 
 * \author 蒋珂
 * \date   2023.05.28   
 *********************************************************************/
#include <QWidget>
#include "ui_SyringeDeviceUI.h"
#include "./include/qtstandard.h"
#include "DeviceUI.h"


class SyringeDeviceUI : public DeviceUI
{
	Q_OBJECT

public:
	SyringeDeviceUI(QWidget *parent = nullptr);
	~SyringeDeviceUI();

private:
	/// 初始化ui界面
	virtual int SetupUi(QWidget* hostwidget) override;

private:
	Ui::SyringeDeviceUIClass ui;
};
