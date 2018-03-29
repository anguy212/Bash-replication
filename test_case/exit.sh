#!/bin/sh

./rshell.out << EOF

echo this && mkdir newfiles && ls -a; rm newfiles || rmdir newfiles && echo newfiles was deleted!;

abort

EOF
