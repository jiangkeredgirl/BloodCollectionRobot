#pragma once
/*********************************************************************
 * \file   DeviceUI.h
 * \brief  DeviceUI对应的UI显示基类. 
 * \author 蒋珂
 * \date   2023.05.28   
 *********************************************************************/

#include <QDialog>
#include "./include/qtstandard.h"
#include "./include/devicedefine.h"
#include "./include/eventdefine.h"
#include "./include/ProducerConsumerTemplate.h"


class DeviceUI : public QDialog
{
	Q_OBJECT

public:
	DeviceUI(QWidget*parent = nullptr);
	~DeviceUI();

public slots:
	virtual int SlotNotifyUI(const shared_ptr<DeviceStateEvent>& state_event);
	virtual int SlotNotifyUI(const shared_ptr<DeviceOperaEvent>& opera_event);
	virtual int SlotNotifyUI(const shared_ptr<DeviceErrorEvent>& error_event);

protected:
	/// 初始化ui界面
	virtual int SetupUi(QWidget* hostwidget);

protected:
	QWidget* m_widget_panel = nullptr;
	QLabel* m_label_device_name = nullptr;
	QLabel* m_label_device_state = nullptr;
	QLabel* m_label_device_error = nullptr;
	QLabel* m_label_device_opera = nullptr;
};
