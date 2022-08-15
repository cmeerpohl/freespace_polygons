set(CollisionTestList
        RingTest.cpp
        FreespaceTest.cpp
        PolygonTest.cpp
        FreespaceGeneratorTest.cpp
        RingGeneratorTest.cpp
        PolygonClipperTest.cpp
        OccupancyMapTest.cpp)


if (CATKIN_ENABLE_TESTING)
    catkin_add_gtest(CollisionTests
            ${CollisionTestList}
            )
    target_link_libraries(CollisionTests  ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} Collision pthread)

elseif(ENABLE_TESTING)
    add_executable(CollisionTests
            ${CollisionTestList}
            )
    target_link_libraries(CollisionTests ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} Collision pthread)
    gtest_add_tests(
            TARGET CollisionTests
    )
endif()





