#include "UltrasoundDeviceUI.h"
#include "ControllerUIAdapter.h"
#include "./include/LogWrapper.h"


UltrasoundDeviceUI::UltrasoundDeviceUI(QWidget *parent)
	: DeviceUI(parent)
{
	ui.setupUi(this);
	SetupUi(this);
	CONNECT_EVENT_TO_UI(UltrasoundDeviceUI);
}

UltrasoundDeviceUI::~UltrasoundDeviceUI()
{}

int UltrasoundDeviceUI::SetupUi(QWidget* hostwidget)
{
	DeviceUI::SetupUi(hostwidget);
	if (hostwidget)
	{
		hostwidget->setWindowTitle(ClassName(*this).c_str());
		m_label_device_name->setText(windowTitle());
	}
	return 0;
}
