file(GLOB_RECURSE hdrs ${PROJECT_SOURCE_DIR}/include/donkey/*.h*)
file(GLOB_RECURSE srcs ${PROJECT_SOURCE_DIR}/src/donkey/*.cpp)

INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/include/donkey)

project(donkey)

add_library(donkey SHARED ${hdrs} ${srcs})

find_package(Glog REQUIRED)

target_link_libraries(donkey glog::glog)





