cmake_minimum_required(VERSION 3.10)

# set the project name
project(messaging)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")
include_directories(include)

# add the executable
add_executable(messaging src/messaging.cpp)
target_link_libraries(messaging pthread rt)

