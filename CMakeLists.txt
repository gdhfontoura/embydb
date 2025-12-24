cmake_minimum_required(VERSION 3.10)

project(EmbyDB)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(include)

add_executable(${PROJECT_NAME} 
    src/main.cpp
    src/disk/disk_manager.cpp
)

add_executable(disk_test
    test/disk/disk_manager_test.cpp
    src/disk/disk_manager.cpp
)

target_link_libraries(disk_test GTest::gtest_main)
