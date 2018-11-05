#!/usr/bin/env bash
mkdir -p build
cd build
cmake  -DCMAKE_BUILD_TYPE=Debug .. 
# cmake "-DCMAKE_TOOLCHAIN_FILE=${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" ..
cmake --build .
