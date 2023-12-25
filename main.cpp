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
    appTracker.clearTracking();
    return 0;
}