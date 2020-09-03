cmake_minimum_required(VERSION 3.1.0)

project(ble)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

#set (CMAKE_PREFIX_PATH /usr/local/opt/qt5/)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Core REQUIRED)

set (EXE_TARGET ble)

add_executable(${EXE_TARGET}
    main.cpp
)

target_link_libraries(${EXE_TARGET} Qt5::Widgets)
target_link_libraries(${EXE_TARGET} Qt5::Core)

get_target_property(QtCore_location Qt5::Core LOCATION)

target_link_libraries(${EXE_TARGET} ${LIB_BLE_TARGET})
include_directories(${CMAKE_SOURCE_DIR}/src)
