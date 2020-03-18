#!/bin/sh

scan-build -k -o $1 g++ code-example/main.cpp
