PROJECT(Client)

set (SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")
SET (SRCS
	"${SOURCE_DIR}/main.cpp"
)

add_executable(babel_client ${SRCS})
target_link_libraries(babel_client ${CONAN_LIBS})