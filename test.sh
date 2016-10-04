#!/bin/bash

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

rm -fv $TMP_BIN
rm -fv $TMP_OUT

g++ -Werror -Wall -O3 -o $TMP_BIN $1

RETURN=$?
if [ ! $RETURN -eq 0 ]; then 
  echo "compile error";
  exit 1
fi

chmod +x $TMP_BIN

$TMP_BIN < "$2.in" > $TMP_OUT
diff "$2.out" $TMP_OUT

if [ "$?" == 0 ]; then
   echo ""
   echo "All went well"
   echo ""
 else
   vimdiff "$2.out" $TMP_OUT
fi
