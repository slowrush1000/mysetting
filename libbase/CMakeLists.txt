cmake_minimum_required(VERSION 3.18.0)
project(libbasic)
set(PROGRAM_NAME                            "my_basic")

# Location of additional cmake modules 
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" "${CMAKE_MODULE_PATH}")

# c++ standard
set(CMAKE_CXX_STANDARD                      17)
set(CMAKE_CXX_STANDARD_REQUIRED             ON)

# dir
set(SRC_DIR                                 "${CMAKE_SOURCE_DIR}/src/${PROJECT_NAME}")
set(TEST_SRC_DIR                            "${CMAKE_SOURCE_DIR}/src/${PROJECT_NAME}")
set(INC_DIR                                 "${SRC_DIR}")
set(DOC_DIR                                 "${CMAKE_SOURCE_DIR}/doc")
set(INST_DIR                                "${CMAKE_SOURCE_DIR}/install")

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
configure_file(${CMAKE_SOURCE_DIR}/src/${PROJECT_NAME}/${PROGRAM_NAME}_git.hpp.in ${CMAKE_SOURCE_DIR}/src/${PROJECT_NAME}/${PROGRAM_NAME}_git.hpp)

# program name/build dir
set(RUNTIME_OUTPUT_DIRECTORY                "${CMAKE_SOURCE_DIR}/build/release")
set(ARCHIVE_OUTPUT_DIRECTORY                "${CMAKE_SOURCE_DIR}/build/release")
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    message("-- Debug build.")
    set(RUNTIME_OUTPUT_DIRECTORY            "${CMAKE_SOURCE_DIR}/build/debug")
    set(ARCHIVE_OUTPUT_DIRECTORY            "${CMAKE_SOURCE_DIR}/build/debug")
    set(MY_EXE_NAME                         "${PROGRAM_NAME}.dbg.exe")
    set(MY_LIB_NAME                         "${PROGRAM_NAME}.dbg")
    set(MY_TEST_EXE_NAME                    "${PROGRAM_NAME}.dbg.test.exe")
    set(MY_TEST_LIB_NAME                    "${PROGRAM_NAME}.dbg.test")
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release")
    message("-- Release build.")
    set(RUNTIME_OUTPUT_DIRECTORY            "${CMAKE_SOURCE_DIR}/build/release")
    set(ARCHIVE_OUTPUT_DIRECTORY            "${CMAKE_SOURCE_DIR}/build/release")
    set(MY_EXE_NAME                         "${PROGRAM_NAME}.exe")
    set(MY_LIB_NAME                         "${PROGRAM_NAME}")
    set(MY_TEST_EXE_NAME                    "${PROGRAM_NAME}.test.exe")
    set(MY_TEST_LIB_NAME                    "${PROGRAM_NAME}.test")
endif()

# sources/headers
set(MY_MAIN_SOURCE                                  "${SRC_DIR}/${PROGRAM_NAME}_main.cpp")
set(MY_MAIN_HEADER                                  "${SRC_DIR}/${PROGRAM_NAME}_main.hpp")
set(MY_TEST_MAIN_SOURCE                             "${SRC_DIR}/${PROGRAM_NAME}_main.test.cpp")
set(MY_TEST_MAIN_HEADER                             "${SRC_DIR}/${PROGRAM_NAME}_main.test.hpp")

file(GLOB MY_SOURCES LIST_DIRECTORIES true          "${SRC_DIR}/${PROGRAM_NAME}_*.cpp")
file(GLOB MY_HEADERS LIST_DIRECTORIES true          "${SRC_DIR}/${PROGRAM_NAME}_*.hpp")
file(GLOB MY_TEST_SOURCES LIST_DIRECTORIES true     "${SRC_DIR}/${PROGRAM_NAME}_*.test.cpp")
file(GLOB MY_TEST_HEADERS LIST_DIRECTORIES true     "${SRC_DIR}/${PROGRAM_NAME}_*.test.hpp")

list(REMOVE_ITEM MY_SOURCES "${MY_MAIN_SOURCE}" ${MY_TEST_SOURCES})
list(REMOVE_ITEM MY_HEADERS "${MY_MAIN_HEADER}" ${MY_TEST_HEADERS})
list(REMOVE_ITEM MY_TEST_SOURCES "${MY_TEST_MAIN_SOURCE}")
list(REMOVE_ITEM MY_TEST_HEADERS "${MY_TEST_MAIN_HEADER}")

# build : make -j
include_directories(${INC_DIR})
add_library(${MY_LIB_NAME} STATIC           ${MY_SOURCES})
add_executable(${MY_EXE_NAME}               ${MY_MAIN_SOURCE})
target_link_libraries(${MY_EXE_NAME}        ${MY_LIB_NAME})
set_target_properties(${MY_EXE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${RUNTIME_OUTPUT_DIRECTORY})
set_target_properties(${MY_LIB_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${RUNTIME_OUTPUT_DIRECTORY})

# library
#find_package(FMT)
#if(FMT_FOUND)
#    include_directories(${FMT_INCLUDE_DIRS})
#    target_link_libraries(${MY_EXE_NAME} ${FMT_LIBRARIES})
#endif(FMT_FOUND)

# googletest : make & ./spflib.test.exe
include_directories("${GOOGLETEST_DIR}/googletest/include")
add_executable(${MY_TEST_EXE_NAME}          ${MY_TEST_MAIN_SOURCE} ${MY_TEST_SOURCES})
target_link_libraries(${MY_TEST_EXE_NAME} PUBLIC ${MY_LIB_NAME} gtest)
set_target_properties(${MY_TEST_EXE_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${RUNTIME_OUTPUT_DIRECTORY})
set_target_properties(${MY_TEST_EXE_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${RUNTIME_OUTPUT_DIRECTORY})

# ctags : make ctags
add_custom_target(ctags
    COMMENT "Generate tags file with ctags"
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMAND ctags -R --c++-kinds=+p --fields=+iaS --extra=+q ${CMAKE_SOURCE_DIR}
    COMMAND cp -f tags ${CMAKE_SOURCE_DIR}/src/${PROJECT_NAME}
)

# install : make install
install(TARGETS ${MY_EXE_NAME} RUNTIME DESTINATION "${INST_DIR}/bin")
install(TARGETS ${MY_LIB_NAME} ARCHIVE DESTINATION "${INST_DIR}/lib")
install(FILES ${MY_HEADERS} DESTINATION "${INST_DIR}/include/${PROJECT_NAME}")
