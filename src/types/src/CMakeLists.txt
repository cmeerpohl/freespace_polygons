cmake_minimum_required(VERSION 3.10.2)

set(LIB_NAME Types)

add_library(${LIB_NAME} STATIC
        Point.cpp
        PoseSE2.cpp
        OccupancyMap.cpp
        )

target_include_directories(${LIB_NAME} INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/
        )

target_link_libraries(${LIB_NAME}
        PUBLIC
        bslam-utils
)


