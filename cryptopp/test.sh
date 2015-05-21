#!/bin/bash

set -e

rm -rf tmp
cp -R res tmp

cd tmp

g++ c000.cpp -lcryptopp -o c000 
./c000

g++ c001.cpp -lcryptopp -o c001 
./c001
