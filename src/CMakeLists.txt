cmake_minimum_required(VERSION 3.10)
project(librustjit VERSION 0.0.1 LANGUAGES CXX)

# Set the minimum cpp version
set(CMAKE_CXX_STANDARD 17)

# For ctags; outputs compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

# Configure build output
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

# Necessary source files
set(APP_SOURCES main.cpp ast_printer.cpp interpreter.cpp lexer.cpp parser.cpp environment.cpp)

# Creates ./build/bin/runner
add_executable(rustjit ${APP_SOURCES})
target_compile_options(rustjit PRIVATE -Wall)

# Include headers
target_include_directories(rustjit
    #PUBLIC 
    #    $<INSTALL_INTERFACE:include>    
    #    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link against statically compiled OMR library
find_library(OMR_LIB_DIRECTORY jitbuilder ${CMAKE_CURRENT_SOURCE_DIR}/libs)
target_link_libraries(rustjit PRIVATE ${OMR_LIB_DIRECTORY})
