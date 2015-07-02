#!/bin/bash

set -e

rm -rf tmp
cp -R res tmp

cd tmp

# RSA + SHA256 sign

# generate private key "private.pem"
openssl genpkey -algorithm RSA -out private.pem

# convert "private.pem" to public key "public.pem"
openssl rsa -in private.pem -out public.pem -outform PEM -pubout

# sign with rsa sha256
openssl dgst -sha256 -sign private.pem -binary -out data.jpg.pem.sig data.jpg

# verify
openssl dgst -sha256 -verify public.pem -signature data.jpg.pem.sig data.jpg 

# convert "private.pem" to "private.der"
openssl rsa -in private.pem -out private.der -outform DER

# convert "public.pem" to "public.der"
openssl rsa -in public.pem -out public.der -outform DER -pubin -pubout

# sign with rsa sha256 by der
openssl dgst -sha256 -sign private.der -keyform DER -binary -out data.jpg.der.sig data.jpg

# verify
openssl dgst -sha256 -verify public.der -keyform DER -signature data.jpg.der.sig data.jpg 

# diff sign
diff data.jpg.pem.sig data.jpg.der.sig

# more sign to do some test
openssl dgst -sha256 -sign private.der -keyform DER -binary -out c002.cpp.sig c002.cpp


# openssl lib
g++ -o c000 c000.cpp -lcrypto
./c000
xxd -p -c 99 data.jpg.c000 > data.jpg.c000.hex

sha256sum -b data.jpg | head -c 64 > data.jpg.sha256.bin
echo >> data.jpg.sha256.bin # append newline

diff data.jpg.c000.hex data.jpg.sha256.bin


g++ -o c001 c001.cpp -lcrypto
./c001

g++ -o c002 c002.cpp -lcrypto
./c002

g++ -o c003 c003.cpp -lcrypto
./c003


openssl aes-128-cbc -in data.jpg -out data.jpg.enc \
 -K  0123456789abcdef0123456789abcdef \
 -iv fedcba9876543210fedcba9876543210

openssl aes-128-cbc -d -in data.jpg.enc -out data.jpg.enc.dec \
 -K  0123456789abcdef0123456789abcdef \
 -iv fedcba9876543210fedcba9876543210

diff data.jpg data.jpg.enc.dec

g++ -o c004 c004.cpp -lcrypto
./c004

diff data.jpg.enc data.jpg.enc.1

g++ -o c005 c005.cpp -lcrypto
./c005

diff data.jpg data.jpg.enc.dec.1

g++ -o c006 c006.cpp -lcrypto
./c006
diff data.jpg data.jpg.c006

g++ -o c007 c007.cpp -lcrypto
./c007
diff data.jpg data.jpg.enc.-.c007

g++ -o c008 c008.cpp -lcrypto
./c008
diff data.jpg data.jpg.enc.-.c008

g++ -o c009 c009.cpp -lcrypto
./c009
diff data.0.c009 data.1.c009 && exit 1 # the files are different

g++ -o c010 c010.cpp -lcrypto
./c010
diff data.0.c010 data.1.c010 # the files are different

echo ${0} OK
