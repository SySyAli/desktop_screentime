/**
 * @file AppTracker.cpp
 * @brief Implementation of AppTracker.h
 * @author Syed Ali
 */
#include "AppTracker.h"
#include "AppEntry.h"
#include <iostream>
#include <algorithm>

AppTracker::AppTracker()
{
#ifdef _WIN32
    windowTracker = std::make_unique<WindowsTracker>();
#elif __linux__
    windowTracker = std::make_unique<LinuxTracker>();
#else
    throw std::runtime_error("Unsupported OS");
#endif
}

std::ostream& operator<<(std::ostream& os, AppTracker& a)
{
    std::vector<AppEntry> appEntries = a.getAppEntries();

    std::for_each(appEntries.begin(), appEntries.end(), [&os](AppEntry& entry) {
        const std::time_t t_s = std::chrono::system_clock::to_time_t(entry.getStartTime());
        const std::time_t t_e = std::chrono::system_clock::to_time_t(entry.getEndTime());
        os << "ID: " << entry.getID() << ", Title: " << entry.getTitle()
           << ", Start Time: " << std::ctime(&t_s) << ", End Time: " << std::ctime(&t_e)
           << '\n';
    });
    return os;
}

void AppTracker::startTracking()
{
    windowTracker->startTracking();
}

void AppTracker::stopTracking()
{
    windowTracker->stopTracking();
}

std::vector<AppEntry> AppTracker::getAppEntries()
{
    return windowTracker->getAppEntries();
}

void AppTracker::clearTracking()
{
    windowTracker->clearTracking();
}

DatabaseManager& AppTracker::getDatabaseManager()
{
    return windowTracker->getDatabaseManager();
}

bool AppTracker::getTrackingBool() const
{
    return windowTracker->getTrackingBool();
}
