#!/bin/bash
cd $(dirname $0) &&
rm -rf gen &&
mkdir gen &&
cd gen &&
cmake -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_CXX_CLANG_TIDY=clang-tidy -DBUILD_TEST=ON ..
