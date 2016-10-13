project( ThoughtWorksHomework2016 )
cmake_minimum_required( VERSION 2.8.3 )

include_directories( ${CMAKE_SOURCE_DIR} )
include_directories( ${CMAKE_SOURCE_DIR}/src )
include_directories( ${CMAKE_BINARY_DIR} )
configure_file(
    "${PROJECT_SOURCE_DIR}/Configs.h.in"
    "${PROJECT_BINARY_DIR}/Configs.h" )

add_executable( demo            src/demo.cpp )
add_executable( stdin2stdout    src/stdin2stdout.cpp )
add_executable( test1           tests/test1.cpp )
add_executable( test2           tests/test2.cpp )
