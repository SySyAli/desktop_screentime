#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include "AppEntry.h"
#include <sqlite3.h>
#include <string>
#include <vector>

/**
 * @class DatabaseManager
 * @brief Helper class that handles SQLite Database Operations. Provides
 * Operations to create a table to store AppEntrys, insert AppEntrys, and get a
 * vector of all AppEntrys.
 * @author Syed Ali
 */
class DatabaseManager {
public:
  // default ctor, creates SQLite3 db and creates AppUsage table.
  DatabaseManager();

  DatabaseManager(const DatabaseManager &copy) = default;

  DatabaseManager &operator=(const DatabaseManager &rhs) = default;

  // inserts an AppEntry into the AppUsage Table
  void insertData(AppEntry &appEntry);

  // prints out the contents of AppEntry
  void queryData();

  void clearData();

  // returns a vector of all AppEntries in the AppUsage Table
  std::vector<AppEntry> getAppEntries();

private:
  // SQLite db that holds the AppUsage Table
  sqlite3 *db;
  // Vector that holds all the AppEntries.
  std::vector<AppEntry> appEntries;
  // function that creates the AppUsage Table
  static void createTable(sqlite3 *dbToCreate);
};

#endif // DATABASEMANAGER_H
