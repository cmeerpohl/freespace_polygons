set(TypesTestList
        OccupancyMapTest.cpp)


if (CATKIN_ENABLE_TESTING)
    catkin_add_gtest(TypesTests
            ${TypesTestList}
            )
    target_link_libraries(TypesTests  ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} Types pthread)

elseif(ENABLE_TESTING)
    add_executable(TypesTests
            ${TypesTestList}
            )
    target_link_libraries(TypesTests ${GTEST_LIBRARIES} ${GTEST_MAIN_LIBRARIES} Types pthread)
    gtest_add_tests(
            TARGET TypesTests
    )
endif()





