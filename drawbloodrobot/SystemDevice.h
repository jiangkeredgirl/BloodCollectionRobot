#pragma once
/*********************************************************************
 * \file   SystemDevice.h
 * \brief  系统设备，是所有设备(采血台、机械臂、超声、注射器等）的组合. 
 * \author 蒋珂
 * \date   2023.05.23   
 *********************************************************************/

#include "./include/idevices/ISystemDevice.h"

class SystemDevice : public ISystemDevice
{

public:
    SystemDevice(int device_num, DeviceEvent device_event);
    ~SystemDevice();

public:
    virtual int Open() override;
    virtual int Close() override;
    virtual const DeviceValue& GetDeviceValue() override;   // 设备的值包括编号、状态、错误码
    virtual int SetManual() override;     // 设置手动模式
    // 紧急停止，作为医疗设备，时刻检查系统状态，有任何不稳定，将会自动立即停止工作
    // 此函数将人工紧急停止设备
    virtual int UrgentStop() override;
    // 设置状态，状态的变化会影响状态机的调用
    virtual int SetSystemState(int state) override;

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
    DeviceValue m_devicevalue;
    DeviceEvent m_deviceevent;
};

