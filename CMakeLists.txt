cmake_minimum_required(VERSION 3.10)

project(Data_Structure VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the source files
set(SOURCES
    "CPU\ Scheduler\ Simulator/CPUSchedulerSimulator.cpp"
    "Calculator\ Language/Calculator\ Language.cpp"
)

# Create the executable
add_executable(Data_Structure ${SOURCES})
