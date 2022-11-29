#!/bin/bash -e

startTime=$(date +%s)
echo "launched at "$(date +"%T")

make clean
make Elbrus.o
make Func.o
make ElbrusFunc.o
make all
