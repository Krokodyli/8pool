#!/bin/bash
cd `dirname $0`
mkdir -p build
cd build && cmake ../ && make
SUCCESS=`echo -n $?`
if [[ $SUCCESS == "0" ]]; then
    cd ..
    if [[ $1 == "debug" ]]; then
        gdb bin/game
    else
        bin/game
    fi
fi
