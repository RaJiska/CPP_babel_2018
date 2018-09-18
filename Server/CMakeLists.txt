PROJECT(Server)

set (SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
SET (SRCS
	"${SOURCE_DIR}/main.cpp"
)

add_executable(babel_server ${SRCS})
target_link_libraries(babel_server ${CONAN_LIBS})