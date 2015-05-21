#!/bin/bash

set -e

rm -rf ${0}.tmp
mkdir ${0}.tmp

cp data.jpg ${0}.tmp/

cd ${0}.tmp

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
