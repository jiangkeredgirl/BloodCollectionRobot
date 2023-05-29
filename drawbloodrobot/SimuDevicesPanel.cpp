#include "SimuDevicesPanel.h"

SimuDevicesPanel::SimuDevicesPanel(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	SetupUi(this);
	this->setWindowTitle("device simulator panel");
}

SimuDevicesPanel::~SimuDevicesPanel()
{}

int SimuDevicesPanel::AddSimDevice(QWidget* simdevice, QString device_name)
{
    m_tab_widget->addTab(simdevice, device_name);
	return 0;
}

int SimuDevicesPanel::SetupUi(QWidget* hostWidget)
{
    if (hostWidget)
    {
        Qt::WindowFlags flags = Qt::Dialog;
        flags |= Qt::WindowMinMaxButtonsHint;
        flags |= Qt::WindowCloseButtonHint;
        flags |= Qt::Tool;
        setWindowFlags(flags);
        hostWidget->setStyleSheet("SimuContainer{border:1px solid green;}");
        QVBoxLayout* layout = new QVBoxLayout;
        hostWidget->setLayout(layout);
        m_tab_widget = new QTabWidget();
        m_tab_widget->setStyleSheet("QTabWidget{border:1px solid green;}");
        layout->addWidget(m_tab_widget);
    }
	return 0;
}
