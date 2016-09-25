#!/bin/bash

set -e

TMP_BIN="/tmp/test.bin"
TMP_OUT="/tmp/test.out"

usage() {
   echo ""
   echo "Usage: $0 SOURCE_CODE TEST_SET_NAME"
   echo ""
}

if [ -z "$1" ]; then
    echo "too few arguments"
    echo "first argument has to be the the source file"
    usage
    exit 2
fi

if [ -z "$2" ]; then
    echo "too few arguments"
    echo "second argument has to be the test set name"
    usage
    exit 2
fi

rm -v $TMP_BIN
rm -v $TMP_OUT

g++  -Wall -O3 -o $TMP_BIN $1

chmod +x $TMP_BIN

$TMP_BIN < "$2.in" > $TMP_OUT
diff "$2.out" $TMP_OUT

if [ "$?" == 0 ]; then
   echo ""
   echo "All went well"
   echo ""
fi
