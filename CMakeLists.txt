cmake_minimum_required(VERSION 3.10.2)

project(freespace_polygons)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#set(CMAKE_VERBOSE_MAKEFILE ON)
add_compile_options(-Wall -Wextra -fPIC)

include(CMakeDependentOption)
cmake_dependent_option(ENABLE_TESTING "Enable Tests" ON
        "CATKIN_ENABLE_TESTING" ON)

#find_package(catkin REQUIRED COMPONENTS
#        roscpp
#        roslib
#
#        )

find_package(Eigen3 QUIET)
if(NOT EIGEN3_FOUND)
#    find_package(PkgConfig REQUIRED)
#    pkg_check_modules(EIGEN3 REQUIRED eigen3)
    set(EIGEN3_INCLUDE_DIR ${EIGEN3_INCLUDE_DIRS})
endif()

#if(ENABLE_TESTING)
#    find_package( rostest REQUIRED gtest)
#endif()

#catkin_package( CATKIN_DEPENDS
#
#        )

include_directories(
        include
        SYSTEM
#        ${catkin_INCLUDE_DIRS}
        ${EIGEN3_INCLUDE_DIR}
)

find_package(GTest REQUIRED)
enable_testing()

#if(catkin_FOUND)
#    add_definitions(-DHAVE_ROS)
#endif()

if (NOT CMAKE_BUILD_TYPE MATCHES Release)
    add_definitions(-DDEBUG_OUTPUT)
endif()

add_subdirectory(src)
add_subdirectory(external)