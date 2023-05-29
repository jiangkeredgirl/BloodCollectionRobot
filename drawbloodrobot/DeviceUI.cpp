#include "DeviceUI.h"
#include "ControllerUIAdapter.h"
#include "./include/LogWrapper.h"


DeviceUI::DeviceUI(QWidget *parent)
	: QDialog(parent)
{	
}

DeviceUI::~DeviceUI()
{}

int DeviceUI::SlotNotifyUI(const shared_ptr<DeviceStateEvent>& state_event)
{
	if (state_event)
	{
		m_label_device_state->setText(("state:" + DeviceStateStr(state_event->new_state)).c_str());	
		if (state_event->new_state == DEVICE_STATE_ABNORMAL)
		{
			m_widget_panel->setStyleSheet(".QWidget{background:red;border:1px solid green;}");
		}
		else
		{
			m_widget_panel->setStyleSheet(".QWidget{background:white;border:1px solid green;}");
		}
	}
	return 0;
}

int DeviceUI::SlotNotifyUI(const shared_ptr<DeviceOperaEvent>& opera_event)
{
	if (opera_event)
	{
		m_label_device_opera->setText(("opera:" + DeviceOperaStr(opera_event->opera_code)).c_str());
	}
	return 0;
}

int DeviceUI::SlotNotifyUI(const shared_ptr<DeviceErrorEvent>& error_event)
{
	if (error_event)
	{
		if (!error_event->error_clear)
		{
			m_label_device_error->setText(("error:" + ErrorCodeStr(error_event->error_code)).c_str());
		}
		else
		{
			m_label_device_error->setText(("error:" + ErrorCodeStr(BLOODROBOT_ERRORCODE_OK)).c_str());
		}		
	}
	return 0;
}

int DeviceUI::SetupUi(QWidget* hostwidget)
{
	if (hostwidget)
	{
		//hostwidget->setWindowTitle(ClassName(*this).c_str());	
		hostwidget->setStyleSheet("QWidget{border:1px solid green;}");

		m_widget_panel = new QWidget();
		//m_widget_panel->setStyleSheet("QWidget{border:1px solid green;}");
		m_widget_panel->setStyleSheet("QWidget{background:white;border:1px solid green;}");

		m_label_device_name = new QLabel();
		m_label_device_name->setStyleSheet("QLabel{border:1px solid green;}");
		m_label_device_name->setText(windowTitle());

		m_label_device_state = new QLabel();
		m_label_device_state->setStyleSheet("QLabel{border:1px solid green;}");
		m_label_device_state->setText("state:");

		m_label_device_error = new QLabel();
		m_label_device_error->setStyleSheet("QLabel{border:1px solid green;}");
		m_label_device_error->setText("error:");

		m_label_device_opera = new QLabel();
		m_label_device_opera->setStyleSheet("QLabel{border:1px solid green;}");
		m_label_device_opera->setText("opera:");

		QVBoxLayout* hostwidget_layout   = new QVBoxLayout;
		QVBoxLayout* widget_panel_layout = new QVBoxLayout;

		hostwidget->setLayout(hostwidget_layout);
		m_widget_panel->setLayout(widget_panel_layout);
		hostwidget_layout->addWidget(m_widget_panel);

		widget_panel_layout->addWidget(m_label_device_name);
		widget_panel_layout->addWidget(m_label_device_state);
		widget_panel_layout->addWidget(m_label_device_error);
		widget_panel_layout->addWidget(m_label_device_opera);
		widget_panel_layout->addStretch();
		hostwidget_layout->addStretch();
	}
	return 0;
}