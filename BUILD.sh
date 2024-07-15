#!/bin/bash

if ! [ -x "$(command -v make)" ]; then
  echo 'Error: make is not installed.' >&2
  exit 1
fi

if [ ! -f "Makefile" ]; then
    echo "Error: Makefile not found in the current directory."
    exit 1
fi

if [ -d "logs" ]; then
    echo "Logs directory found. Deleting it..."
    rm -rf logs
fi

mkdir logs

if [ -d "build" ]; then
    echo "Build directory found. Running make clean..."
    make clean
fi

echo "Starting project build..."
start_time=$(date +%s.%N)

{
    make
} | tee logs/build.log

if [ $? -eq 0 ]; then
    clear
    end_time=$(date +%s.%N)
    duration=$(echo "$end_time - $start_time" | bc)
    printf "Build completed successfully in %.2f seconds!\n" "$duration" | tee -a logs/build.log

    # Move logs to the build directory
    if [ ! -d "build/logs" ]; then
        mkdir build/logs
    fi
    mv logs/* build/logs/

    # Optionally remove the empty logs directory
    rmdir logs || true
else
    echo "Error during project build." | tee -a logs/build.log
    exit 1
fi