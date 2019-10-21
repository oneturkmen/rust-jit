cmake_minimum_required(VERSION 3.10)

# Project info
project(rust_jit
    LANGUAGES CXX
    VERSION 0.1)

# Set the minimum cpp version
set(CMAKE_CXX_STANDARD 11)

# For ctags; outputs compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

# Configure build output
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib") 
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

# the -I flag in gcc
include_directories(
    ${PROJECT_SOURCE_DIR}/cpp/include/
    ) 

set(APP_SOURCES cpp/src/main.cpp)
# set(LIB_SOURCES src/World.cpp)

# Creates ./build/bin/runner
add_executable(${PROJECT_NAME} ${APP_SOURCES})

# Link shared library
find_library(RUST_LIB rust_ffi rust/target/debug)
#set(RUST_LIB librust_ffi)
target_link_libraries(${PROJECT_NAME} ${RUST_LIB})


# Shared library
# TODO: not needed now
#set(LIBRARY_NAME World)
#add_library(${LIBRARY_NAME} SHARED ${LIB_SOURCES})
#target_link_libraries(${PROJECT_NAME} ${LIBRARY_NAME})


# ---------------------- OMR configuration ----------------------
# TODO
