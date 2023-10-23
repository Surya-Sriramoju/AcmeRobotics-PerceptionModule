# Include the tests directory
add_subdirectory(tests)

# Define a target for running tests and collecting coverage data
add_custom_target(test_coverage
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    COMMAND lcov --capture --directory . --output-file coverage.info
    COMMAND lcov --remove coverage.info '/usr/*' --output-file coverage.info # filter out system libraries
    COMMAND lcov --list coverage.info # debug info
    DEPENDS your_test_target
)