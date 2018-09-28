PROJECT(Server)

set (SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
SET (SRCS
	"${SOURCE_DIR}/main.cpp"
	"${SOURCE_DIR}/Server.cpp"
	"${SOURCE_DIR}/Client.cpp"
	"${SOURCE_DIR}/NetworkClient.cpp"
	"${SOURCE_DIR}/NetworkMessage.cpp"
	"${SOURCE_DIR}/NetworkMessageLogin.cpp"
	"${SOURCE_DIR}/NetworkMessageLogout.cpp"
	"${SOURCE_DIR}/NetworkMessageClientJoined.cpp"
	"${SOURCE_DIR}/NetworkMessageClientLeft.cpp"
	"${SOURCE_DIR}/NetworkMessageHeader.cpp"
)

include_directories("${PROJECT_SOURCE_DIR}/include")

add_executable(babel_server ${SRCS})
target_link_libraries(babel_server ${CONAN_LIBS})