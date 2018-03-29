#!/bin/sh

./rshell.out

test -e src && echo this and the file before works!;

[ -f file.cpp ] || echo the previous file does not work!;

test -e src && echo this worked;

test -f exit.sh;

[ -e testfiles ]

abort