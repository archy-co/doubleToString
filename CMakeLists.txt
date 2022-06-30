cmake_minimum_required(VERSION 3.15)

#! Check every comment after the "#!"

#! CHANGE YOUR PROJECT NAME
#  It is used as your project's main executable name. 
set(PROJECT_NAME dtos_time)
project(${PROJECT_NAME} C CXX) # project(${PROJECT_NAME} C CXX ASM)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

##########################################################
# User configurable options of the template
##########################################################
# Note: symbols like WARNINGS_AS_ERRORS in configuration are intentionally variables
# and not CMake options --using options creates too much problem for students.

#! It is a good practice to set "WARNINGS_AS_ERRORS" ON,
#  but sometimes it creates too much trouble, so default is OFF.
set(WARNINGS_AS_ERRORS OFF)

#! Always use PVS Studio while developing. 
set(ENABLE_PVS_STUDIO OFF)

#! Select appropriate sanitizers.
#  Definitely enable sanitizers while developing.
#  Disable it for the production builds and before submitting for grading.
#  Only one of Memory (MSAN), Address (ASAN), or Thread (TSan)
#  sanitizers is applicable at the time -- the first defined.

#! UndefinedBehaviorSanitizer (UBSan)
#  Info: https://clang.llvm.org/docs/UndefinedBehaviorSanitizer.html
set(ENABLE_UBSan OFF)
#! AddressSanitizer -- detects use after free or after scope exit,
#  memory overflows and leaks.  
#  Info: https://github.com/google/sanitizers/wiki/AddressSanitizer
set(ENABLE_ASAN OFF)
#! ThreadSanitizer -- detects data races.
set(ENABLE_TSan OFF)
#! MemorySanitizer detects uninitialized memory reads 
#  Info: https://github.com/google/sanitizers/wiki/MemorySanitizer
set(ENABLE_MSAN OFF)


#! Be default -- build release version if not specified otherwise.
if (NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif ()

# Warnings as errors should be imported here -- do not move this line
include(cmake/CompilerWarnings.cmake)

##########################################################
# Project files, packages, libraries and so on
##########################################################


#! Project main executable source compilation
add_executable(${PROJECT_NAME}
    src/main.cpp
    include/main.hpp
    src/methods.cpp
    include/methods.hpp
    strtk/strtk.hpp
    include/custom.hpp
    src/custom.cpp)


##############     RYU double conversion algorithm    ######################
set(RYU_FILES
    ryu/common.h
    ryu/d2fixed.c
    ryu/d2fixed_full_table.h
    ryu/d2s.c
    ryu/d2s_full_table.h
    ryu/d2s_intrinsics.h
    ryu/d2s_small_table.h
    ryu/digit_table.h
    ryu/f2s.c
    ryu/f2s_full_table.h
    ryu/f2s_intrinsics.h
    ryu/generic_128.c
    ryu/generic_128.h
    ryu/ryu_generic_128.h
    ryu/ryu.h
    ryu/ryu_parse.h
    ryu/s2d.c
    ryu/s2f.c)

add_library(ryu SHARED ${RYU_FILES})
############################################################################


################     Google double conversion     ##########################
set(GOOGLE_DTOA_FILES
    double-conversion/bignum.h
    double-conversion/cached-powers.h
    double-conversion/diy-fp.h
    double-conversion/double-conversion.h
    double-conversion/double-to-string.h
    double-conversion/fast-dtoa.h
    double-conversion/fixed-dtoa.h
    double-conversion/ieee.h
    double-conversion/string-to-double.h
    double-conversion/strtod.h
    double-conversion/utils.h
    double-conversion/bignum.cc
    double-conversion/bignum-dtoa.cc
    double-conversion/cached-powers.cc
    double-conversion/double-to-string.cc
    double-conversion/fast-dtoa.cc
    double-conversion/fixed-dtoa.cc
    double-conversion/string-to-double.cc
    double-conversion/strtod.cc)

add_library(google-dtoa SHARED ${GOOGLE_DTOA_FILES})
set_target_properties(google-dtoa PROPERTIES
                                  VERSION 1
                                  SOVERSION 3)
############################################################################


find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Boost 1.71.0 COMPONENTS program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME} Boost::program_options)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
target_link_libraries(${PROJECT_NAME} ryu)
target_link_libraries(${PROJECT_NAME} google-dtoa)

target_include_directories(${PROJECT_NAME}
                    PUBLIC ${CMAKE_SOURCE_DIR}
                    PUBLIC ${CMAKE_SOURCE_DIR}/include
                    PUBLIC ${CMAKE_SOURCE_DIR}/floaxie/include)


##########################################################
# Fixed CMakeLists.txt part 
##########################################################

INSTALL(PROGRAMS
		$<TARGET_FILE:${PROJECT_NAME}>	# ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}
		DESTINATION bin)

# Define ALL_TARGETS variable to use in PVS and Sanitizers
set(ALL_TARGETS ${PROJECT_NAME})

# Include CMake setup
include(cmake/main-config.cmake)
