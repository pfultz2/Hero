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

# Moved down, so everything above is common
if (BIICODE) 
    ADD_BII_TARGETS()
    target_compile_options(${BII_LIB_TARGET} INTERFACE ${CXX_EXTRA_FLAGS})
    return() #finish processing, no need to run cmake below
endif()
