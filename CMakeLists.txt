cmake_minimum_required(VERSION 3.10)
project(AcmeRobotics-PerceptionModule)

# Fetch GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.10.0
)
FetchContent_MakeAvailable(googletest)

set(CMAKE_CXX_STANDARD 14)

# Find OpenCV
find_package(OpenCV REQUIRED)

# Include directories
include_directories(${OpenCV_INCLUDE_DIRS})

# Add executable
add_executable(PerceptionModule src/main.cpp)

# Link libraries
target_link_libraries(PerceptionModule ${OpenCV_LIBS})

# Set compiler flags for coverage
if(WANT_COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
endif()

# Create test target (assuming tests are in a directory called tests)
add_executable(runTests tests/test_main.cpp)
target_link_libraries(runTests gtest gtest_main ${OpenCV_LIBS})

# Define a target for running tests and collecting coverage data
add_custom_target(test_coverage
    COMMAND ${CMAKE_CTEST_COMMAND} -C Debug --output-on-failure
    COMMAND lcov --directory ${CMAKE_BINARY_DIR} --capture --output-file coverage.info
    COMMAND lcov --remove coverage.info '/usr/*' --output-file coverage.info # filter out system libraries
    COMMAND lcov --list coverage.info # debug info
    DEPENDS runTests
)
