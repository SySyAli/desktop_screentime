#ifndef APPTRACKER_H
#define APPTRACKER_H

#include "DatabaseManager.h"

/**
 * @class AppTracker
 * @brief Main interface - starts the window tracking and logging process.
 * Only the Windows OS is supported.
 * @author Syed Ali
 */
class AppTracker {
public:
  // default ctor.
  AppTracker();

  // startTracking Method -  throws error if OS is not windows
  [[noreturn]] void startTracking();

  // return a vector of all the AppEntries from the AppUsage table
  std::vector<AppEntry> getAppEntries();

private:
  // DatabaseManager for the AppTracker
  DatabaseManager dbManager;
  // startTracking Method - make throws error if not windows
  [[noreturn]] void startTrackingWindows();
};

#endif // APPTRACKER_H
