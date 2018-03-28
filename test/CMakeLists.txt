add_subdirectory(gtest)
include_directories(${PROJECT_SOURCE_DIR}/src/gtest)
include_directories(${PROJECT_SOURCE_DIR}/include/donkey)
include_directories(${PROJECT_SOURCE_DIR}/include/donkey/test)

file(GLOB test_srcs
        ${PROJECT_SOURCE_DIR}/test/test_*.cpp
        ${PROJECT_SOURCE_DIR}/test/dataStructure/test_*.cpp
        ${PROJECT_SOURCE_DIR}/test/util/test_*.cpp
        ${PROJECT_SOURCE_DIR}/test/pattern/test_*.cpp)




find_package(Glog REQUIRED)

add_executable(runTest ${test_srcs})
target_link_libraries(runTest gtest gtest_main donkey)
target_link_libraries(runTest glog::glog)




