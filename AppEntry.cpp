/**
 * @file AppEntry
 * @brief Implementation of AppEntry.h
 * @author Syed Ali
 */
#include "AppEntry.h"
#include <utility>

AppEntry::AppEntry(std::string ti, const TimePoint sT, const TimePoint eT, const long long i)
    : id(i)
    , title(std::move(ti))
    , startTime(sT)
    , endTime(eT)
{
}

void AppEntry::setID(const long long i)
{
    id = i;
}

long long AppEntry::getID() const
{
    return id;
}

void AppEntry::setTitle(const std::string& t)
{
    title = t;
}

std::string AppEntry::getTitle() const
{
    return title;
}

void AppEntry::setStartTime(AppEntry::TimePoint sT)
{
    startTime = sT;
}

AppEntry::TimePoint AppEntry::getStartTime() const
{
    return startTime;
}

void AppEntry::setEndTime(AppEntry::TimePoint eT)
{
    endTime = eT;
}

AppEntry::TimePoint AppEntry::getEndTime() const
{
    return endTime;
}

bool AppEntry::isEmpty() const
{
    return title.empty();
}
