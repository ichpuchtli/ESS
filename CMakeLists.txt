cmake_minimum_required(VERSION 2.8.11)

project(EmbeddedSystemSimulator)

set(TARGET ess)

set(LIBS elf libsimavr.a)

set(RESOURCE_FILE resources.qrc)

set(INCLUDES "include/simavr/simavr/sim")

set ( SOURCES 
  src/ess.cpp
  src/mainwindow.cpp
  src/PluginManager.cpp
  src/AVRIOAdapter.cpp
  src/GPIOPin.cpp
  src/AVRProcessor.cpp
  src/HybridAVRProcessor.cpp
  src/RegulatedAVRProcessor.cpp
  src/RRAVRProcessor.cpp
)

set ( HEADERS 
  src/AbstractAVRProcessor.h
  src/AbstractPeripheralLogic.h
  src/AbstractPeripheralWidget.h
  src/AbstractPin.h
  src/AVRProcessor.h
  src/GPIOPin.h
  src/mainwindow.h
)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/plugins)

set( PLUGINS
  rectmatrix
  
  )

foreach(plugin ${PLUGINS})
  add_subdirectory(plugins/${plugin})
endforeach()

include(CPack)

set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Another graphical front end to simavr")
set(CPACK_PACKAGE_NAME "simavr-qt")
set(CPACK_PACKAGE_VERSION "1.0")

find_package(Qt5Widgets)

set(CMAKE_AUTOMOC ON)

include_directories(${INCLUDES})

qt5_add_resources ( RESOURCES ${RESOURCE_FILE})

add_executable(${TARGET} ${SOURCES} ${HEADERS} ${RESOURCES})

target_link_libraries(${TARGET} Qt5::Widgets ${LIBS})
