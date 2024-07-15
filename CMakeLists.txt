cmake_minimum_required(VERSION 3.10)

project(Compress-File)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

include_directories(${PROJECT_SOURCE_DIR})

set(HEADER_FILES
    include/huffman.h
)

set(SOURCE_FILES
    src/huffman.c
    src/main.c
)

add_executable(Compress-File ${SOURCE_FILES} ${HEADER_FILES})

# target_link_libraries(... ...)
