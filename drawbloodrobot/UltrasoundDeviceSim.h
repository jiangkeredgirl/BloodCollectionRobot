#pragma once
/*********************************************************************
 * \file   UltrasoundDeviceSim.h
 * \brief  模拟超声设备
 *
 * \author 蒋珂
 * \date   2023.05.14
 *********************************************************************/
#include "include/idevices/IUltrasoundDevice.h"
#include "include/qtstandard.h"

class UltrasoundDeviceSim :
    public QDialog,
    public IUltrasoundDevice
{
    Q_OBJECT

public:
    UltrasoundDeviceSim(int device_num, DeviceEvent device_event);
    ~UltrasoundDeviceSim();

public:
    virtual int Open() override;
    virtual int Close() override;
    virtual const DeviceValue& GetDeviceValue() override;   // 设备的值包括编号、状态、错误码
    virtual int ScanBlood() override;  // 扫描血管

private:
    /**
     * 时刻检查设备错误. 模拟设备检查不到错误，是通过SlotErrorChanged槽函数手动生成错误
     * \return  错误码.
     */
    int CheckError();
    /**
     * 产生错误或者清除错误.
     * \param   error_code 错误码
     * \param   clear 产生或者清除标记
     * \return  0 保留
     */
    int SetError(int error_code, bool clear);
    /**
     * 设置设备状态.
     * \param   state
     * \return 0 保留
     */
    int SetState(int state);
    /**
     * 设备上的操作，比如一些按键或者自动执行的操作.
     * \param   opera
     * \return
     */
    int SetOpera(int opera);

private:
    /// 初始化ui界面
    int SetupUi(QWidget* hostWidget);
signals:
    int SignalSetState(int state);
    int SignalSetError(int error);
private slots:
    int SlotStateChanged(const QString& state_text);
    int SlotOperaChanged(const QString& opera_text);
    int SlotErrorChanged(const QString& error_text);
    /// 设置ui界面的状态值
    int SlotSetState(int state);
    int SlotSetError(int error);

private:
    DeviceValue m_devicevalue;
    DeviceEvent m_deviceevent;
    QComboBox* m_box_state = nullptr;
    QComboBox* m_box_opera = nullptr;
    QComboBox* m_box_error = nullptr;
};

