#!/bin/bash

build/sin-vm dummy file
if [ "$?" = "1" ]; then
	echo "ERROR: sin-vm did not execute dummy program"
	exit 1
fi

build/sin-vm test/test.sin
if [ "$?" = "1" ]; then
	echo "ERROR: sin-vm did not execute test.sin"
	exit 1
fi

build/sin-asm test/test.san
if [ "$?" = "1" ]; then
	echo "ERROR: sin-asm did not execute test.san"
	exit 1
fi
