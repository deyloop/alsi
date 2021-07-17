cmake_minimum_required (VERSION 2.8.11)

project(ALSI)

include_directories(${PROJECT_SOURCE_DIR}/headers)

file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_executable(alsi ${SRC_FILES})
