#include "SyringeDeviceUI.h"
#include "ControllerUIAdapter.h"
#include "./include/LogWrapper.h"


SyringeDeviceUI::SyringeDeviceUI(QWidget *parent)
	: DeviceUI(parent)
{
	ui.setupUi(this);
	SetupUi(this);
	CONNECT_EVENT_TO_UI(SyringeDeviceUI);
}

SyringeDeviceUI::~SyringeDeviceUI()
{}

int SyringeDeviceUI::SetupUi(QWidget* hostwidget)
{
	DeviceUI::SetupUi(hostwidget);
	if (hostwidget)
	{
		hostwidget->setWindowTitle(ClassName(*this).c_str());
		m_label_device_name->setText(windowTitle());
	}
	return 0;
}