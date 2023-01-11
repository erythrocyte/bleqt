find_package(Boost COMPONENTS log log_setup REQUIRED)
find_package(Threads REQUIRED)
add_definitions(-DBOOST_LOG_DYN_LINK)

set(HEADERS
	calc/models/saturSolverSettings.hpp
	calc/models/saturSolverType.hpp	
	calc/models/diagMatrix.hpp
	calc/models/bleCalc.hpp
	calc/models/bleResultData.hpp

	calc/services/workSigma.hpp
	calc/services/pressureSolver.hpp	
	calc/services/saturSolverNum.hpp
	calc/services/workTimeStep.hpp
	calc/services/saturSolverAnalytic.hpp
	calc/services/workParam.hpp
	calc/services/saturAverService.hpp
	calc/services/saturImplicitSolver.hpp
	
	logging/logger.hpp

	file/services/workFile.hpp

	common/services/workRp.hpp
	common/services/shockFront.hpp
	common/services/commonVector.hpp
	common/services/commonMath.hpp
	common/services/workString.hpp
	common/services/workDir.hpp
	common/services/dataDistributionService.hpp
	common/services/dimensionlessService.hpp
	common/services/wellWorkCalc.hpp

	common/utils/mapInit.hpp

	common/models/inputData.hpp
	common/models/physData.hpp
	common/models/gridType.hpp
	common/models/dynamicData.hpp
	common/models/outputSettings.hpp
	common/models/wellWorkParams.hpp
	common/models/boundCondData.hpp
	common/models/dataDistribution.hpp
	common/models/commonVals.hpp
	common/models/tauData.hpp

	mesh/models/cell.hpp
	mesh/models/face.hpp
	mesh/models/faceType.hpp
	mesh/models/grid.hpp
	mesh/models/node.hpp

	mesh/services/makeGrid.hpp
)

set (SOURCES
	calc/services/workSigma.cpp
	calc/services/pressureSolver.cpp	
	calc/services/saturSolverNum.cpp
	calc/services/workTimeStep.cpp		
	calc/services/saturSolverAnalytic.cpp	
	calc/services/workParam.cpp
	calc/services/saturAverService.cpp
	calc/services/saturImplicitSolver.cpp
	
	calc/models/bleCalc.cpp
	calc/models/bleResultData.cpp
	
	logging/logger.cpp

	file/services/workFile.cpp

	common/models/solverData.cpp

	common/services/shockFront.cpp
	common/services/workRp.cpp
	common/services/commonVector.cpp
	common/services/commonMath.cpp
	common/services/workString.cpp
	common/services/workDir.cpp
	common/services/dataDistributionService.cpp
	common/services/dimensionlessService.cpp
	common/services/wellWorkCalc.cpp

	mesh/models/grid.cpp

	mesh/services/makeGrid.cpp
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

include_directories(${CMAKE_SOURCE_DIR}/src)

target_link_libraries(${LIB_BLE_TARGET} stdc++fs)
