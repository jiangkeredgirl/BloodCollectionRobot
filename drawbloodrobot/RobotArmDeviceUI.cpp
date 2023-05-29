#include "RobotArmDeviceUI.h"
#include "ControllerUIAdapter.h"
#include "./include/LogWrapper.h"

RobotArmDeviceUI::RobotArmDeviceUI(QWidget *parent)
	: DeviceUI(parent)
{
	ui.setupUi(this);
	SetupUi(this);
	CONNECT_EVENT_TO_UI(RobotArmDeviceUI);
}

RobotArmDeviceUI::~RobotArmDeviceUI()
{}

int RobotArmDeviceUI::SetupUi(QWidget* hostwidget)
{
	DeviceUI::SetupUi(hostwidget);
	if (hostwidget)
	{
		hostwidget->setWindowTitle(ClassName(*this).c_str());
		m_label_device_name->setText(windowTitle());
	}
	return 0;
}