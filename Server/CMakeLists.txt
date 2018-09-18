PROJECT(Server)

set (SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
SET (SRCS
	"${SOURCE_DIR}/main.cpp"
	"${SOURCE_DIR}/Server.cpp"
	"${SOURCE_DIR}/NetClient.cpp"
)

include_directories("${PROJECT_SOURCE_DIR}/include")

add_executable(babel_server ${SRCS})
target_link_libraries(babel_server ${CONAN_LIBS})