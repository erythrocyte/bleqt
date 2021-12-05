cmake_minimum_required(VERSION 3.1.0)

project(ble_calc)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

set (HEADERS
	voids.hpp
)

set (SOURCES
	voids.cpp
	main.cpp
)

add_executable(${EXE_BIN_TARGET} ${HEADERS} ${SOURCES})

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -fPIC")

target_link_libraries(${EXE_BIN_TARGET} ${LIB_BLE_TARGET})
include_directories(${CMAKE_SOURCE_DIR}/src)
