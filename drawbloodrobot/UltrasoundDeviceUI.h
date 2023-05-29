#pragma once
/*********************************************************************
 * \file   UltrasoundDeviceUI.h
 * \brief  UltrasoundDevice对应的ui显示. 
 * \author 蒋珂
 * \date   2023.05.28   
 *********************************************************************/
#include <QWidget>
#include "ui_UltrasoundDeviceUI.h"
#include "./include/qtstandard.h"
#include "DeviceUI.h"


class UltrasoundDeviceUI : public DeviceUI
{
	Q_OBJECT

public:
	UltrasoundDeviceUI(QWidget *parent = nullptr);
	~UltrasoundDeviceUI();

private:
	/// 初始化ui界面
	virtual int SetupUi(QWidget* hostwidget) override;

private:
	Ui::UltrasoundDeviceUIClass ui;
};
