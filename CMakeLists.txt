cmake_minimum_required(VERSION 3.1)
project(trefle_engine_c)

# set( CMAKE_VERBOSE_MAKEFILE on )

# Enable C+14 features
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set build type
# set(CMAKE_BUILD_TYPE Release)

find_package(OpenMP)

if(OPENMP_FOUND)
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

# Compiler specific flags
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -ftree-vectorize -mtune=native -march=native -mavx")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS} -static-libstdc++")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Intel")
endif()

include_directories(
        include
        vendor/catch2/single_include
        vendor/json/single_include
        )

set(LINK_LIBRARIES
        )

set(SOURCES
        src/main.cpp
        # Membership functions
        src/membershipfunction_i.cpp
        src/trimf.cpp
        # Linguistic variables
        src/linguisticvariable.cpp
        src/trilv.cpp
        # Fuzzy Rules
        src/fuzzy_rule.cpp
        src/fuzzy_rule_element.cpp
        # Fuzzy Systems
        src/singleton_fis.cpp
        # Json import/export
        src/json_fis_reader.cpp
        )

set(SOURCES_TEST
        tests/fis_lininterp_test.cpp
        tests/fuzzy_labels_generator_test.cpp
        tests/tests.cpp
        )
set(SOURCES_TEST ${SOURCES_TEST} ${SOURCES})

# Make executable
add_library(trefle_engine_c ${SOURCES})
target_link_libraries(trefle_engine_c ${LINK_LIBRARIES})
# add_executable(trefle_engine_c_exe ${SOURCES})

# compile tests only if debug
# TODO: use cmake built-in test mecanisms
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
        # remove the main from SOURCE to only use the main from tests.cpp
        list(REMOVE_ITEM SOURCES_TEST src/main.cpp)
        add_executable(run_tests ${SOURCES_TEST})
        target_link_libraries(run_tests ${LINK_LIBRARIES})
endif()
