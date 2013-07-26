cmake_minimum_required(VERSION 2.8.11)

project(matrixfactory)

set(TARGET matrixfactory)

set(SOURCES matrixfactory.cpp RectMatrix.cpp RectMatrixLogic.cpp) 

set(HEADERS matrixfactory.h RectMatrix.h RectMatrixLogic.h)

include_directories(../../src)

add_definitions(-DQT_PLUGIN)

find_package(Qt5Widgets)

set(CMAKE_AUTOMOC ON)

add_library(${PROJECT_NAME} SHARED ${HEADERS} ${SOURCES})

target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
