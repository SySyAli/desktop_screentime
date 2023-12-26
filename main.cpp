#include "AppTracker.h"
#include <iostream>
#include <thread>

AppTracker appTracker;

void startTrackingWrapper()
{
    try {
        appTracker.startTracking();
    } catch (std::runtime_error& e) {
        throw std::runtime_error(e.what());
    }
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
    std::cout << appTracker << std::endl;
    appTracker.clearTracking();
    return 0;
}