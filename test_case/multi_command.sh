#!/bin/sh

./rshell.out 

echo this && mkdir newfiles && ls -a; rm newfiles || rmdir newfiles && echo newfiles was deleted!

echo this too || echo this other thing && ls -a; touch newfile.txt  && mv newfiles.txt "newfiles"
