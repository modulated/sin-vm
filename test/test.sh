#!/bin/bash

build/sin-vm dummy file
if [ "$?" = "1" ]; then
	echo "ERROR: sin-vm did not execute dummy program"
	exit 1
fi

build/sin-vm demo/test.sin
if [ "$?" = "1" ]; then
	echo "ERROR: sin-vm did not execute demo.sin"
	exit 1
fi

build/sin-asm demo/test.san
if [ "$?" = "1" ]; then
	echo "ERROR: sin-asm did not execute demo.san"
	exit 1
fi