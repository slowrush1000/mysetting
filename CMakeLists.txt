cmake_minimum_required(VERSION 3.18.0)
project(T_PROJECT)
set(PROGRAM_NAME                            "T_PROGRAM")

# Location of additional cmake modules 
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" "${CMAKE_MODULE_PATH}")

# c++ standard
set(CMAKE_CXX_STANDARD                      20)
set(CMAKE_CXX_STANDARD_REQUIRED             ON)

## google
#set(GOOGLETEST_DIR                          "extern/googletest")
#add_subdirectory(${GOOGLETEST_DIR})
## spdlog
#set(SPDLOG_DIR                              "extern/spdlog")
#add_subdirectory(${SPDLOG_DIR})
## toml++
#set(TOMLPLUSPLUS_DIR                        "extern/tomlplusplus")
#add_subdirectory(${TOMLPLUSPLUS_DIR})

# libraries
set(PROJECT_NAME                            "T_PROJECT")
set(PROJECT_SRC_DIR                         "src")
#set(PROJECT_LIBS_DIR                        "libs")
#set(PROJECT_LIBS                            
#                                            "util")
#foreach(LIBRARY ${PROJECT_LIBS})
#    add_subdirectory("${PROJECT_LIBS_DIR}/${LIBRARY}")
#endforeach(LIBRARY ${PROJECT_LIBS})
add_subdirectory(docs)

# dir
set(SRC_DIR                                     "src")
set(INC_DIR                                     "include")

#set(TEST_SRC_DIR                               "${CMAKE_SOURCE_DIR}/src")
set(INSTALL_DIR                                 "${CMAKE_SOURCE_DIR}/install")
#set(EXTERN_DIR                                  "/media/PROJECT02/extern")
#set(EXTERN_DIR                                 "../../../extern")

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
set(PROJECT_MAIN_SOURCE                         "${SRC_DIR}/T_PROGRAM_main.cpp")
set(PROJECT_MAIN_HEADER                         "${SRC_DIR}/T_PROGRAM_main.hpp")
set(PROJECT_SOURCES                             "")
set(PROJECT_HEADERS                             "")
set(PROJECT_SOURCES                             
                                               "${SRC_DIR}/T_PROGRAM_object.cpp"
                                               )
set(PROJECT_HEADERS                             
                                               "${INC_DIR}/T_PROGRAM_object.hpp"
                                               )
# build : make -j
include_directories(${INC_DIR})
set(PROJECT_SOURCES_LENGTH                      "")
list(LENGTH PROJECT_SOURCES PROJECT_SOURCES_LENGTH)
add_library(${PROJECT_LIB_NAME} STATIC           ${PROJECT_SOURCES})
add_executable(${PROJECT_EXE_NAME}               ${PROJECT_MAIN_SOURCE})
target_link_libraries(${PROJECT_EXE_NAME}        ${PROJECT_LIB_NAME})
set_target_properties(${PROJECT_EXE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${RUNTIME_OUTPUT_DIRECTORY})
set_target_properties(${PROJECT_LIB_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${RUNTIME_OUTPUT_DIRECTORY})

# googletest : make & ./prograem_name.test.exe
#include_directories("${EXTERN_DIR}/googletest/googletest/include")
#set(GOOGLETEST_LIBRARIES                    "${EXTERN_DIR}/googletest/build/lib/libgtest.a")
#add_executable(${PROJECT_TEST_EXE_NAME}          ${PROJECT_TEST_MAIN_SOURCE} ${PROJECT_TEST_SOURCES})
#target_link_libraries(${PROJECT_TEST_EXE_NAME}   ${PROJECT_LIB_NAME})
#target_link_libraries(${PROJECT_TEST_EXE_NAME}   ${GOOGLETEST_LIBRARIES})
#set_target_properties(${PROJECT_TEST_EXE_NAME}   PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${RUNTIME_OUTPUT_DIRECTORY})
#set_target_properties(${PROJECT_TEST_EXE_NAME}   PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${RUNTIME_OUTPUT_DIRECTORY})

## openmp
#find_package(OpenMP)
#if(OPENMP_FOUND)
#    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
#endif(OPENMP_FOUND)

## yh::util
#set(UTIL_DIR                              "${CMAKE_SOURCE_DIR}/libs")
##set(UTIL_DIR                              "${CMAKE_SOURCE_DIR}/libs/util")
##set(UTIL_DIR                              "/media/PROJECT02/extern/spdlog")
#set(UTIL_INC_DIR                          "${UTIL_DIR}")
#if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
#set(UTIL_LIBRARIES                        "util.dbg")
#elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release")
#set(UTIL_LIBRARIES                        "util")
#endif()
#include_directories(${UTIL_INC_DIR})
#target_link_libraries(${PROJECT_EXE_NAME}        ${UTIL_LIBRARIES})

## spdlog
#set(SPDLOG_DIR                              "${EXTERN_DIR}/spdlog")
##set(SPDLOG_DIR                              "/media/PROJECT02/extern/spdlog")
#set(SPDLOG_INC_DIR                          "${SPDLOG_DIR}/include")
#set(SPDLOG_LIBRARIES                        "${SPDLOG_DIR}/build/libspdlog.a")
#include_directories(${SPDLOG_INC_DIR})
#target_link_libraries(${PROJECT_EXE_NAME}        ${SPDLOG_LIBRARIES})
##target_link_libraries(${PROJECT_TEST_EXE_NAME}   ${SPDLOG_LIBRARIES})
###include_directories("../{SPDLOG_DIR}/include")
###target_link_libraries(${PROJECT_EXE_NAME}        spdlog)
###find_package(spdlog)
###if(spdlog_FOUND)
###    target_link_libraries(${PROJECT_EXE_NAME} spdlog)
###endif(spdlog_FOUND)

## gzstream
#find_package(GZSTREAM)
#if (GZSTREAM_FOUND)
#    include_directories(${GZSTREAM_INCLUDE_DIRS})
#    target_link_libraries(${PROJECT_EXE_NAME} ${GZSTREAM_LIBRARIES})
##    target_link_libraries(${PROJECT_TEST_EXE_NAME} ${GZSTREAM_LIBRARIES})
#    target_link_libraries(${PROJECT_EXE_NAME} z)
##    target_link_libraries(${PROJECT_TEST_EXE_NAME} z)
#endif(GZSTREAM_FOUND)
#
## fmt
#find_package(fmt)
#if(fmt_FOUND)
#    #    include_directories(${fmt_INCLUDE_DIRS})
#    target_link_libraries(${PROJECT_EXE_NAME} fmt::fmt)
##    target_link_libraries(${PROJECT_TEST_EXE_NAME} fmt::fmt)
#endif(fmt_FOUND)

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

# ctags : make ctags
add_custom_target(ctags
    COMMENT "Generate tags file with ctags"
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMAND ctags -R --c++-kinds=+p --fields=+iaS --extra=+q ${CMAKE_SOURCE_DIR}
    COMMAND cp -f tags ${CMAKE_SOURCE_DIR}/src
)

## test
#add_subdirectory(test)
