cmake_minimum_required(VERSION 3.10.2)

set(LIB_NAME Polygons)

add_library(${LIB_NAME} STATIC
        Ring.cpp
        Polygon.cpp
        Freespace.cpp
        Geometry.cpp
        FreespaceGenerator.cpp
        RingGenerator.cpp
        PolygonClipper.cpp
        )

target_include_directories(${LIB_NAME} INTERFACE
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
        )

target_link_libraries(${LIB_NAME}
        PUBLIC
        Types
        ClipperLib
)


