cmake_minimum_required(VERSION 2.8.9)

set(target pmodsevenseg) 

set(sources PmodSevenSegWidget.cpp PmodSevenSegLogic.cpp)

set(headers factory.h PmodSevenSegWidget.h PmodSevenSegLogic.h)

set(CMAKE_AUTOMOC ON)

include_directories(../../src)

add_definitions(-DQT_PLUGIN)

find_package(Qt5Widgets)

add_definitions(${Qt5Widgets_DEFINITIONS})

add_definitions(-std=c++0x)

add_library(${target} SHARED ${headers} ${sources})

qt5_use_modules(${target} Widgets)
