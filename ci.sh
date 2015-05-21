#!/bin/bash

set -e

function t {
	echo ${1} START
	pushd ${1} >> /dev/null
	./test.sh
	popd >> /dev/null
	echo ${1} END
	echo
}

t openssl
