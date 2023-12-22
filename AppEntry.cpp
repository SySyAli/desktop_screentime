/**
 * @file AppEntry
 * @brief Implementation of AppEntry.h
 * @author Syed Ali
 */
#include "AppEntry.h"
#include <utility>

AppEntry::AppEntry(std::string ti, const std::time_t sT, const std::time_t eT,
                   const long long &i)
    : id(i), title(std::move(ti)), startTime(sT), endTime(eT) {}

void AppEntry::setID(const long long i) { id = i; }

long long AppEntry::getID() const { return id; }

void AppEntry::setTitle(const std::string &t) { title = t; }

std::string AppEntry::getTitle() const { return title; }

void AppEntry::setStartTime(std::time_t sT) { startTime = sT; }

std::time_t AppEntry::getStartTime() const { return startTime; }

void AppEntry::setEndTime(std::time_t eT) { endTime = eT; }

std::time_t AppEntry::getEndTime() const { return endTime; }

bool AppEntry::isEmpty() const { return title.empty(); }
