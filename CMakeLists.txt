cmake_minimum_required(VERSION 4.0)

project(VIVASVAN VERSION 1.0)

set(SOURCE_FILES 
    src/main.cpp 
    src/shell.cpp
    src/lexer.cpp
    # src/astprinter.cpp
    src/parser.cpp
    src/interpreter.cpp
    src/library.cpp
    src/implemented.cpp
)

add_executable(vivasvan ${SOURCE_FILES})

target_include_directories(vivasvan
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/include
)

target_compile_features(vivasvan PRIVATE cxx_std_17)