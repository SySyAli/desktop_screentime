//
// Created by syeda on 12/21/2023.
//

#include "AppTracker.h"
#include "AppEntry.h"
#include <iostream>
#include <windows.h>

AppTracker::AppTracker() : dbManager(DatabaseManager()) {}

// TODO - add conditions for windows!!!!
[[noreturn]] void AppTracker::startTracking() {

  char windowTitle[256];
  AppEntry prevEntry;

  while (true) {
    HWND hwnd = GetForegroundWindow();
    GetWindowText(hwnd, windowTitle, sizeof(windowTitle));
    std::string title(windowTitle);
    time_t now = time(nullptr);
    // convert now to string form
    char *dt = ctime(&now);
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
    Sleep(1000); // Check every second
  }
}

std::vector<AppEntry> AppTracker::getAppEntries() {
  return dbManager.getAppEntries();
}
