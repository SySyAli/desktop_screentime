// TODO COMMENTS
#include "DatabaseManager.h"
#include <iostream>
#include <sqlite3.h>

DatabaseManager::DatabaseManager() {
  sqlite3 *local_db;
  int rc = sqlite3_open("app_usage.db", &local_db);

  if (rc != SQLITE_OK) {
    std::cerr << "Can't open database: " << sqlite3_errmsg(local_db)
              << std::endl;
  }
  db = local_db;

  createTable(db);
}

void DatabaseManager::insertData(AppEntry &appEntry) {
  const char *insertSql =
      "INSERT INTO AppUsage (title, startTime, endTime) VALUES (?, ?, ?)";
  sqlite3_stmt *stmt;
  int rc = sqlite3_prepare_v2(db, insertSql, -1, &stmt, NULL);

  if (rc == SQLITE_OK) {
    sqlite3_bind_text(stmt, 1, appEntry.getTitle().c_str(), -1,
                      SQLITE_TRANSIENT);
    sqlite3_bind_int64(stmt, 2,
                       static_cast<long long>(appEntry.getStartTime()));
    sqlite3_bind_int64(stmt, 3, static_cast<long long>(appEntry.getEndTime()));

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_DONE) {
      // Get the last inserted row ID
      long long insertedId = sqlite3_last_insert_rowid(db);
      appEntry.setID(insertedId);

      std::cout << "Inserted ID: " << insertedId << std::endl;
    } else {
      std::cerr << "Insertion error: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
  } else {
    std::cerr << "Preparation error: " << sqlite3_errmsg(db) << std::endl;
  }
}

void DatabaseManager::queryData() {
  const char *selectSql = "SELECT * FROM AppUsage";
  sqlite3_stmt *stmt;
  int rc = sqlite3_prepare_v2(db, selectSql, -1, &stmt, NULL);

  if (rc == SQLITE_OK) {
    while (sqlite3_step(stmt) == SQLITE_ROW) {
      int id = sqlite3_column_int(stmt, 0);
      const unsigned char *title = sqlite3_column_text(stmt, 1);
      auto startTime = static_cast<std::time_t>(sqlite3_column_int64(stmt, 2));
      auto endTime = static_cast<std::time_t>(sqlite3_column_int64(stmt, 3));

      std::cout << "ID: " << id << ", Title: " << title
                << ", Start Time: " << startTime << ", End Time: " << endTime
                << std::endl;
    }
    sqlite3_finalize(stmt);
  } else {
    std::cerr << "Query error: " << sqlite3_errmsg(db) << std::endl;
  }
}

void DatabaseManager::createTable(sqlite3 *dbToCreate) {
  // elements of AppEntry
  const char *createTableSql = R"(
    CREATE TABLE IF NOT EXISTS AppUsage (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        title TEXT NOT NULL,
        startTime INTEGER,
        endTime INTEGER
    ))";

  char *errMsg;
  int rc = sqlite3_exec(dbToCreate, createTableSql, 0, 0, &errMsg);

  if (rc != SQLITE_OK) {
    std::cerr << "SQL error: " << errMsg << std::endl;
    sqlite3_free(errMsg);
  }
}
