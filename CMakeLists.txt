cmake_minimum_required(VERSION 3.18.0)
project(myProject)
#
set(GOOGLETEST_DIR                          "extern/googletest")
#
add_subdirectory(${GOOGLETEST_DIR})
add_subdirectory(src/libbasic)
add_subdirectory(doc)
