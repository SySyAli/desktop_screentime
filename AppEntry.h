#ifndef APPENTRY_H
#define APPENTRY_H

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
  // alternate ctor - defaults to an empty AppEntry.
  explicit AppEntry(std::string ti = "", std::time_t sT = 0, std::time_t eT = 0,
                    long long i = 0);

  // defaulted copy ctor
  AppEntry(const AppEntry &copy) = default;

  // defaulted assignment op
  AppEntry &operator=(const AppEntry &rhs) = default;

  // variety of setters/getters
  void setID(long long i);
  [[nodiscard]] long long getID() const;

  void setTitle(const std::string &t);
  [[nodiscard]] std::string getTitle() const;

  void setStartTime(std::time_t sT);
  [[nodiscard]] std::time_t getStartTime() const;

  void setEndTime(std::time_t sT);
  [[nodiscard]] std::time_t getEndTime() const;

  // returns whether title is empty
  bool isEmpty() const;

private:
  // id of AppEntry
  long long id;
  // title of AppEntry
  std::string title;
  // startTime of Window Visitation
  std::time_t startTime;
  // endTime of Window Visitation
  std::time_t endTime;
};

#endif // APPENTRY_H
