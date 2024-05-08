cmake_minimum_required(VERSION 3.13)  # Make sure this is 3.13 or later
project(gmod-module-base LANGUAGES CXX)

# Set policy CMP0079 to NEW
cmake_policy(SET CMP0079 NEW)

set(CMAKE_CONFIGURATION_TYPES Release Debug)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/release)
set(CMAKE_RUNTIME_LIBRARY_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/bin/debug)
set(CMAKE_RUNTIME_LIBRARY_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/bin/release)

# Set the paths to the Python libraries and headers
set(PYTHON_LIBRARIES "${CMAKE_SOURCE_DIR}/python/libs/python311.lib")
set(PYTHON_INCLUDE_DIRS "${CMAKE_SOURCE_DIR}/include")

# Include the Python headers
include_directories(${PYTHON_INCLUDE_DIRS})

add_subdirectory(include)
add_subdirectory(examples/queue)
add_subdirectory(examples/MetaTable)

set_gmod_suffix_prefix(queue)
