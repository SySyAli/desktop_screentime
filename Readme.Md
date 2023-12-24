# Desktop Screentime Tracker

<p align='center'>
  <a target="_blank" href='https://en.cppreference.com/w/'><img src='https://img.shields.io/badge/C%2B%2B-blue?style=for-the-badge&logo=cplusplus&color=blue' alt="CPP Reference Page"> </a>
  <a target="_blank" href='https://github.com/SySyAli/desktop_screentime/blob/main/CMakeLists.txt'><img src='https://img.shields.io/badge/CMake-blue?style=for-the-badge&logo=cmake&color=%230096FF' alt="CMakeList.txt of desktop_screentime"></a>
  <a target="_blank" href='https://www.sqlite.org/index.html'><img src='https://img.shields.io/badge/SQLite-blue?style=for-the-badge&logo=sqlite&color=darkgreen' alt="SQLite"></a>
 <a target="_blank" href='https://google.github.io/googletest/'><img src="https://img.shields.io/badge/GTest-blue?style=for-the-badge&logo=google&labelColor=GTest&color=lightgray" alt="GTest Documentation Page"/></a>
  <a target="_blank" href='https://github.com/SySyAli/desktop_screentime/actions'><img src='https://img.shields.io/badge/Github%20Actions-blue?style=for-the-badge&logo=githubactions&logoColor=white&color=%231134A6' alt="GitHub Actions for desktop_screentime"></a>
</p>
Track and analyze your active window time with the Desktop Screentime Tracker, a C++ and 
SQLite-based application for efficient usage monitoring. As of 12/25/23, only Windows OS is 
supported. Expect more to come!

## Features

- Real-time tracking of active window titles.
- Time spent on each application is logged for later analysis.
- Ability to generate reports based on screentime data.
- Simple and intuitive user interface.
- Secure local data storage using SQLite.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

What you need to install the software:

- CMake (Version 3.26 or higher)
- A C++17 compatible compiler
- SQLite3

### Installing

A step by step series of examples that tell you how to get a development environment running:

Clone the repository:

```bash
git clone https://github.com/yourusername/desktop_screentime.git
```
Navigate to the project repository:
```bash
cd desktop_screentime
```
Build the project with CMake:
```bash
cmake -B build
cmake --build build
```
Run the application:
```bash
./build/desktop_screentime
```
## Running the Tests
How to run the automated tests for this system:
```bash
cd build
ctest
```
## Built With:
- C++ - Primary programming language.
- CMake - Build System
- SQLite - Data Storage.
- GoogleTest - Testing Framework.
- Windows API - Active Window Tracking.

## Example Code Usage

The following example initializes the tracking process in a separate thread and waits for user input to stop tracking. It demonstrates how to integrate the Desktop Screentime Tracker into your C++ application.

```cpp
#include "AppTracker.h"
#include <atomic>
#include <iostream>
#include <thread>

std::atomic<bool> trackingActive(true); // Global flag to control tracking
AppTracker appTracker;

void startTrackingWrapper()
{

    appTracker.startTracking(); // Pass the flag to the tracking function
}

int main()
{
    // Start tracking in a separate thread
    std::thread trackingThread(startTrackingWrapper);

    // Wait for user input
    std::cout << "Press Enter to stop tracking..." << std::endl;
    std::cin.get(); // Wait for Enter key

    // Stop tracking
    appTracker.stopTracking();

    // Join the thread
    if (trackingThread.joinable()) {
        trackingThread.join();
    }

    std::cout << "Tracking stopped." << std::endl;
    return 0;
}
```
See the tests directory for more examples of how to use the interface.

## Contributing

Contributions to this project are welcome. If you find any issues or have suggestions for improvements, please open an issue or submit a pull request.

## License

This project is licensed under the [MIT License](https://opensource.org/license/mit/). Feel free to use and modify the code as per the license terms.
