cmake_minimum_required(VERSION 3.14)
project(AcmeRobotics-PerceptionModule)

# Define model directory
add_definitions(-DMODELS_DIR="${CMAKE_SOURCE_DIR}/models")

# Set default values for WANT_COVERAGE and CMAKE_BUILD_TYPE
set(WANT_COVERAGE ON CACHE BOOL "Enable coverage by default")
set(CMAKE_BUILD_TYPE Debug CACHE STRING "Set build type to Debug by default")

# Fetch GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

set(CMAKE_CXX_STANDARD 14)

# Find and Include Eigen
find_package(Eigen3 REQUIRED)
include_directories(${EIGEN3_INCLUDE_DIR})

# Find OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add libraries along with their header files
add_library(CameraLib lib/Camera.cpp include/Camera.h)
add_library(YOLOLib lib/YOLO.cpp include/YOLO.h)
add_library(OpenCVProcessorLib lib/OpenCVProcessor.cpp include/OpenCVProcessor.h)
add_library(WorldCoordLib lib/CoordToWorld.cpp include/CoordToWorld.h)

# Add executable
add_executable(PerceptionModule src/main.cpp)

# Link libraries
target_link_libraries(PerceptionModule CameraLib YOLOLib OpenCVProcessorLib WorldCoordLib ${OpenCV_LIBS})

# Specify include directories for each target
target_include_directories(CameraLib PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(YOLOLib PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(OpenCVProcessorLib PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(WorldCoordLib PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_include_directories(PerceptionModule PUBLIC ${CMAKE_SOURCE_DIR}/include)


#
# Doxygen Support check if Doxygen is installed
# ref: https://cmake.org/cmake/help/latest/module/FindDoxygen.html
#
find_package(Doxygen)
if ( DOXYGEN_FOUND )
  set( DOXYGEN_OUTPUT_DIRECTORY     ${PROJECT_SOURCE_DIR}/docs )
  set( DOXYGEN_COLLABORATION_GRAPH  YES )
  set( DOXYGEN_EXTRACT_ALL          YES )
  set( DOXYGEN_CLASS_DIAGRAMS       YES )
  set( DOXYGEN_HIDE_UNDOC_RELATIONS NO )
  set( DOXYGEN_HAVE_DOT             YES )
  set( DOXYGEN_CLASS_GRAPH          YES )
  set( DOXYGEN_CALL_GRAPH           YES )
  set( DOXYGEN_CALLER_GRAPH         YES )
  set( DOXYGEN_COLLABORATION_GRAPH  YES )
  set( DOXYGEN_BUILTIN_STL_SUPPORT  YES )
  set( DOXYGEN_EXTRACT_PRIVATE      YES )
  set( DOXYGEN_EXTRACT_PACKAGE      YES )
  set( DOXYGEN_EXTRACT_STATIC       YES )
  set( DOXYGEN_EXTRACT_LOCALMETHODS YES )
  set( DOXYGEN_UML_LOOK             YES )
  set( DOXYGEN_UML_LIMIT_NUM_FIELDS 50 )
  set( DOXYGEN_TEMPLATE_RELATIONS   YES )
  set( DOXYGEN_DOT_GRAPH_MAX_NODES  100 )
  set( DOXYGEN_MAX_DOT_GRAPH_DEPTH  0 )
  set( DOXYGEN_DOT_TRANSPARENT      YES )
else()
  message( FATAL_ERROR "Doxygen needs to be installed to generate the doxygen documentation" )
endif()

#
# Create the compilation database for clangd and move it out of the build dir.
#
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Enable compile_commands.json
execute_process(COMMAND cmake -E create_symlink
                "${PROJECT_BINARY_DIR}/compile_commands.json"
                "${PROJECT_SOURCE_DIR}/compile_commands.json")


# Set compiler flags for coverage
if(WANT_COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")
endif()

# Create test target (assuming tests are in a directory called tests)
add_executable(runTests tests/test_main.cpp)
target_link_libraries(runTests gtest gtest_main CameraLib YOLOLib OpenCVProcessorLib ${OpenCV_LIBS})

# Define a target for running tests and collecting coverage data
add_custom_target(test_coverage
    COMMAND ./runTests
    COMMAND lcov --directory ${CMAKE_BINARY_DIR} --base-directory ${CMAKE_SOURCE_DIR} --capture --output-file test_coverage.info  # Updated file name
    COMMAND lcov --remove test_coverage.info '/usr/*' --output-file test_coverage.info  # Updated file name
    COMMAND lcov --list test_coverage.info  # Updated file name
    DEPENDS runTests
)