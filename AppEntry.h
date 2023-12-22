//
// Created by syeda on 12/21/2023.
//

#ifndef APPENTRY_H
#define APPENTRY_H

#include <ctime>
#include <string>

class AppEntry {
public:
  // default/alternate ctor
  explicit AppEntry(std::string ti = "", std::time_t sT = 0, std::time_t eT = 0,
                    const long long &i = 0);

  // just default the assignment and cctor
  AppEntry(const AppEntry &copy) = default;

  AppEntry &operator=(const AppEntry &rhs) = default;

  // variety of setters/getters
  void setID(const long long i);
  long long getID() const;

  void setTitle(const std::string &t);
  [[nodiscard]] std::string getTitle() const;

  void setStartTime(std::time_t sT);
  [[nodiscard]] std::time_t getStartTime() const;

  void setEndTime(std::time_t sT);
  [[nodiscard]] std::time_t getEndTime() const;

  // returns whether title is empty
  bool isEmpty() const;

private:
  long long id;
  std::string title;
  std::time_t startTime;
  std::time_t endTime;
};

#endif // APPENTRY_H
