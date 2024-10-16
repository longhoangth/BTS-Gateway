cmake_minimum_required(VERSION 3.0.0)
project(json_test VERSION 0.1.0)

set(CMAKE_GENERATOR "Unix Makefiles")

include(CTest)
enable_testing()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(json_test 
    json_test.cc 
    json_test.h 
    register.h 
    json_unittest.cc
    )
    
target_link_libraries(json_test ${GTEST_LIBRARIES} jsoncpp pthread)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
