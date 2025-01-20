# Specify the minimum required version of CMake
cmake_minimum_required(VERSION 3.5)

# Define the project name as "task-soft-s"
project(task-soft-s)

# Set the required C++ standard
set(CMAKE_CXX_STANDARD 17)

# Find the OpenSSL library in the system
find_package(OpenSSL REQUIRED)

# Create an executable named "task-soft-s" and include HashManager.cpp
add_executable(task-soft-s main.cpp HashManager.cpp)

# Link the OpenSSL Crypto library to the "task-soft-s" executable
target_link_libraries(task-soft-s OpenSSL::Crypto)

# Set the installation prefix for the project
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)

# Installation of the executable
install(TARGETS task-soft-s DESTINATION bin)
