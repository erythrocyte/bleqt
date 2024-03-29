cmake_minimum_required(VERSION 3.1.0)

project(ble)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
	set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(Qt5 COMPONENTS Charts REQUIRED)
find_package(Qt5 COMPONENTS Svg REQUIRED)

set(SOURCES
	services/saveFilePathService.cpp

	views/bleFrame.cpp
	views/presenters/bleFramePresenter.cpp

	widgets/dataWidget.cpp
	widgets/satSolverSettsWidget.cpp
	widgets/gridSettsWidget.cpp
	widgets/shockFrontSettsWidget.cpp
	widgets/resultDataWidget.cpp
	widgets/fluidParamsGraphWidget.cpp
	widgets/wellWorkDataWidget.cpp
	widgets/conditionsWidget.cpp
	widgets/boundVisualWidget.cpp
	widgets/tauVisualWidget.cpp
	widgets/fwVisualWidget.cpp
	widgets/dimlesParamsWidget.cpp
	widgets/schemeWidget.cpp

	widgets/models/wellWorkParamsModel.cpp
	widgets/models/boundModel.cpp
	widgets/models/tauModel.cpp
	widgets/models/fwModel.cpp

	widgets/presenters/fluidParamGraphWidgetPresenter.cpp
	widgets/presenters/dataWidgetPresenter.cpp
	widgets/presenters/gridSettsWidgetPresenter.cpp
	widgets/presenters/resultDataWidgetPresenter.cpp
	widgets/presenters/satSolverSettsWidgetPresenter.cpp
	widgets/presenters/shockFrontSettsWidgetPresenter.cpp
	widgets/presenters/wellWorkDataWidgetPresenter.cpp
	widgets/presenters/conditionsWidgetPresenter.cpp
	widgets/presenters/boundVisualWidgetPresenter.cpp
	widgets/presenters/tauVisualWidgetPresenter.cpp
	widgets/presenters/fwVisualWidgetPresenter.cpp
	widgets/presenters/dimlesParamsWidgetPresenter.cpp

	mvp/blePresenter.cpp

	frames/qVerticalLabel.cpp

	bleapp.cpp
	main.cpp
)
qt5_add_resources(SOURCES resources.qrc)

add_executable(${EXE_GUI_TARGET} ${SOURCES})

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -fPIC")

get_target_property(QtCore_location Qt5::Core LOCATION)

target_link_libraries(${EXE_GUI_TARGET} Qt5::Widgets)
target_link_libraries(${EXE_GUI_TARGET} Qt5::Core)
target_link_libraries(${EXE_GUI_TARGET} Qt5::Charts)
target_link_libraries(${EXE_GUI_TARGET} Qt5::Svg)

target_link_libraries(${EXE_GUI_TARGET} ${LIB_BLE_TARGET})

include_directories(${CMAKE_SOURCE_DIR}/src)
include_directories(${CMAKE_SOURCE_DIR}/gui)
include_directories(${CMAKE_SOURCE_DIR}/gui/widgets)
include_directories(${CMAKE_SOURCE_DIR}/gui/widgets/models)
include_directories(${CMAKE_SOURCE_DIR}/gui/widgets/presenters)
include_directories(${CMAKE_SOURCE_DIR}/gui/frames)
include_directories(${CMAKE_SOURCE_DIR}/gui/views)
include_directories(${CMAKE_SOURCE_DIR}/gui/views/presenters)
include_directories(${CMAKE_SOURCE_DIR}/gui/mvp)
