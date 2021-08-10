find_package(Boost COMPONENTS log log_setup REQUIRED)
find_package(Threads REQUIRED)
add_definitions(-DBOOST_LOG_DYN_LINK)

set(HEADERS 
	inputData.hpp
	physData.hpp
	modelData.hpp
	gridData.hpp
	gridType.hpp
	saturSolverSettings.hpp
	saturSolverType.hpp
	outputSettings.hpp
	dynamicData.hpp
	diagMatrix.hpp
	cell.hpp
	grid.hpp
	makeGrid.hpp
	workSigma.hpp
	pressureSolver.hpp
	faceType.hpp
	workRp.hpp
	saturSolverNum.hpp
	workTimeStep.hpp
	shockFront.hpp
	commonMath.hpp
	saturSolverAnalytic.hpp
	commonVector.hpp
	workParam.hpp
	mapInit.hpp
	bleCalc.hpp
	workString.hpp
	logging/logger.hpp
	file/services/workFile.hpp
)

set (SOURCES
	makeGrid.cpp
	workSigma.cpp
	pressureSolver.cpp
	workRp.cpp
	saturSolverNum.cpp
	workTimeStep.cpp
	shockFront.cpp
	commonMath.cpp
	saturSolverAnalytic.cpp
	commonVector.cpp
	workParam.cpp
	bleCalc.cpp
	workString.cpp
	logging/logger.cpp
	file/services/workFile.cpp
)

source_group ("Header Files" FILES ${HEADERS})
source_group ("Source Files" FILES ${SOURCES})

add_library(${LIB_BLE_TARGET} SHARED ${HEADERS} ${SOURCES})

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -fPIC") 

install(TARGETS ${LIB_BLE_TARGET}
	ARCHIVE DESTINATION ${LIB_INSTALL_DIR}
	LIBRARY DESTINATION ${LIB_INSTALL_DIR}
)

target_link_libraries(${LIB_BLE_TARGET} ${Boost_LIBRARIES})
