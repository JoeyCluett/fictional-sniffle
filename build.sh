#!/bin/bash

# build the CPJL message type
cpjl_generate -i ChatMessage.cpjl -cdir ./

# CPJL needs to be cloned in the same  directory as fictional-shuffle
CPJLDIR="-I./../CPJL/lib/cpp/"
STDOPTS="-std=c++11 -march=native -O3 -ffast-math -lpthread"

g++ -o main main.cpp $CPJLDIR $STDOPTS
