cmake_minimum_required(VERSION 2.8.9)

set(target oscilloscope1ch) 

set(sources OscilloscopeLogic.cpp OscilloscopeWidget.cpp include/qcustomplot/qcustomplot.cpp)

set(headers factory.h OscilloscopeWidget.h OscilloscopeLogic.h include/qcustomplot/qcustomplot.h)

set(CMAKE_AUTOMOC ON)

include_directories(../../src)

add_definitions(-DQT_PLUGIN)

find_package(Qt5Widgets)

add_definitions(${Qt5Widgets_DEFINITIONS})

add_library(${target} SHARED ${headers} ${sources})

qt5_use_modules(${target} Widgets PrintSupport)
