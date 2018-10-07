PROJECT(Client)

set(CMAKE_AUTOMOC ON)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
set(QT_INCLUDES ${Qt5Core_INCLUDE_DIRS})
include_directories(${QT_INCLUDES})
include_directories("include")
QT5_WRAP_CPP(doriannsuce_HEADERS_MOC ${HuggleLite_HEADERS})

set (SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
set (PROJECT_SHAREDINCL_DIR "${PROJECT_SOURCE_DIR}/../shared/include")
set (PROJECT_SHAREDSRC_DIR "${PROJECT_SOURCE_DIR}/../shared/src")

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++0x")
set(CMAKE_INCLUDE_CURRENT_DIR ON)

SET (SRCS
	"${SOURCE_DIR}/main.cpp"
	"${SOURCE_DIR}/mainwindow.cpp"
	"${SOURCE_DIR}/voice.cpp"
	"${SOURCE_DIR}/encode.cpp"
	"${SOURCE_DIR}/Server.cpp"
	"${PROJECT_SHAREDSRC_DIR}/NetworkMessage.cpp"
)

SET (INCLUDES
	"include/mainwindow.h"
	"include/voice.hpp"
	"include/encode.hpp"
	"include/Server.hpp"
)

include_directories(${SOURCE_DIR}/include)
include_directories("${PROJECT_SHAREDINCL_DIR}")

qt5_wrap_ui(UI_GENERATED_HEADERS "ui/mainwindow.ui")

add_executable(babel_client ${SRCS} ${INCLUDES} ${UI_GENERATED_HEADERS})
qt5_use_modules(babel_client Core Widgets)
target_link_libraries(babel_client ${CONAN_LIBS})