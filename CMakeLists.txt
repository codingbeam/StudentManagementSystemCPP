
cmake_minimum_required(VERSION 3.20)

project(StudentManagementSystem
    VERSION 1.0
    LANGUAGES CXX
)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Create application executable
add_executable(StudentApp
    src/main.cpp
    src/StudentApplication.cpp
    src/Student.cpp
    src/StudentManager.cpp
)

# Include header files
target_include_directories(StudentApp PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Enable CTest
include(CTest)

# Download GoogleTest automatically when testing is enabled
if(BUILD_TESTING)

    include(FetchContent)

    FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )

    FetchContent_MakeAvailable(googletest)

    # Create test executable
    add_executable(StudentTests
        tests/test_student.cpp
        tests/StudentManagerTests.cpp
        tests/StudentApplicationTests.cpp
        src/Student.cpp
        src/StudentManager.cpp
        src/StudentApplication.cpp
    )

    # Include header files
    target_include_directories(StudentTests PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    )

    # Link GoogleTest
    target_link_libraries(StudentTests PRIVATE
        GTest::gtest_main
        GTest::gmock
    )

    # Discover GoogleTest test cases
    include(GoogleTest)
    gtest_discover_tests(StudentTests)

endif()
