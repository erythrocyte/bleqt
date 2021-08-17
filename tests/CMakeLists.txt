find_package(Boost COMPONENTS unit_test_framework REQUIRED)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -fPIC -g") 

set (HEADERS
	src_unit_tests/common/services/shockFrontTests.hpp
	src_unit_tests/common/services/workRpTests.hpp
)

set (SOURCE
	# bleTests.cpp
	src_unit_tests/common/services/shockFrontTests.cpp
	src_unit_tests/common/services/workRpTests.cpp
	main.cpp
)

set (EXE_TARGET ble_unit_tests)

add_executable(${EXE_TARGET} ${HEADERS} ${SOURCE})

include_directories(${CMAKE_SOURCE_DIR}/src)
target_link_libraries(${EXE_TARGET} ${LIB_BLE_TARGET})

target_link_libraries(${EXE_TARGET} ${Boost_LIBRARIES})

add_test(NAME TestBle COMMAND $<TARGET_FILE:${EXE_TARGET}>)
