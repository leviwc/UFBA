#!/bin/bash
set -e

rm -rf tests
mkdir -p tests/main

g++ -std=c++11 gen.cpp -O2 -o /tmp/gen
g++ -std=c++11 sol.cpp -O2 -o /tmp/sol

for i in {001..010}; do
    echo $i
    /tmp/gen > "tests/main/$i.in"
    /tmp/sol < "tests/main/$i.in" > "tests/main/$i.out"
done
