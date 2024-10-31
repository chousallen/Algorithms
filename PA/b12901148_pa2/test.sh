#!/bin/bash

# Build the project (assuming a Makefile is present)
make clean
make opt

# Test cases
#case=($(ls ./inputs | sed 's/\.in$//'))
case=(12 1000 10000 60000 100000)
len=${#case[@]}

# Execute the project (assuming the output binary is named 'project')
for ((i=0; i<$len; i++)); do
    echo "Running test case ${case[i]}"
    ./bin/mps ./inputs/${case[i]}.in ./outputs/${case[i]}.out
    #diff ./outputs/${case[i]}.out ./expected/${case[i]}.out
done