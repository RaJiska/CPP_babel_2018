PROJECT(Server)

set (SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
SET (SRCS
	"${SOURCE_DIR}/main.cpp"
	"${SOURCE_DIR}/Server.cpp"
	"${SOURCE_DIR}/Client.cpp"
	"${SOURCE_DIR}/NetworkClient.cpp"
	"${SOURCE_DIR}/NetworkMessage.cpp"
	"${SOURCE_DIR}/NetworkMessageHeader.cpp"
)

include_directories("${PROJECT_SOURCE_DIR}/include")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -lboost_serialization")

add_executable(babel_server ${SRCS})
target_link_libraries(babel_server ${CONAN_LIBS})