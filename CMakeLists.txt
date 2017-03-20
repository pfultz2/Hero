cmake_minimum_required (VERSION 3.0)
project (Hero)
 
# The version number.
set (Hero_VERSION_MAJOR 0)
set (Hero_VERSION_MINOR 1)

include(CheckCXXCompilerFlag)
enable_language(CXX)

if(CMAKE_HOST_APPLE)
    list(APPEND CXX_EXTRA_FLAGS -stdlib=libc++)
endif()

set(ENABLE_CXXFLAGS_TO_CHECK 
    -std=gnu++1y 
    -std=c++1y
    -std=gnu++11 
    -std=c++11
    -std=gnu++0x 
    -std=c++0x)

foreach(flag ${ENABLE_CXXFLAGS_TO_CHECK})
    string(REPLACE "-std=" "_" flag_var ${flag})
    string(REPLACE "+" "x" flag_var ${flag_var})
    check_cxx_compiler_flag("${flag}" COMPILER_HAS_CXX_FLAG${flag_var})
    if(COMPILER_HAS_CXX_FLAG${flag_var})
        list(APPEND CXX_EXTRA_FLAGS ${flag})
        break()
    endif()
endforeach()

install (DIRECTORY include/hero DESTINATION include)

add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} -VV -C ${CMAKE_CFG_INTDIR})

macro(add_test_executable TEST_NAME_)
    set(TEST_NAME "${TEST_NAME_}")
    add_executable (${TEST_NAME} EXCLUDE_FROM_ALL test/${TEST_NAME}.cpp ${ARGN})
    target_compile_options(${TEST_NAME} PUBLIC ${CXX_EXTRA_FLAGS})
    if(WIN32)
        add_test(NAME ${TEST_NAME} WORKING_DIRECTORY ${LIBRARY_OUTPUT_PATH} COMMAND ${TEST_NAME}${CMAKE_EXECUTABLE_SUFFIX})
    else()
        add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
    endif()
    add_dependencies(check ${TEST_NAME})
    set_tests_properties(${TEST_NAME} PROPERTIES FAIL_REGULAR_EXPRESSION "FAILED")
endmacro(add_test_executable)

include(CTest)

include_directories(include)

add_test_executable(attribute)
add_test_executable(empty)
add_test_executable(filter)
add_test_executable(for_each)
add_test_executable(fold)
add_test_executable(join)
add_test_executable(map)
add_test_executable(pair)
add_test_executable(push_back)
add_test_executable(push_front)
add_test_executable(reverse_fold)
add_test_executable(size)
add_test_executable(transform)
add_test_executable(tuple)
add_test_executable(zip)
