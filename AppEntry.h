#ifndef APPENTRY_H
#define APPENTRY_H

#include <chrono>
#include <ctime>
#include <string>

/**
 * @class AppEntry
 * @brief Helper Class encapsulating what a AppEntry is. Has properties for the
 * id, title, startTime and endTime for when a Window was visited. Contains
 * various getters and setters for the mentioned properties.
 * @author Syed Ali
 */
class AppEntry {
public:
    // Use std::chrono::system_clock::time_point for time tracking
    using TimePoint = std::chrono::system_clock::time_point;

    // alternate ctor - defaults to an empty AppEntry.
    explicit AppEntry(std::string ti = "", TimePoint sT = std::chrono::system_clock::now(),
        TimePoint eT = std::chrono::system_clock::now(), long long i = 0);

    // defaulted copy ctor
    AppEntry(const AppEntry& copy) = default;

    // defaulted assignment op
    AppEntry& operator=(const AppEntry& rhs) = default;

    // variety of setters/getters
    void setID(long long i);
    [[nodiscard]] long long getID() const;

    void setTitle(const std::string& t);
    [[nodiscard]] std::string getTitle() const;

    void setStartTime(TimePoint sT);
    [[nodiscard]] TimePoint getStartTime() const;

    void setEndTime(TimePoint sT);
    [[nodiscard]] TimePoint getEndTime() const;

    // returns whether title is empty
    [[nodiscard]] bool isEmpty() const;

private:
    // id of AppEntry
    long long id;
    // title of AppEntry
    std::string title;
    // startTime of Window Visitation
    TimePoint startTime;
    // endTime of Window Visitation
    TimePoint endTime;
};

#endif // APPENTRY_H
