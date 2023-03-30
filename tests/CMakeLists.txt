enable_testing()

include(GoogleTest)
# Executable
add_executable (tests
    NamedPropertyTests.cpp)

gtest_discover_tests(tests)
target_link_libraries (tests gtest_main flexiobjects)