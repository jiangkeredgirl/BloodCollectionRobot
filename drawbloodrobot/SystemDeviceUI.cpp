#include "SystemDeviceUI.h"
#include "ControllerUIAdapter.h"
#include "./include/LogWrapper.h"

SystemDeviceUI::SystemDeviceUI(QWidget *parent)
	: DeviceUI(parent)
{
	ui.setupUi(this);
	SetupUi(this);
	CONNECT_EVENT_TO_UI(SystemDeviceUI);	
}

SystemDeviceUI::~SystemDeviceUI()
{}

int SystemDeviceUI::CreateDevices()
{
	int errocode = ControllerUIAdapter::instance().CreateDevices();
	return errocode;
}

int SystemDeviceUI::DestroyDevices()
{
	int errocode = ControllerUIAdapter::instance().DestroyDevices();
	return errocode;
}


void SystemDeviceUI::closeEvent(QCloseEvent*) 
{
	LOG_INFO("");
	DestroyDevices();
}

void SystemDeviceUI::showEvent(QShowEvent*) 
{
	LOG_INFO("");
	if (m_firstshow)
	{
		m_firstshow = false;
		CreateDevices();
	}
}

int SystemDeviceUI::SlotNotifyUI(const shared_ptr<DeviceStateEvent>& state_event)
{
	DeviceUI::SlotNotifyUI(state_event);
	return 0;
}

int SystemDeviceUI::SlotNotifyUI(const shared_ptr<DeviceOperaEvent>& opera_event)
{
	DeviceUI::SlotNotifyUI(opera_event);
	return 0;
}

int SystemDeviceUI::SlotNotifyUI(const shared_ptr<DeviceErrorEvent>& error_event)
{
	DeviceUI::SlotNotifyUI(error_event);
	return 0;
}

int SystemDeviceUI::SetupUi(QWidget* hostwidget)
{
	DeviceUI::SetupUi(hostwidget);
	if (hostwidget)
	{
		hostwidget->setWindowTitle(ClassName(*this).c_str());
		m_label_device_name->setText(windowTitle());
		
		Qt::WindowFlags flags = Qt::Dialog;
		flags |= Qt::WindowMinMaxButtonsHint;
		flags |= Qt::WindowCloseButtonHint;
		//flags |= Qt::WindowStaysOnTopHint;
		hostwidget->setWindowFlags(flags);
		hostwidget->resize(800, 450);
		//Qt::WindowFlags flags = Qt::Dialog | Qt::WindowStaysOnTopHint;
		//hostWidget->setWindowFlags(flags);
		hostwidget->setStyleSheet("QDialog{border:1px solid green;}");

		m_armplatedevice = new ArmPlateDeviceUI(nullptr);
		m_armplatedevice->setStyleSheet("ArmPlateDeviceUI{border:1px solid green;}");
		m_armplatedevice->resize(width() / 2, height() / 2);
		m_armplatedevice->show();

		m_robotarmdevice = new RobotArmDeviceUI(nullptr);
		m_robotarmdevice->setStyleSheet("RobotArmDeviceUI{border:1px solid green;}");
		m_robotarmdevice->resize(width() / 2, height() / 2);
		m_robotarmdevice->show();

		m_ultradevice = new UltrasoundDeviceUI(nullptr);
		m_ultradevice->setStyleSheet("UltrasoundDeviceUI{border:1px solid green;}");
		m_ultradevice->resize(width() / 2, height() / 2);
		m_ultradevice->show();

		m_syringedevice = new SyringeDeviceUI(nullptr);
		m_syringedevice->setStyleSheet("SyringeDeviceUI{border:1px solid green;}");
		m_syringedevice->resize(width() / 2, height() / 2);
		m_syringedevice->show();
	
		QVBoxLayout* widget_panel_layout = dynamic_cast<QVBoxLayout*>(m_widget_panel->layout());
		QGridLayout* layout_widget_childdevices = new QGridLayout;		
	
		widget_panel_layout->addLayout(layout_widget_childdevices);

		layout_widget_childdevices->addWidget(m_armplatedevice, 0, 0);
		layout_widget_childdevices->addWidget(m_robotarmdevice, 0, 1);
		layout_widget_childdevices->addWidget(m_ultradevice, 1, 0);
		layout_widget_childdevices->addWidget(m_syringedevice, 1, 1);
		widget_panel_layout->addStretch();
	}
	return 0;
}