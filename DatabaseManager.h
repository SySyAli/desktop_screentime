// TODO COMMENTS

#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include "AppEntry.h"
#include <sqlite3.h>
#include <string>

class DatabaseManager {
public:
  DatabaseManager();

  DatabaseManager(const DatabaseManager &copy) = default;

  DatabaseManager &operator=(const DatabaseManager &rhs) = default;

  void insertData(AppEntry &appEntry);

  void queryData();

private:
  sqlite3 *db;

  // create a table
  static void createTable(sqlite3 *dbToCreate);
};

#endif // DATABASEMANAGER_H
