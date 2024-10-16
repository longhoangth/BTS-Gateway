cmake_minimum_required(VERSION 3.0.0)
project(http_excecutable VERSION 0.1.0)

include(CTest)
enable_testing()

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the source and header directories
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Collect the source files
file(GLOB SOURCES "${SOURCE_DIR}/*.cpp")

# Collect the header files
file(GLOB HEADERS "${HEADERS_DIR}/*.h}")

add_executable(http_excecutable)

# Add source files to target
target_sources(http_excecutable PRIVATE ${SOURCES} ${HEADERS})

# Add include directories to target
target_include_directories(http_excecutable PRIVATE ${HEADER_DIR})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

