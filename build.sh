#!/bin/bash

make clean
make
cp ./trash /usr/local/bin/
echo >> "alias rm='/usr/local/bin/trash -d'";
echo >> "alias rm -c='/usr/local/bin/trash -c'";
