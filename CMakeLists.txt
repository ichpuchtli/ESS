cmake_minimum_required(VERSION 2.8.9)

project(EmbeddedSystemSimulator)

set(target ess)

set(libs libsimavr.a elf)

set(resource_file resources.qrc)

set(includes "include/simavr/simavr/sim")

set ( sources 
  src/ess.cpp
  src/mainwindow.cpp
  src/PluginManager.cpp
  src/AVRIOAdapter.cpp
  src/GPIOPin.cpp
  src/AVRProcessor.cpp
  src/HybridAVRProcessor.cpp
  src/RegulatedAVRProcessor.cpp
  src/RRAVRProcessor.cpp
  src/netmanager.cpp
)

set ( headers 
  src/AbstractAVRProcessor.h
  src/AbstractPeripheralLogic.h
  src/AbstractPin.h
  src/AVRProcessor.h
  src/GPIOPin.h
  src/mainwindow.h
  src/netmanager.h
)

set(CMAKE_AUTOMOC ON)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/plugins)

set( plugins
  cerebot-leds
  pmod-pushbuttons

  )

foreach(plugin ${plugins})
  add_subdirectory(plugins/${plugin})
endforeach()

add_custom_target(
  simavr_install
  sudo make install -C ${CMAKE_SOURCE_DIR}/include/simavr
)

add_custom_target(
  simavr_build
  make -C ${CMAKE_SOURCE_DIR}/include/simavr
)

include(CPack)

set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Another graphical front end to simavr")
set(CPACK_PACKAGE_NAME "simavr-qt")
set(CPACK_PACKAGE_VERSION "1.0")

find_package(Qt5Widgets)

qt5_wrap_ui ( src src/mainwindow.ui )

include_directories(${includes})

add_definitions(${Qt5Widgets_DEFINITIONS}) 

qt5_add_resources ( resources ${resource_file})

add_executable(${target} ${sources} ${headers} ${resources})

target_link_libraries(${target} ${libs})

add_dependencies(${target} simavr_install)

add_dependencies(simavr_install simavr_build)

qt5_use_modules(${target} Widgets)
