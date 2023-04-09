cmake_minimum_required(VERSION 3.0.0)
project(demo VERSION 0.1.0)

include(CTest)
enable_testing()


add_executable(demo main.cpp ItemSet.cpp ItemSet.h)
add_executable(dTest test.cpp ItemSet.cpp ItemSet.h)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
