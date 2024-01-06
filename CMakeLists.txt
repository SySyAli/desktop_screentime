## Preamble ##
cmake_minimum_required(VERSION 3.26)
project(desktop_screentime)

## Projectwide setup ##
set(CMAKE_CXX_STANDARD 17)

# Set compiler flags
if(MSVC)
    # Using Microsoft Visual C++
    add_compile_options(/W4 /WX)
else()
    # Assuming GCC or Clang
    add_compile_options(-Wall -Wextra -pedantic -Werror)
endif()
# include sqlite3
find_package(SQLite3 REQUIRED)

# Include directories
include_directories(${SQLite3_INCLUDE_DIRS})

# Include X11 for Linux
if(UNIX AND NOT APPLE)
    find_package(X11 REQUIRED)
    if(X11_FOUND)
        include_directories(${X11_INCLUDE_DIR})
    endif()
endif()

# include testing
enable_testing()
# Bring in GoogleTest
include(FetchContent)
FetchContent_Declare(googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG f8d7d77c06936315286eb55f8de22cd23c188571  # release-1.14.0
)
FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()
include_directories(${googletest_SOURCE_DIR}/googletest/include)

# Main Executable
add_executable(desktop_screentime main.cpp
        AppTracker.cpp
        DatabaseManager.cpp
        AppEntry.cpp
        IWindowInterface.cpp
)

# Link SQLite3 to the executable
target_link_libraries(desktop_screentime PRIVATE ${SQLite3_LIBRARIES})


# Link pthread and X11 for Linux
if(UNIX AND NOT APPLE)
    if(X11_FOUND)
        target_link_libraries(desktop_screentime PRIVATE ${X11_LIBRARIES} pthread)
    else()
        target_link_libraries(desktop_screentime PRIVATE pthread)
    endif()
endif()

# Link Application Services for macOS
if(APPLE)
    target_link_libraries(desktop_screentime "-framework ApplicationServices")
endif()

# Testing Executable
# Define the source files and dependencies for the executable
set(SOURCE_FILES
        tests/main.cpp
        tests/AppEntryTest.cpp
        tests/AppTrackerTest.cpp
        tests/DatabaseManagerTest.cpp
        AppTracker.cpp
        DatabaseManager.cpp
        AppEntry.cpp
        IWindowInterface.cpp
)

# Make the project root directory the working directory when we run
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
add_executable(tests ${SOURCE_FILES})
target_link_libraries(tests gtest gtest_main ${SQLite3_LIBRARIES})
if(UNIX AND NOT APPLE)
    target_link_libraries(tests ${X11_LIBRARIES} pthread)
endif()
# Link Application Services for macOS
if(APPLE)
    target_link_libraries(tests "-framework ApplicationServices")
endif()

target_include_directories(tests PRIVATE ${SQLite3_INCLUDE_DIRS})