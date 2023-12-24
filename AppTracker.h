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

  // startTracking Method -  throws error if OS is not windows. controlled by
  // tracking boolean
  void startTracking();

  // sets tracking boolean to false
  void stopTracking();

  // return a vector of all the AppEntries from the AppUsage table
  std::vector<AppEntry> getAppEntries();

  // clear the tracking entries
  void clearTracking();

private:
  // DatabaseManager for the AppTracker
  DatabaseManager dbManager;
  // boolean for tracking
  bool tracking;
  // startTracking Method - make throws error if not windows
  void startTrackingWindows();
};

#endif // APPTRACKER_H
