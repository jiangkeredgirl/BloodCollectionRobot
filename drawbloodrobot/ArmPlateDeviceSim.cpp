#include "ArmPlateDeviceSim.h"


ArmPlateDeviceSim::ArmPlateDeviceSim(int device_num, DeviceEvent device_event)
{
	m_devicevalue.device_type = DEVICE_TYPE_ARMPLATE;
	m_devicevalue.device_name = "ArmPlateDevice";
	m_devicevalue.device_num = device_num;
	m_deviceevent = device_event;
	SetupUi(this);
}

ArmPlateDeviceSim::~ArmPlateDeviceSim()
{

}

int ArmPlateDeviceSim::Open()
{
	return 0;
}

int ArmPlateDeviceSim::Close()
{
	return 0;
}

const DeviceValue& ArmPlateDeviceSim::GetDeviceValue()
{
	return m_devicevalue;
}

int ArmPlateDeviceSim::ArmBand()
{
	return 0;
}

int ArmPlateDeviceSim::ArmLooseBand()
{
	return 0;
}

int ArmPlateDeviceSim::CheckError()
{
	return 0;
}

int ArmPlateDeviceSim::SetError(int error_code, bool clear)
{
	do
	{
		if (clear) //< 清除错误
		{
			if (error_code != m_devicevalue.error_code) //< 清除错误码和当前错误码不一致
			{
				break;
			}
			shared_ptr<DeviceErrorEvent> event(new DeviceErrorEvent());
			event->device_value = m_devicevalue;
			event->error_level = m_devicevalue.error_level;
			event->error_code = m_devicevalue.error_code;
			event->error_clear = clear;
			if (m_deviceevent.error_event)
			{
				LOG_ERROR("generate event:{}", event->EventStr());
				m_deviceevent.error_event(event);
			}
			int new_error_code = CheckError();
			/// 没有新的错误
			if (new_error_code == BLOODROBOT_ERRORCODE_OK)
			{
				m_devicevalue.error_level = ERROR_LEVEL_NONE;
				m_devicevalue.error_code = BLOODROBOT_ERRORCODE_OK;
				SetState(DEVICE_STATE_NORMAL);
				emit SignalSetError(m_devicevalue.error_code);
			}
			else
			{
				/// 新错误
				SetError(new_error_code, false);
			}
		}
		else /// 产生新错误
		{
			if (error_code == m_devicevalue.error_code) //< 新错误码和当前错误码一致
			{
				break;
			}
			/// 当前已有错误，有2种处理方式，1）不处理新错误，2）将当前错误清除，产生新错误,模拟设备用方式2
#if 0
			/// 方式1
			if (BLOODROBOT_ERRORCODE_OK != m_devicevalue.error_code)
			{
				break;
			}
#endif
			/// 方式2 将当前错误清除
			if (BLOODROBOT_ERRORCODE_OK != m_devicevalue.error_code)
			{
				shared_ptr<DeviceErrorEvent> event(new DeviceErrorEvent());
				event->device_value = m_devicevalue;
				event->error_level = m_devicevalue.error_level;
				event->error_code = m_devicevalue.error_code;
				event->error_clear = true;
				if (m_deviceevent.error_event)
				{
					LOG_ERROR("generate event:{}", event->EventStr());
					m_deviceevent.error_event(event);
				}
			}
			m_devicevalue.error_code = error_code;
			m_devicevalue.error_level = GetErrorLevel(error_code);
			shared_ptr<DeviceErrorEvent> event(new DeviceErrorEvent());
			event->device_value = m_devicevalue;
			event->error_level = m_devicevalue.error_level;
			event->error_code = m_devicevalue.error_code;
			event->error_clear = clear;
			if (m_deviceevent.error_event)
			{
				LOG_ERROR("generate event:{}", event->EventStr());
				m_deviceevent.error_event(event);
			}
			SetState(DEVICE_STATE_ABNORMAL);
			emit SignalSetError(m_devicevalue.error_code);
		}

	} while (0);
	return 0;
}

int ArmPlateDeviceSim::SetState(int state)
{
	if (state != m_devicevalue.device_state)
	{
		shared_ptr<DeviceStateEvent> event(new DeviceStateEvent());
		event->device_value = m_devicevalue;
		event->old_state = m_devicevalue.device_state;
		event->new_state = state;
		m_devicevalue.device_state = state;
		if (m_deviceevent.state_event)
		{
			LOG_INFO("generate event:{}", event->EventStr());
			m_deviceevent.state_event(event);
		}
		emit SignalSetState(state);
		if (event->new_state != DEVICE_STATE_ABNORMAL)
		{
			if (m_devicevalue.error_code != BLOODROBOT_ERRORCODE_OK)
			{
				SetError(m_devicevalue.error_code, true);
			}
		}
	}
	return 0;
}

int ArmPlateDeviceSim::SetOpera(int opera)
{
	m_devicevalue.device_opera = opera;
	shared_ptr<DeviceOperaEvent> event(new DeviceOperaEvent());
	event->device_value = m_devicevalue;
	event->opera_code = m_devicevalue.device_opera;
	if (m_deviceevent.opera_event)
	{
		LOG_INFO("generate event:{}", event->EventStr());
		m_deviceevent.opera_event(event);
	}
	return 0;
}

int ArmPlateDeviceSim::SetupUi(QWidget* hostWidget)
{
	if (hostWidget)
	{
		this->setWindowTitle(typeid((*this)).name());
		connect(this, &ArmPlateDeviceSim::SignalSetState, this, &ArmPlateDeviceSim::SlotSetState);
		connect(this, &ArmPlateDeviceSim::SignalSetError, this, &ArmPlateDeviceSim::SlotSetError);

		Qt::WindowFlags flags = Qt::Dialog;
		flags |= Qt::WindowMinMaxButtonsHint;
		flags |= Qt::WindowCloseButtonHint;
		setWindowFlags(flags);
		hostWidget->setStyleSheet("ArmPlateDeviceSim{border:1px solid green;}");
		QVBoxLayout* layout = new QVBoxLayout;
		hostWidget->setLayout(layout);

		QWidget* widget_device = new QWidget();
		//widget_device->setStyleSheet("QWidget{border:1px solid green;}");
		QVBoxLayout* layout_widget_device = new QVBoxLayout;
		widget_device->setLayout(layout_widget_device);
		layout->addWidget(widget_device);

		QLabel* label_device_num = new QLabel();
		label_device_num->setStyleSheet("QLabel{border:1px solid green;}");
		label_device_num->setText(("num:" + DeviceNumStr(m_devicevalue.device_type, m_devicevalue.device_num)).c_str());

#if 0
		QLabel* label_device_state = new QLabel();
		label_device_state->setStyleSheet("QLabel{border:1px solid green;}");
		label_device_state->setText("state:");
#endif

		QComboBox* box_device_state = new QComboBox();
		box_device_state->setStyleSheet("QComboBox{border:1px solid green;}");
		box_device_state->addItem(DeviceStateStr(DEVICE_STATE_NORMAL).c_str(), DEVICE_STATE_NORMAL);
		box_device_state->addItem(DeviceStateStr(DEVICE_STATE_ABNORMAL).c_str(), DEVICE_STATE_ABNORMAL);
		box_device_state->addItem(DeviceStateStr(DEVICE_STATE_STANDBY).c_str(), DEVICE_STATE_STANDBY);
		box_device_state->addItem(DeviceStateStr(DEVICE_STATE_RUNNING).c_str(), DEVICE_STATE_RUNNING);
		box_device_state->addItem(DeviceStateStr(DEVICE_STATE_WORKING).c_str(), DEVICE_STATE_WORKING);
		box_device_state->addItem(DeviceStateStr(DEVICE_STATE_URGENTSTOP).c_str(), DEVICE_STATE_URGENTSTOP);
		m_box_state = box_device_state;

#if 0
		QLabel* label_device_error = new QLabel();
		label_device_error->setStyleSheet("QLabel{border:1px solid green;}");
		label_device_error->setText("error:");
#endif

		QComboBox* box_device_error = new QComboBox();
		box_device_error->setStyleSheet("QComboBox{border:1px solid green;}");
		box_device_error->addItem(ErrorCodeStr(BLOODROBOT_ERRORCODE_OK).c_str(), BLOODROBOT_ERRORCODE_OK);
		box_device_error->addItem(ErrorCodeStr(BLOODROBOT_ERROR_ARMPLATEDEVICE_BOOT).c_str(), BLOODROBOT_ERROR_ARMPLATEDEVICE_BOOT);
		box_device_error->addItem(ErrorCodeStr(BLOODROBOT_ERROR_ARMPLATEDEVICE_BAND).c_str(), BLOODROBOT_ERROR_ARMPLATEDEVICE_BAND);
		m_box_error = box_device_error;

#if 0
		QLabel* label_device_opera = new QLabel();
		label_device_opera->setStyleSheet("QLabel{border:1px solid green;}");
		label_device_opera->setText("opera:");
#endif

		QComboBox* box_device_opera = new QComboBox();
		box_device_opera->setStyleSheet("QComboBox{border:1px solid green;}");
		box_device_opera->addItem(DeviceOperaStr(ARMPLATEDEVICE_OPERA_UNKNOWN).c_str(), ARMPLATEDEVICE_OPERA_UNKNOWN);
		box_device_opera->addItem(DeviceOperaStr(ARMPLATEDEVICE_OPERA_ARMFIXED).c_str(), ARMPLATEDEVICE_OPERA_ARMFIXED);
		box_device_opera->addItem(DeviceOperaStr(ARMPLATEDEVICE_OPERA_ARMUNFIXED).c_str(), ARMPLATEDEVICE_OPERA_ARMUNFIXED);
		box_device_opera->addItem(DeviceOperaStr(ARMPLATEDEVICE_OPERA_BAND).c_str(), ARMPLATEDEVICE_OPERA_BAND);
		box_device_opera->addItem(DeviceOperaStr(ARMPLATEDEVICE_OPERA_LOOSEBAND).c_str(), ARMPLATEDEVICE_OPERA_LOOSEBAND);
		m_box_opera = box_device_opera;

		connect(box_device_state, &QComboBox::currentTextChanged,
			[this](const QString& text) { SlotStateChanged(text); });
		connect(box_device_error, &QComboBox::currentTextChanged,
			[this](const QString& text) { SlotErrorChanged(text); });
		connect(box_device_opera, &QComboBox::currentTextChanged,
			[this](const QString& text) { SlotOperaChanged(text); });

		box_device_state->setCurrentText(DeviceStateStr(m_devicevalue.device_state).c_str());
		box_device_error->setCurrentText(ErrorCodeStr(m_devicevalue.error_code).c_str());
		box_device_opera->setCurrentText(DeviceOperaStr(m_devicevalue.device_opera).c_str());

		layout_widget_device->addWidget(label_device_num);
		//layout_widget_device->addWidget(label_device_state);
		layout_widget_device->addWidget(box_device_state);
		//layout_widget_device->addWidget(label_device_error);
		layout_widget_device->addWidget(box_device_error);
		//layout_widget_device->addWidget(label_device_opera);
		layout_widget_device->addWidget(box_device_opera);
		layout_widget_device->addStretch();
		layout->addStretch();
	}
	return 0;
}

int ArmPlateDeviceSim::SlotStateChanged(const QString& state_text)
{
	int newstate = m_box_state->currentData().toInt(); //项关联的数据
	SetState(newstate);
	return 0;
}

int ArmPlateDeviceSim::SlotOperaChanged(const QString& opera_text)
{
	int opera = m_box_opera->currentData().toInt(); //项关联的数据
	SetOpera(opera);
	return 0;
}

int ArmPlateDeviceSim::SlotErrorChanged(const QString& error_text)
{
	int error = m_box_error->currentData().toInt(); //项关联的数据
	if (error != BLOODROBOT_ERRORCODE_OK)
	{
		SetError(error, false);
	}
	else if (error == BLOODROBOT_ERRORCODE_OK)
	{
		if (m_devicevalue.error_code != BLOODROBOT_ERRORCODE_OK)
		{
			SetError(m_devicevalue.error_code, true);
		}
	}
	return 0;
}

int ArmPlateDeviceSim::SlotSetState(int state)
{
	m_box_state->setCurrentText(DeviceStateStr(state).c_str());
	return 0;
}

int ArmPlateDeviceSim::SlotSetError(int error)
{
	m_box_error->setCurrentText(ErrorCodeStr(error).c_str());
	return 0;
}


IArmPlateDevice* NewArmPlateDevice(int device_num, DeviceEvent device_event)
{
	return new ArmPlateDeviceSim(device_num, device_event);
}

void DeleteArmPlateDevice(IArmPlateDevice* device)
{
	if (device)
	{
		delete dynamic_cast<ArmPlateDeviceSim*>(device);
	}
}