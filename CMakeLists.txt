cmake_minimum_required(VERSION 3.10)

# Set the project name
project(RTproject)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${PROJECT_SOURCE_DIR}/include)

# Add the executable
add_executable(RTproject src/main.cpp)