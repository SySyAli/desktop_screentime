#ifndef APPTRACKER_H
#define APPTRACKER_H

#include "DatabaseManager.h"
#include "IWindowInterface.h"
#include <memory>

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

    // operator overload that prints results
    friend std::ostream& operator<<(std::ostream& os, AppTracker& a);

    // startTracking Method -  throws error if OS is not windows. controlled by
    // tracking boolean
    void startTracking();

    // sets tracking boolean to false
    void stopTracking();

    // return a vector of all the AppEntries from the AppUsage table
    std::vector<AppEntry> getAppEntries();

    // clear the tracking entries
    void clearTracking();

    // returns a reference dbManager
    DatabaseManager& getDatabaseManager();

    // gets tracking boolean
    [[nodiscard]] bool getTrackingBool() const;

private:
    std::unique_ptr<IWindowInterface> windowTracker;
};

#endif // APPTRACKER_H
