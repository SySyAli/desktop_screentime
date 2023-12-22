//
// Created by syeda on 12/21/2023.
//

#ifndef APPTRACKER_H
#define APPTRACKER_H

#include "DatabaseManager.h"

class AppTracker {
public:
  // ctor
  AppTracker();
  // startTracking Method - make throws error if not windows
  [[noreturn]] void startTracking();

  std::vector<AppEntry> getAppEntries();

private:
  DatabaseManager dbManager;
};

#endif // APPTRACKER_H
