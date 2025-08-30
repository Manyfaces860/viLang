#!/bin/bash

make -C build

if [ "$1" == "debug" ]; then
    shift # remove "debug" so $1 becomes your script/test file
    lldb ./build/vivasvan -- "$@"
else
    ./build/vivasvan "$@"
fi