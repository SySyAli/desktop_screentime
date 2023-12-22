// TODO COMMENTS

#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include "AppEntry.h"
#include <sqlite3.h>
#include <string>
#include <vector>

class DatabaseManager {
public:
  DatabaseManager();

  DatabaseManager(const DatabaseManager &copy) = default;

  DatabaseManager &operator=(const DatabaseManager &rhs) = default;

  void insertData(AppEntry &appEntry);

  void queryData();

  std::vector<AppEntry> getAppEntries();

private:
  sqlite3 *db;
  std::vector<AppEntry> appEntries;
  // create a table
  static void createTable(sqlite3 *dbToCreate);
};

#endif // DATABASEMANAGER_H
