#!/bin/bash

make clean && make && sudo cp ./trash /usr/local/bin/
echo "alias rm='/usr/local/bin/trash -d'" >> ~/.bashrc
echo "alias rm -c='/usr/local/bin/trash -c'" >> ~/.bashrc
echo "alias rm -l='/usr/local/bin/trash'" >> ~/.bashrc
source ~/.bashrc
