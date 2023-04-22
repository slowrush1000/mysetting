cmake_minimum_required(VERSION 3.18.0)
project(util)
set(PROGRAM_NAME                                "util")

# dir
set(SRC_DIR                                     "src")
set(INC_DIR                                     "include")

#set(TEST_SRC_DIR                               "${CMAKE_SOURCE_DIR}/src")
set(INSTALL_DIR                                 "${CMAKE_SOURCE_DIR}/install")
set(EXTERN_DIR                                  "/media/PROJECT02/extern")
#set(EXTERN_DIR                                 "../../../extern")

# git version
execute_process(
    COMMAND git rev-parse --abbrev-ref HEAD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_BRANCH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
execute_process(
    COMMAND git log -1 --format=%h
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_COMMIT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
execute_process(
    COMMAND pwd
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE SOURCE_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

configure_file(${CMAKE_SOURCE_DIR}/libs/util/include/${PROGRAM_NAME}_git.hpp.in ${CMAKE_SOURCE_DIR}/libs/util/include/${PROGRAM_NAME}_git.hpp)

# program name/build dir
set(RUNTIME_OUTPUT_DIRECTORY                    "${CMAKE_SOURCE_DIR}/build/release")
set(ARCHIVE_OUTPUT_DIRECTORY                    "${CMAKE_SOURCE_DIR}/build/release")
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    message("-- Debug build.")
    set(RUNTIME_OUTPUT_DIRECTORY                "${CMAKE_SOURCE_DIR}/build/debug")
    set(ARCHIVE_OUTPUT_DIRECTORY                "${CMAKE_SOURCE_DIR}/build/debug")
    set(PROJECT_EXE_NAME                        "${PROGRAM_NAME}.dbg.exe")
    set(PROJECT_LIB_NAME                        "${PROGRAM_NAME}.dbg")
#    set(PROJECT_TEST_EXE_NAME                   "${PROGRAM_NAME}.dbg.test.exe")
#    set(PROJECT_TEST_LIB_NAME                   "${PROGRAM_NAME}.dbg.test")
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release")
    message("-- Release build.")
    set(RUNTIME_OUTPUT_DIRECTORY                "${CMAKE_SOURCE_DIR}/build/release")
    set(ARCHIVE_OUTPUT_DIRECTORY                "${CMAKE_SOURCE_DIR}/build/release")
    set(PROJECT_EXE_NAME                        "${PROGRAM_NAME}.exe")
    set(PROJECT_LIB_NAME                        "${PROGRAM_NAME}")
#    set(PROJECT_TEST_EXE_NAME                   "${PROGRAM_NAME}.test.exe")
#    set(PROJECT_TEST_LIB_NAME                   "${PROGRAM_NAME}.test")
endif()

# sources/headers
set(PROJECT_MAIN_SOURCE                         "${SRC_DIR}/util_main.cpp")
set(PROJECT_MAIN_HEADER                         "${SRC_DIR}/util_main.hpp")
set(PROJECT_SOURCES                             
                                                "${SRC_DIR}/util_git.cpp"
                                                "${SRC_DIR}/util_log.cpp"
                                                "${SRC_DIR}/util_util.cpp"
                                                "${SRC_DIR}/util_version.cpp"
                                                )
set(PROJECT_HEADERS                             
                                                "${INC_DIR}/util_git.hpp"
                                                "${INC_DIR}/util_log.hpp"
                                                "${INC_DIR}/util_util.hpp"
                                                "${INC_DIR}/util_version.hpp"
                                                )
# build : make -j
include_directories(${INC_DIR})
add_library(${PROJECT_LIB_NAME} STATIC           ${PROJECT_SOURCES})
add_executable(${PROJECT_EXE_NAME}               ${PROJECT_MAIN_SOURCE})
target_link_libraries(${PROJECT_EXE_NAME}        ${PROJECT_LIB_NAME})
set_target_properties(${PROJECT_EXE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${RUNTIME_OUTPUT_DIRECTORY})
set_target_properties(${PROJECT_LIB_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${RUNTIME_OUTPUT_DIRECTORY})

## openmp
#find_package(OpenMP)
#if(OPENMP_FOUND)
#    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
#endif(OPENMP_FOUND)

# spdlog
set(SPDLOG_DIR                              "${EXTERN_DIR}/spdlog")
#set(SPDLOG_DIR                              "/media/PROJECT02/extern/spdlog")
set(SPDLOG_INC_DIR                          "${SPDLOG_DIR}/include")
set(SPDLOG_LIBRARIES                        "${SPDLOG_DIR}/build/libspdlog.a")
include_directories(${SPDLOG_INC_DIR})
target_link_libraries(${PROJECT_EXE_NAME}        ${SPDLOG_LIBRARIES})
#target_link_libraries(${PROJECT_TEST_EXE_NAME}   ${SPDLOG_LIBRARIES})
##include_directories("../{SPDLOG_DIR}/include")
##target_link_libraries(${PROJECT_EXE_NAME}        spdlog)
##find_package(spdlog)
##if(spdlog_FOUND)
##    target_link_libraries(${PROJECT_EXE_NAME} spdlog)
##endif(spdlog_FOUND)

# gzstream
find_package(GZSTREAM)
if (GZSTREAM_FOUND)
    include_directories(${GZSTREAM_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_EXE_NAME} ${GZSTREAM_LIBRARIES})
#    target_link_libraries(${PROJECT_TEST_EXE_NAME} ${GZSTREAM_LIBRARIES})
    target_link_libraries(${PROJECT_EXE_NAME} z)
#    target_link_libraries(${PROJECT_TEST_EXE_NAME} z)
endif(GZSTREAM_FOUND)

# fmt
find_package(fmt)
if(fmt_FOUND)
    #    include_directories(${fmt_INCLUDE_DIRS})
    target_link_libraries(${PROJECT_EXE_NAME} fmt::fmt)
#    target_link_libraries(${PROJECT_TEST_EXE_NAME} fmt::fmt)
endif(fmt_FOUND)

## tcl/tk
#find_package(TCL)
#if(TCL_FOUND)
#    include_directories(${TCL_INCLUDE_PATH})
#    target_link_libraries(${PROJECT_EXE_NAME} ${TCL_LIBRARY})
#endif(TCL_FOUND)

## tomlplusplus
#include_directories("../${TOMLPLUSPLUS_DIR}/include")

# install : make install
install(TARGETS ${PROJECT_EXE_NAME} RUNTIME DESTINATION "${INSTALL_DIR}/bin")
install(TARGETS ${PROJECT_LIB_NAME} ARCHIVE DESTINATION "${INSTALL_DIR}/lib")
install(FILES ${PROJECT_HEADERS} DESTINATION "${INSTALL_DIR}/include")

# test
add_subdirectory(test)