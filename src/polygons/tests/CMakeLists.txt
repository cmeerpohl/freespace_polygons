set(PolygonsTestList
        RingTest.cpp
        FreespaceTest.cpp
        PolygonTest.cpp
        FreespaceGeneratorTest.cpp
        RingGeneratorTest.cpp
        PolygonClipperTest.cpp)


if (CATKIN_ENABLE_TESTING)
    catkin_add_gtest(PolygonsTests
            ${PolygonsTestList}
            )
    target_link_libraries(Polygons  ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} Polygons pthread)

elseif(ENABLE_TESTING)
    add_executable(PolygonsTests
            ${PolygonsTestList}
            )
    target_link_libraries(PolygonsTests ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} Polygons pthread)
    gtest_add_tests(
            TARGET PolygonsTests
    )
endif()





