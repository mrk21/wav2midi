#!/bin/bash
cd $(dirname $0) &&
rm -rf gen &&
mkdir gen &&
cd gen &&
cmake -DCMAKE_CXX_COMPILER=clang++ -DBUILD_TEST=ON ..
