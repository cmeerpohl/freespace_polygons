PROJECT(ClipperLib)

ADD_LIBRARY(${PROJECT_NAME} STATIC clipper.cpp)

target_include_directories(
	${PROJECT_NAME}
		PUBLIC
			"${CMAKE_CURRENT_SOURCE_DIR}"
)

