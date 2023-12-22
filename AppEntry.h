//
// Created by syeda on 12/21/2023.
//

#ifndef APPENTRY_H
#define APPENTRY_H

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

    // get id
    // get title
    // get startTime
    // get endTime

private:
    int id;
    std::string title;
    std::time_t startTime;
    std::time_t endTime;
};


#endif //DESKTOP_SCREENTIME_APPENTRY_H
