PROJECT(Server)

set (SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
set (PROJECT_SHAREDINCL_DIR "${PROJECT_SOURCE_DIR}/../shared/include")
set (PROJECT_SHAREDSRC_DIR "${PROJECT_SOURCE_DIR}/../shared/src")
SET (SRCS
	"${SOURCE_DIR}/main.cpp"
	"${SOURCE_DIR}/Server.cpp"
	"${SOURCE_DIR}/Client.cpp"
	"${SOURCE_DIR}/NetworkClient.cpp"
	"${PROJECT_SHAREDSRC_DIR}/NetworkMessage.cpp"
)

include_directories("${PROJECT_SOURCE_DIR}/include")
include_directories("${PROJECT_SHAREDINCL_DIR}")

add_executable(babel_server ${SRCS})
target_link_libraries(babel_server ${CONAN_LIBS})