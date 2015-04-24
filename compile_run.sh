#!/bin/sh

cd code ; make MAC=1 CC=gcc-4.9; cd ..; ./cvc.sh
