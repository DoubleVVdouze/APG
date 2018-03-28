cmake_minimum_required(VERSION 3.9)
project(ProjetAPG)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

include_directories(Include)

file(GLOB SOURCE_FILES Source/*.cpp)
file(GLOB INCLUDE_FILES Include/*.hpp)

add_executable(ProjetAPG main.cpp ${SOURCE_FILES} ${INCLUDE_FILES})