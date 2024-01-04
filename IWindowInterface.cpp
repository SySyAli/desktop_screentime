/**
 * @file IWindowInterface.cpp
 * @brief Implementation of IWindowInterface.h
 * @author Syed Ali
 */

#include "IWindowInterface.h"
#include <chrono>
#include <iostream>
#include <stdexcept>
#include <thread>
#ifdef _WIN32
#include <windows.h>
#elif __linux__
#include <X11/Xatom.h>
#include <X11/Xlib.h>
#endif

IWindowInterface::IWindowInterface()
    : dbManager(DatabaseManager())
    , tracking(true)
{
}

void IWindowInterface::stopTracking()
{
    tracking = false;
}

std::vector<AppEntry> IWindowInterface::getAppEntries()
{
    return dbManager.getAppEntries();
}

void IWindowInterface::clearTracking()
{
    dbManager.clearData();
}

DatabaseManager& IWindowInterface::getDatabaseManager()
{
    return dbManager;
}

bool IWindowInterface::getTrackingBool() const
{
    return tracking;
}

#ifdef _WIN32
void WindowsTracker::startTracking()
{
    char windowTitle[256];
    AppEntry prevEntry;

    while (tracking) {
        HWND hwnd = GetForegroundWindow();
        GetWindowText(hwnd, windowTitle, sizeof(windowTitle));
        std::string title(windowTitle);

        char dt[26];
        auto curTime = std::chrono::system_clock::now();
        const std::time_t t_c = std::chrono::system_clock::to_time_t(curTime);

        // For Windows - ctime_s
        int err = ctime_s(dt, sizeof(dt), &t_c);
        if (err) {
            throw std::runtime_error("Error converting time");
        }

        if (!title.empty()) {
            // handle the first entry
            if (prevEntry.isEmpty()) {
                std::cout << "Starting time for " << title << " : " << dt;

                prevEntry.setTitle(title);
                prevEntry.setStartTime(curTime);
            } else if (prevEntry.getTitle() != title) {
                prevEntry.setEndTime(curTime);
                // Calculate the duration in seconds
                auto duration = std::chrono::duration_cast<std::chrono::seconds>(
                    prevEntry.getEndTime() - prevEntry.getStartTime());

                std::cout << "Ending time for " << prevEntry.getTitle() << " : " << dt;
                std::cout << "Duration for " << prevEntry.getTitle() << " : " << duration.count()
                          << " seconds" << std::endl;

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
#endif

#if __linux__
std::string getTrackingScreenLinux(Display* display)
{
    Window window;
    char* title = nullptr;
    int revert_to_return;
    int status = XGetInputFocus(display, &window, &revert_to_return);

    if (status == Success && window != None) {
        XFetchName(display, window, &title);
    }

    std::string windowTitle(title ? title : "");
    XFree(title);
    return windowTitle;
}

void LinuxTracker::startTracking()
{
    AppEntry prevEntry;
    Display* display = XOpenDisplay(nullptr);
    if (!display) {
        throw std::runtime_error("Cannot open display");
    }

    while (tracking) {
        std::string title = getTrackingScreenLinux(display);
        char dt[26];
        auto curTime = std::chrono::system_clock::now();
        const std::time_t t_c = std::chrono::system_clock::to_time_t(curTime);

        // unix based systems - ctime_r
        char* res_s = ctime_r(&t_c, dt);
        if (!res_s) {
            throw std::runtime_error("Error converting time");
        }
        if (!title.empty()) {
            // handle the first entry
            if (prevEntry.isEmpty()) {
                std::cout << "Starting time for " << title << " : " << dt;
                prevEntry.setTitle(title);
                prevEntry.setStartTime(curTime);
            } else if (prevEntry.getTitle() != title) {
                prevEntry.setEndTime(curTime);
                // Calculate the duration in seconds
                auto duration = std::chrono::duration_cast<std::chrono::seconds>(
                    prevEntry.getEndTime() - prevEntry.getStartTime());

                std::cout << "Ending time for " << prevEntry.getTitle() << " : " << dt;
                std::cout << "Duration for " << prevEntry.getTitle() << " : " << duration.count()
                          << " seconds" << std::endl;

                // insert the appEntry
                dbManager.insertData(prevEntry);

                // figure out the time spent at the website
                std::cout << "Starting time for " << title << " : " << dt << std::endl;
                prevEntry.setTitle(title);
                prevEntry.setStartTime(curTime);
            }
        }

        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    XCloseDisplay(display);
}
#endif

// TODO
void MacOSTracker::startTracking() {
    throw std::runtime_error("MacOS has not been implemented yet!");
}