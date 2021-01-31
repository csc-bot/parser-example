#!/bin/bash

readonly antlr=antlr-4.9.1-complete.jar

mkdir cmake-build-debug
pushd cmake-build-debug
curl -O https://www.antlr.org/download/$antlr
cmake .. \
  -DCMAKE_BUILD_TYPE=Debug \
  -DANTLR_EXECUTABLE=$(pwd)/$antlr
cmake --build .
ctest --verbose
popd
