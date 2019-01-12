#! /bin/bash

ASM_SOURCE_FILE=$1
OBJECT_FILE="${1%.*}.o"
EXE=${1%.*}

as -g -o $OBJECT_FILE $ASM_SOURCE_FILE

ld -g -o $EXE -lc -dynamic-linker /lib/ld-linux.so.2  -e main $OBJECT_FILE
