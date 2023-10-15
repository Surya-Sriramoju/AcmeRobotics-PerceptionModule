cmake_minimum_required(VERSION 3.10)
project(AcmeRobotics-PerceptionModule)

set(CMAKE_CXX_STANDARD 14)

# Find OpenCV
find_package(OpenCV REQUIRED)

# Include directories
include_directories(${OpenCV_INCLUDE_DIRS})

# Add executable
add_executable(PerceptionModule src/main.cpp)

# Link libraries
target_link_libraries(PerceptionModule ${OpenCV_LIBS})
