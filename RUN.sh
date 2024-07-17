#!/bin/bash

if [ ! -d "build" ]; then
    echo "Build directory does not exist. Running ./BUILD.sh..."
    ./BUILD.sh
else
    if [ ! -d "build/bin" ]; then
        echo "Bin directory is missing. Please run ./BUILD.sh to create it."
        exit 1
    else
        if [ -f "build/bin/Compress-File" ]; then
            echo "Starting 'Compress-File'..."
            cd ./build/bin/
            ./Compress-File
        else
            echo "Executable 'Compress-File' is missing. Please run ./BUILD.sh to create it."
            exit 1
        fi
    fi
fi
