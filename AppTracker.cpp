/**
 * @file AppTracker.cpp
 * @brief Implementation of AppTracker.h
 * @author Syed Ali
 */
#include "AppTracker.h"
#include "AppEntry.h"
#include <algorithm>
#include <iostream>

AppTracker::AppTracker()
{
#ifdef _WIN32
    windowTracker = std::make_unique<WindowsTracker>();
#elif __linux__
    windowTracker = std::make_unique<LinuxTracker>();
#elif __APPLE__
    windowTracker = std::make_unique<MacOSTracker>();
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
        char dt_s[26];
        char dt_e[26];

// For Windows, use ctime_s
#ifdef _WIN32
        int err_s = ctime_s(dt_s, sizeof(dt_s), &t_s);
        int err_e = ctime_s(dt_e, sizeof(dt_e), &t_e);
        if (err_s || err_e) {
            throw std::runtime_error("Error converting time");
        }
// For Unix systems (Linux, macOS), use ctime_r
#else
            char* res_s = ctime_r(&t_s, dt_s);
            char* res_e = ctime_r(&t_e, dt_e);
            if (!res_s || !res_e) {
                throw std::runtime_error("Error converting time");
            }
#endif

        os << "ID: " << entry.getID() << ", Title: " << entry.getTitle() << ", Start Time: " << dt_s
           << ", End Time: " << dt_e << '\n';
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
