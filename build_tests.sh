#!/bin/sh
set -x

cc -std=c99 -Wall -Wextra -pedantic -g -c tests.c DynamicArray.c
cc -g tests.o DynamicArray.o -o tests
