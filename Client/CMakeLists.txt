PROJECT(Client)

set(CMAKE_AUTOMOC ON)
find_package(Qt5Core REQUIRED)
set(QT_INCLUDES ${Qt5Core_INCLUDE_DIRS})
include_directories(${QT_INCLUDES})
include_directories("include")
QT5_WRAP_CPP(doriannsuce_HEADERS_MOC ${HuggleLite_HEADERS})

set (SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++0x")
set(CMAKE_PREFIX_PATH "/opt/Qt/5.1.1/gcc_64")
set(CMAKE_INCLUDE_CURRENT_DIR ON)
SET (SRCS
	"${SOURCE_DIR}/main.cpp"
	"${SOURCE_DIR}/mainwindow.cpp"
	"${SOURCE_DIR}/voice.cpp"
)

include_directories(${SOURCE_DIR}/include)

add_executable(babel_client ${SRCS})
qt5_use_modules(babel_client Core Widgets)
target_link_libraries(babel_client ${CONAN_LIBS})