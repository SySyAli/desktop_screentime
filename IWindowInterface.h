//
// Created by syeda on 12/25/2023.
// TODO COMMENTS

#ifndef WINDOWTRACKER_H
#define WINDOWTRACKER_H

#include "DatabaseManager.h"

// factory pattern
class IWindowInterface {
public:
    IWindowInterface();
    virtual ~IWindowInterface() = default;

    virtual void startTracking() = 0;

    // sets tracking boolean to false
    virtual void stopTracking();

    // return a vector of all the AppEntries from the AppUsage table
    virtual std::vector<AppEntry> getAppEntries();

    // clear the tracking entries
    virtual void clearTracking();

    // returns a reference dbManager
    virtual DatabaseManager& getDatabaseManager();

    // gets tracking boolean
    [[nodiscard]] virtual bool getTrackingBool() const;

protected:
    // DatabaseManager for the AppTracker
    DatabaseManager dbManager;
    // boolean for tracking
    bool tracking;
};

class WindowsTracker : public IWindowInterface {
public:
    void startTracking() override;
};

class LinuxTracker : public IWindowInterface {
public:
    void startTracking() override;
};

#endif // WINDOWTRACKER_H
