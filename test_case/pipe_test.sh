#!/bin/bash



cd ..

./rshell.out

cat < new_file.txt | tr A-Z a-z | tee new_file2.txt | tr a-z A-Z > new_file.txt
