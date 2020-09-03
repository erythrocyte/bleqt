find_package(Boost COMPONENTS unit_test_framework REQUIRED)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall") 

set (test_ble_source
	bleTests.cpp
)

set (EXE_TARGET ble_unit_tests)

add_executable(${EXE_TARGET} ${test_ble_source})

include_directories(${CMAKE_SOURCE_DIR}/src)
target_link_libraries(${EXE_TARGET} ${LIB_BLE_TARGET})

target_link_libraries(${EXE_TARGET} ${Boost_LIBRARIES})


add_test(NAME TestBle COMMAND ${EXE_TARGET})
