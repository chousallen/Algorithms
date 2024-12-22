#!/bin/bash

# Create the outputs directory if it doesn't exist
mkdir -p ./outputs

# Loop through all input files
for input_file in ./inputs/*.in; do
    # Extract the base name of the input file (without directory and extension)
    base_name=$(basename "$input_file" .in)
    
    # Construct the output file name
    output_file="./outputs/${base_name}.out"
    
    # Run the command
    ./bin/cb "$input_file" "$output_file"
    ./checker/pa3_checker "$input_file" "$output_file"
done

# Run the judge command with seeds from 1126 to 1140
for seed in {60000..60010}; do
    ./judge -s "$seed"
done