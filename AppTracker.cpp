/**
 * @file AppTracker.cpp
 * @brief Implementation of AppTracker.h
 * @author Syed Ali
 */
#include "AppTracker.h"
#include "AppEntry.h"
#include <iostream>

#ifndef _WIN32
#include <windows.h>
#elif _WIN64
#include <windows.h>
#endif

AppTracker::AppTracker() : dbManager(DatabaseManager()), tracking(true) {}

void AppTracker::startTracking() {

#ifndef _WIN32
  startTrackingWindows();
#elif _WIN64
  startTrackingWindows();
#else
  throw std::runtime_error(
      "Operating Systems other than Windows have not been supported yet!");
#endif
}

void AppTracker::stopTracking() { tracking = false; }

std::vector<AppEntry> AppTracker::getAppEntries() {
  return dbManager.getAppEntries();
}

void AppTracker::clearTracking() {
    dbManager.clearData();
}

DatabaseManager &AppTracker::getDatabaseManager() {
    return dbManager;
}

bool AppTracker::getTrackingBool() const{
    return tracking;
}

void AppTracker::startTrackingWindows() {
  char windowTitle[256];
  AppEntry prevEntry;

  while (tracking) {
    HWND hwnd = GetForegroundWindow();
    GetWindowText(hwnd, windowTitle, sizeof(windowTitle));
    std::string title(windowTitle);
    time_t now = time(nullptr);
    // convert now to string form
    char dt[26];

    errno_t err = ctime_s(dt, sizeof(dt), &now);

    if (err) {
      throw std::runtime_error("Error converting time");
    }

    clock_t curTime = clock();

    if (!title.empty()) {
      // handle the first entry
      if (prevEntry.isEmpty()) {
        std::cout << "Starting time for " << title << " : " << dt;

        prevEntry.setTitle(title);
        prevEntry.setStartTime(clock());
      } else if (prevEntry.getTitle() != title) {
        prevEntry.setEndTime(curTime);
        std::cout << "Ending time for " << prevEntry.getTitle() << " : " << dt;
        std::cout << "Duration for " << prevEntry.getTitle() << " : "
                  << (prevEntry.getEndTime() - prevEntry.getStartTime()) /
                         (long long)CLOCKS_PER_SEC
                  << std::endl;

        // insert the appEntry
        dbManager.insertData(prevEntry);

        // figure out the time spent at the website
        std::cout << "Starting time for " << title << " : " << dt << std::endl;
        prevEntry.setTitle(title);
        prevEntry.setStartTime(curTime);
      }
    }
    Sleep(1000); // Check every second, check if this should be changed
  }
}



