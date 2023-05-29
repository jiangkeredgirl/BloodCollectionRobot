/*********************************************************************
 * \file   main.cpp
 * \brief  程序入口函数. 
 * \author 蒋珂
 * \date   2023.05.27   
 *********************************************************************/
#include <QtCore/QCoreApplication>
#include <QtWidgets/QApplication>
#include "SystemDeviceUI.h"
#include "./include/LogWrapper.h"

int main(int argc, char *argv[])
{
    InitLog("./log", spdlog::level::level_enum::trace);
    LOG_INFO("main run");

    //QCoreApplication a(argc, argv);
    QApplication a(argc, argv);

    SystemDeviceUI main_ui;
    main_ui.show();

    return a.exec();
}
