//
// Created by syeda on 12/21/2023.
//

#ifndef DESKTOP_SCREENTIME_APPENTRY_H
#define DESKTOP_SCREENTIME_APPENTRY_H

#include <string>
#include <ctime>

class AppEntry {
public:
    // default ctor
    AppEntry();
    // alternate ctor
    // just default the assignment and cctor
    // maybe even move ctor and assignment op

    // variety of setters/getters

private:
    int id;
    std::string title;
    std::time_t startTime;
    std::time_t endTime;
};


#endif //DESKTOP_SCREENTIME_APPENTRY_H
