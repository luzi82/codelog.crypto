#!/bin/bash

set -e

pushd openssl
./test.sh
popd
