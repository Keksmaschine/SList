# Define project name
project(SLIST)
 
# States that CMake required version must be greater than 2.8
cmake_minimum_required(VERSION 2.8)

# Set runtime output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})



# Detect compiler
if(CMAKE_COMPILER_IS_GNUCXX)

# Set compiler flags for g++
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -lpthread")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

elseif(MSVC)

# Set compiler flags for Microsoft Visual Studio
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MDd")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MD")

endif()



# Add directories
add_subdirectory(src)
add_subdirectory(test)
