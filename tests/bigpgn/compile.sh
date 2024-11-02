#! /bin/sh
set -x
g++ -std=c++17 -O3 -march=native -o $1 $1.cpp
