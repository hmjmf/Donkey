#add_subdirectory(${PROJECT_SOURCE_DIR}/test/gtest)
#include_directories(${PROJECT_SOURCE_DIR}/src/gtest)
#include_directories(${PROJECT_SOURCE_DIR}/include/donkey)
#include_directories(${PROJECT_SOURCE_DIR}/include/donkey/test)

file(GLOB beta_srcs ${PROJECT_SOURCE_DIR}/beta/test.cpp)

find_package(Glog REQUIRED)

add_executable(beta_Test ${beta_srcs} SkipList.hpp forward_list.h)

target_link_libraries(beta_Test gtest gtest_main donkey)
target_link_libraries(beta_Test glog::glog)




