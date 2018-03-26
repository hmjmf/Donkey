cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++0x")

set (Donkey_VERSION_MAJOR 1)
set (Donkey_VERSION_MINOR 0)





set(Donkey_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(Donkey_SRC_DIR ${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_BINARY_DIR})

add_subdirectory(src/donkey)
add_subdirectory(test)

if(EXISTS ${PROJECT_SOURCE_DIR}/tmp)
    add_subdirectory(tmp)
endif()







