#!/bin/bash

set -e

rm -rf venv

python3 -m venv venv
. ./venv/bin/activate
pip install --upgrade pip
pip install cryptography

rm -rf tmp
cp -R res tmp

cd tmp
python3 c000.py
openssl dgst -sha256 -verify c000.public.pem -signature c000.sign data.jpg
