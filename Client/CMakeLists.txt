# PROJECT(Client)

# set(CMAKE_AUTOMOC ON)
# find_package(Qt5Core REQUIRED)
# set(QT_INCLUDES ${Qt5Core_INCLUDE_DIRS})
# include_directories(${QT_INCLUDES})
# include_directories("include")
# QT5_WRAP_CPP(doriannsuce_HEADERS_MOC ${HuggleLite_HEADERS})

# set (SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
# set (PROJECT_SHAREDINCL_DIR "${PROJECT_SOURCE_DIR}/../shared/include")
# set (PROJECT_SHAREDSRC_DIR "${PROJECT_SOURCE_DIR}/../shared/src")

# set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++0x")
# set(CMAKE_PREFIX_PATH "/opt/Qt/5.1.1/gcc_64")
# set(CMAKE_INCLUDE_CURRENT_DIR ON)

# SET (SRCS
# 	"${SOURCE_DIR}/main.cpp"
# 	"${SOURCE_DIR}/mainwindow.cpp"
# 	"${SOURCE_DIR}/voice.cpp"
# 	"${SOURCE_DIR}/encode.cpp"
# 	"${SOURCE_DIR}/Server.cpp"
# 	"${PROJECT_SHAREDSRC_DIR}/NetworkMessage.cpp"
# )

# include_directories(${SOURCE_DIR}/include)
# include_directories("${PROJECT_SHAREDINCL_DIR}")

# add_executable(babel_client ${SRCS})
# qt5_use_modules(babel_client Core Widgets Network)
# target_link_libraries(babel_client ${CONAN_LIBS})


cmake_minimum_required (VERSION 2.6)
PROJECT(Client)


set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)

set(QT_INCLUDES ${Qt5Core_INCLUDE_DIRS})
include_directories(${QT_INCLUDES})
include_directories("include")

set(Client_SOURCES "src/main.cpp" "src/mainwindow.cpp")
set(Client_HEADERS "include/mainwindow.h")
set(Client_UI "ui/mainwindow.ui")

QT5_WRAP_UI(UI_GENERATED_HEADERS ${Client_UI})
#QT5_WRAP_CPP(Client_HEADERS_MOC ${HuggleLite_HEADERS})


add_executable(babel_client ${Client_SOURCES} ${Client_HEADERS} ${UI_GENERATED_HEADERS})
qt5_use_modules(babel_client Core Widgets Network)
target_link_libraries(babel_client ${CONAN_LIBS})