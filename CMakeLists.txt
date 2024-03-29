cmake_minimum_required(VERSION 3.1.0)

project(BleQt)

set(APPNAME ble)

# "make install" output
set(LIB_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/lib/${APPNAME}")
set(INCLUDE_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/include/${APPNAME}")
set(EXE_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/bin")
set(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_RPATH}${LIB_INSTALL_DIR})

# set standart
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -fPIC") 

# targets
set(EXE_GUI_TARGET ble)
set(EXE_BIN_TARGET a)
set(LIB_BLE_TARGET libBle)

# "make" output
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

enable_testing()

find_package(Boost REQUIRED)

# adding sub directories which have own CMake files
add_subdirectory(src)
add_subdirectory(gui)
add_subdirectory(tests)
add_subdirectory(bin)

