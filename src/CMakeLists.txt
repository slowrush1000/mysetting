cmake_minimum_required(VERSION 3.18.0)
project(myname)
set(PROGRAM_NAME                            "myname")

# dir
set(SRC_DIR                                 "${CMAKE_SOURCE_DIR}/src")
set(TEST_SRC_DIR                            "${CMAKE_SOURCE_DIR}/src")
set(INC_DIR                                 "${CMAKE_SOURCE_DIR}/src")
set(INST_DIR                                "${CMAKE_SOURCE_DIR}/install")
set(EXTERN_DIR                              "/media/PROJECT02/extern")
#set(EXTERN_DIR                              "../../../extern")

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
configure_file(${CMAKE_SOURCE_DIR}/src/${PROGRAM_NAME}_git.hpp.in ${CMAKE_SOURCE_DIR}/src/${PROGRAM_NAME}_git.hpp)

# program name/build dir
set(RUNTIME_OUTPUT_DIRECTORY                "${CMAKE_SOURCE_DIR}/build/release")
set(ARCHIVE_OUTPUT_DIRECTORY                "${CMAKE_SOURCE_DIR}/build/release")
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    message("-- Debug build.")
    set(RUNTIME_OUTPUT_DIRECTORY            "${CMAKE_SOURCE_DIR}/build/debug")
    set(ARCHIVE_OUTPUT_DIRECTORY            "${CMAKE_SOURCE_DIR}/build/debug")
    set(MYNAMENAME_EXE_NAME                         "${PROGRAM_NAME}.dbg.exe")
    set(MYNAMENAME_LIB_NAME                         "${PROGRAM_NAME}.dbg")
    set(MYNAMENAME_TEST_EXE_NAME                    "${PROGRAM_NAME}.dbg.test.exe")
    set(MYNAMENAME_TEST_LIB_NAME                    "${PROGRAM_NAME}.dbg.test")
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release")
    message("-- Release build.")
    set(RUNTIME_OUTPUT_DIRECTORY            "${CMAKE_SOURCE_DIR}/build/release")
    set(ARCHIVE_OUTPUT_DIRECTORY            "${CMAKE_SOURCE_DIR}/build/release")
    set(MYNAMENAME_EXE_NAME                         "${PROGRAM_NAME}.exe")
    set(MYNAMENAME_LIB_NAME                         "${PROGRAM_NAME}")
    set(MYNAMENAME_TEST_EXE_NAME                    "${PROGRAM_NAME}.test.exe")
    set(MYNAMENAME_TEST_LIB_NAME                    "${PROGRAM_NAME}.test")
endif()

# sources/headers
set(MYNAMENAME_MAIN_SOURCE                                  "${SRC_DIR}/${PROGRAM_NAME}_main.cpp")
set(MYNAMENAME_MAIN_HEADER                                  "${SRC_DIR}/${PROGRAM_NAME}_main.hpp")
file(GLOB MYNAMENAME_SOURCES LIST_DIRECTORIES true          "${SRC_DIR}/${PROGRAM_NAME}_*.cpp")
file(GLOB MYNAMENAME_HEADERS LIST_DIRECTORIES true          "${SRC_DIR}/${PROGRAM_NAME}_*.hpp")

set(MYNAMENAME_TEST_MAIN_SOURCE                             "${SRC_DIR}/${PROGRAM_NAME}_main.test.cpp")
set(MYNAMENAME_TEST_MAIN_HEADER                             "${SRC_DIR}/${PROGRAM_NAME}_main.test.hpp")
file(GLOB MYNAMENAME_TEST_SOURCES LIST_DIRECTORIES true     "${SRC_DIR}/${PROGRAM_NAME}_*.test.cpp")
file(GLOB MYNAMENAME_TEST_HEADERS LIST_DIRECTORIES true     "${SRC_DIR}/${PROGRAM_NAME}_*.test.hpp")

list(REMOVE_ITEM MYNAMENAME_SOURCES "${MYNAMENAME_MAIN_SOURCE}" ${MYNAMENAME_TEST_SOURCES})
list(REMOVE_ITEM MYNAMENAME_HEADERS "${MYNAMENAME_MAIN_HEADER}" ${MYNAMENAME_TEST_HEADERS})
list(REMOVE_ITEM MYNAMENAME_TEST_SOURCES "${MYNAMENAME_TEST_MAIN_SOURCE}")
list(REMOVE_ITEM MYNAMENAME_TEST_HEADERS "${MYNAMENAME_TEST_MAIN_HEADER}")

# build : make -j
include_directories(${INC_DIR})
add_library(${MYNAMENAME_LIB_NAME} STATIC           ${MYNAMENAME_SOURCES})
add_executable(${MYNAMENAME_EXE_NAME}               ${MYNAMENAME_MAIN_SOURCE})
target_link_libraries(${MYNAMENAME_EXE_NAME}        ${MYNAMENAME_LIB_NAME})
set_target_properties(${MYNAMENAME_EXE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${RUNTIME_OUTPUT_DIRECTORY})
set_target_properties(${MYNAMENAME_LIB_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${RUNTIME_OUTPUT_DIRECTORY})

# googletest : make & ./prograem_name.test.exe
include_directories("${EXTERN_DIR}/googletest/googletest/include")
set(GOOGLETEST_LIBRARIES                    "${EXTERN_DIR}/googletest/build/lib/libgtest.a")
add_executable(${MYNAMENAME_TEST_EXE_NAME}          ${MYNAMENAME_TEST_MAIN_SOURCE} ${MYNAMENAME_TEST_SOURCES})
target_link_libraries(${MYNAMENAME_TEST_EXE_NAME}   ${MYNAMENAME_LIB_NAME})
target_link_libraries(${MYNAMENAME_TEST_EXE_NAME}   ${GOOGLETEST_LIBRARIES})
set_target_properties(${MYNAMENAME_TEST_EXE_NAME}   PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${RUNTIME_OUTPUT_DIRECTORY})
set_target_properties(${MYNAMENAME_TEST_EXE_NAME}   PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${RUNTIME_OUTPUT_DIRECTORY})

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
target_link_libraries(${MYNAMENAME_EXE_NAME}        ${SPDLOG_LIBRARIES})
target_link_libraries(${MYNAMENAME_TEST_EXE_NAME}   ${SPDLOG_LIBRARIES})
##include_directories("../{SPDLOG_DIR}/include")
##target_link_libraries(${MYNAMENAME_EXE_NAME}        spdlog)
##find_package(spdlog)
##if(spdlog_FOUND)
##    target_link_libraries(${MYNAMENAME_EXE_NAME} spdlog)
##endif(spdlog_FOUND)

# gzstream
find_package(GZSTREAM)
if (GZSTREAM_FOUND)
    include_directories(${GZSTREAM_INCLUDE_DIRS})
    target_link_libraries(${MYNAMENAME_EXE_NAME} ${GZSTREAM_LIBRARIES})
    target_link_libraries(${MYNAMENAME_TEST_EXE_NAME} ${GZSTREAM_LIBRARIES})
    target_link_libraries(${MYNAMENAME_EXE_NAME} z)
    target_link_libraries(${MYNAMENAME_TEST_EXE_NAME} z)
endif(GZSTREAM_FOUND)

# fmt
find_package(fmt)
if(fmt_FOUND)
    #    include_directories(${fmt_INCLUDE_DIRS})
    target_link_libraries(${MYNAMENAME_EXE_NAME} fmt::fmt)
    target_link_libraries(${MYNAMENAME_TEST_EXE_NAME} fmt::fmt)
endif(fmt_FOUND)

## tcl/tk
#find_package(TCL)
#if(TCL_FOUND)
#    include_directories(${TCL_INCLUDE_PATH})
#    target_link_libraries(${MYNAMENAME_EXE_NAME} ${TCL_LIBRARY})
#endif(TCL_FOUND)

## tomlplusplus
#include_directories("../${TOMLPLUSPLUS_DIR}/include")

# install : make install
install(TARGETS ${MYNAMENAME_EXE_NAME} RUNTIME DESTINATION "${INST_DIR}/bin")
install(TARGETS ${MYNAMENAME_LIB_NAME} ARCHIVE DESTINATION "${INST_DIR}/lib")
install(FILES ${MYNAMENAME_HEADERS} DESTINATION "${INST_DIR}/include")
