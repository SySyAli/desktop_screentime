## Preamble ##
cmake_minimum_required(VERSION 3.26)
project(desktop_screentime)

## Projectwide setup ##
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wextra -pedantic -pedantic-errors -g")

# include sqlite3
find_package(SQLite3 REQUIRED)

add_executable(desktop_screentime main.cpp
        AppTracker.cpp
        DatabaseManager.cpp
        AppEntry.cpp)

## Link SQLite3 to the executable ##
target_link_libraries(desktop_screentime PRIVATE ${SQLite3_LIBRARIES})
target_include_directories(desktop_screentime PRIVATE ${SQLite3_INCLUDE_DIRS})

