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
    AppEntry() = delete;

    // alternate ctor
    AppEntry(std::string  ti, std::time_t sT, std::time_t eT, const long long& i = 0);

    // just default the assignment and cctor
    AppEntry(const AppEntry & copy) = default;

    AppEntry& operator=(const AppEntry & rhs) = default;

    // variety of setters/getters
    void setID(const long long i);
    long long getID() const;

    void setTitle(const std::string& t);
    [[nodiscard]] std::string getTitle() const;

    void setStartTime(std::time_t sT);
    [[nodiscard]] std::time_t getStartTime() const;

    void setEndTime(std::time_t sT);
    [[nodiscard]] std::time_t getEndTime() const;

private:
    long long id;
    std::string title;
    std::time_t startTime;
    std::time_t endTime;
};


#endif //APPENTRY_H
