cmake_minimum_required(VERSION 3.10)

# Set the minimum cpp version
set(CMAKE_CXX_STANDARD 17)

# For ctags; outputs compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

# Configure build output
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib") 
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")


set(APP_SOURCES main.cpp ast_printer.cpp interpreter.cpp lexer.cpp parser.cpp environment.cpp)

# Creates ./build/bin/runner
add_executable(lexer ${APP_SOURCES})

#target_include_directories(lexer PRIVATE ${PROJECT_SOURCE_DIR}/lexer)
