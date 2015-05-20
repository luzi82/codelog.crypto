#!/bin/bash

set -e

rm -rf tmp
mkdir tmp

cp data.jpg tmp/

cd tmp

# RSA + SHA256 sign

# generate private key "key.pem"
openssl genpkey -algorithm RSA -out private.pem

# convert "key.pem" to public key
openssl rsa -in private.pem -out public.pem -outform PEM -pubout

# sign with rsa sha256
openssl dgst -sha256 -sign private.pem -binary -out data.jpg.sig data.jpg

# verify
openssl dgst -sha256 -verify public.pem -signature data.jpg.sig data.jpg 
