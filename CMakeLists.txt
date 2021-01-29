cmake_minimum_required(VERSION 3.0.0)
project(testat_bintree VERSION 0.1.0)

include(CTest)
enable_testing()

add_executable(testat_bintree main.cpp)
add_library(bintree bintree.cpp)
target_link_libraries(testat_bintree bintree)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
