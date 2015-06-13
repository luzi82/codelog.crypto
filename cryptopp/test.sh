#!/bin/bash

set -e

rm -rf tmp
cp -R res tmp

cd tmp

g++ c000.cpp -lcryptopp -o c000 
./c000

g++ c001.cpp -lcryptopp -o c001 
./c001

g++ c002.cpp -lcryptopp -o c002 
./c002

g++ c003.cpp -lcryptopp -o c003 
./c003
diff data.jpg data.jpg.aes.-
