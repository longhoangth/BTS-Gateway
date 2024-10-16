cmake_minimum_required(VERSION 3.0.0)
project(mqtt VERSION 0.1.0)

set(CMAKE_GENERATOR "Unix Makefiles")

include(CTest)
enable_testing()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(mqtt 
    mqtt.cc 
    mqtt.h 
    mqtt_unittest.cc
)
    
target_link_libraries(mqtt ${GTEST_LIBRARIES} mosquitto jsoncpp pthread)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
