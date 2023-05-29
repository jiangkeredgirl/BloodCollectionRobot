#pragma once

#include "./include/qtstandard.h"
#include "ui_SimuDevicesPanel.h"

class SimuDevicesPanel : public QDialog
{
	Q_OBJECT

public:
	SimuDevicesPanel(QWidget *parent = nullptr);
	~SimuDevicesPanel();

public:
	int AddSimDevice(QWidget* simdevice, QString device_name);

private:
	int SetupUi(QWidget* hostWidget);
	QTabWidget* m_tab_widget = nullptr;
	Ui::SimuDevicesPanelClass ui;
};
