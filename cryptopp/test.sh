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

openssl aes-128-cbc -in data.jpg -out data.jpg.openssl-aes \
 -K  0123456789abcdef0123456789abcdef \
 -iv fedcba9876543210fedcba9876543210

g++ c004.cpp -lcryptopp -o c004
./c004
diff data.jpg data.jpg.openssl-aes.-

g++ c005.cpp -lcryptopp -o c005
./c005
rm -rf tmp

g++ c006.cpp -lcryptopp -o c006
./c006
rm -rf tmp
