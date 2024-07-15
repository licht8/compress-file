#!/bin/bash

# Check if the build directory exists
if [ ! -d "build" ]; then
    echo "Build directory does not exist. Running ./BUILD.sh..."
    ./BUILD.sh
else
    # Check if the bin directory exists
    if [ ! -d "build/bin" ]; then
        echo "Bin directory is missing. Please run ./BUILD.sh to create it."
        exit 1
    else
        # Check if the executable file Compress_File exists
        if [ -f "build/bin/huffman" ]; then
            echo "Starting huffman..."
            cd ./build/bin/
            ./huffman
        else
            echo "Executable huffman is missing. Please run ./BUILD.sh to create it."
            exit 1
        fi
    fi
fi
