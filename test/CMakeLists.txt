cmake_minimum_required(VERSION 3.18.0)
project(T_PROJECT.test)
set(PROGRAM_NAME                                "T_PROGRAM")

# program name/build dir
set(RUNTIME_OUTPUT_DIRECTORY                    "${CMAKE_SOURCE_DIR}/build/release")
set(ARCHIVE_OUTPUT_DIRECTORY                    "${CMAKE_SOURCE_DIR}/build/release")
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    message("-- Debug build.")
    set(RUNTIME_OUTPUT_DIRECTORY                "${CMAKE_SOURCE_DIR}/build/debug")
    set(ARCHIVE_OUTPUT_DIRECTORY                "${CMAKE_SOURCE_DIR}/build/debug")
    set(PROJECT_TEST_EXE_NAME                   "${PROGRAM_NAME}.dbg.test.exe")
    set(PROJECT_TEST_LIB_NAME                   "${PROGRAM_NAME}.dbg.test")
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release")
    message("-- Release build.")
    set(RUNTIME_OUTPUT_DIRECTORY                "${CMAKE_SOURCE_DIR}/build/release")
    set(ARCHIVE_OUTPUT_DIRECTORY                "${CMAKE_SOURCE_DIR}/build/release")
    set(PROJECT_TEST_EXE_NAME                   "${PROGRAM_NAME}.test.exe")
    set(PROJECT_TEST_LIB_NAME                   "${PROGRAM_NAME}.test")
endif()

# sources/headers
set(PROJECT_TEST_MAIN_SOURCE                    "T_PROGRAM_main.test.cpp")
set(PROJECT_TEST_SOURCES                             
                                                "T_PROGRAM_object.test.cpp"
                                                )

# googletest : make & ./program_name.test.exe
include_directories("${EXTERN_DIR}/googletest/googletest/include")
include_directories("${CMAKE_SOURCE_DIR}/libs")
set(GOOGLETEST_LIBRARIES                        "${EXTERN_DIR}/googletest/build/lib/libgtest.a")
add_executable(${PROJECT_TEST_EXE_NAME}         ${PROJECT_TEST_MAIN_SOURCE} ${PROJECT_TEST_SOURCES})
target_link_libraries(${PROJECT_TEST_EXE_NAME}  ${PROJECT_LIB_NAME})
target_link_libraries(${PROJECT_TEST_EXE_NAME}  ${GOOGLETEST_LIBRARIES})
set_target_properties(${PROJECT_TEST_EXE_NAME}  PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${RUNTIME_OUTPUT_DIRECTORY})
set_target_properties(${PROJECT_TEST_EXE_NAME}  PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${RUNTIME_OUTPUT_DIRECTORY})

#enable_testing()
#if (NOT (TARGET gtest AND TARGET gtest_main))
#    message(FATAL_ERROR "gtest and gtest_main targets NOT found")
#endif()
#
#add_executable(${TEST_PROJECT_NAME} ${LIBRARY_TESTS_SOURCE})
#target_link_libraries(${TEST_PROJECT_NAME} 
#    gtest 
#    gtest_main 
#    ${LIBRARY_NAME} # NOTE: This is defined from project above
#)
#add_test(${TEST_PROJECT_NAME} ${TEST_PROJECT_NAME})
