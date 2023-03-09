#!/bin/bash

make clean && make && sudo cp ./trash /usr/local/bin/
echo "alias rm='/usr/local/bin/trash'" >> ~/.bashrc
source ~/.bashrc
alias rm='/usr/local/bin/trash'
