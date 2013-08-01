cmake_minimum_required(VERSION 2.8.9)

set(target cerebotleds) 

set(sources CerebotIILEDWidget.cpp CerebotIILEDLogic.cpp ../utils/LEDLogic.cpp)

set(headers factory.h CerebotIILEDWidget.h CerebotIILEDLogic.h ../utils/LEDLogic.h)

set(CMAKE_AUTOMOC ON)

include_directories(../../src)

add_definitions(-DQT_PLUGIN)

find_package(Qt5Widgets)

add_definitions(${Qt5Widgets_DEFINITIONS})

add_library(${target} SHARED ${headers} ${sources})

qt5_use_modules(${target} Widgets)
