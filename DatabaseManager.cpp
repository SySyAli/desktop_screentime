/**
 * @file DatabaseManager.cpp
 * @brief Implementation of DatabaseManager.h
 * @author Syed Ali
 */

#include "DatabaseManager.h"
#include <algorithm>
#include <iostream>
#include <sqlite3.h>

DatabaseManager::DatabaseManager()
    : appEntries({})
{
    sqlite3* local_db;
    int rc = sqlite3_open("app_usage.db", &local_db);

    if (rc != SQLITE_OK) {
        throw std::runtime_error("Can't open database " + std::string(sqlite3_errmsg(local_db)));
    }
    db = local_db;

    createTable(db);
}

void DatabaseManager::insertData(AppEntry& appEntry)
{
    const char* insertSql = "INSERT INTO AppUsage (title, startTime, endTime) VALUES (?, ?, ?)";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, insertSql, -1, &stmt, nullptr);

    if (rc == SQLITE_OK) {
        sqlite3_bind_text(stmt, 1, appEntry.getTitle().c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_int64(stmt, 2, static_cast<long long>(appEntry.getStartTime()));
        sqlite3_bind_int64(stmt, 3, static_cast<long long>(appEntry.getEndTime()));

        rc = sqlite3_step(stmt);
        if (rc == SQLITE_DONE) {
            // Get the last inserted row ID
            long long insertedId = sqlite3_last_insert_rowid(db);
            appEntry.setID(insertedId);

            std::cout << "Inserted ID: " << insertedId << std::endl;
        } else {
            throw std::runtime_error("Insertion error: " + std::string(sqlite3_errmsg(db)));
        }

        sqlite3_finalize(stmt);
    } else {
        throw std::runtime_error("Preparation error: " + std::string(sqlite3_errmsg(db)));
    }
}

void DatabaseManager::queryData()
{
    auto currEntries = getAppEntries();
    std::for_each(appEntries.begin(), appEntries.end(), [](AppEntry& entry) {
        std::cout << "ID: " << entry.getID() << ", Title: " << entry.getTitle()
                  << ", Start Time: " << entry.getStartTime()
                  << ", End Time: " << entry.getEndTime() << std::endl;
    });
}

void DatabaseManager::clearData()
{
    const char* deleteSql = "DELETE FROM AppUsage";
    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, deleteSql, nullptr, nullptr, &errMsg);

    if (rc != SQLITE_OK) {
        std::string error = "SQL error: ";
        if (errMsg) {
            error += errMsg;
            sqlite3_free(errMsg);
        }
        throw std::runtime_error(error);
    }

    appEntries.clear();
}

std::vector<AppEntry> DatabaseManager::getAppEntries()
{
    std::vector<AppEntry> entries;
    const char* selectSql = "SELECT id, title, startTime, endTime FROM AppUsage";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, selectSql, -1, &stmt, nullptr);

    if (rc == SQLITE_OK) {
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            int id = sqlite3_column_int(stmt, 0);
            const char* title = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
            auto startTime = static_cast<std::time_t>(sqlite3_column_int64(stmt, 2));
            auto endTime = static_cast<std::time_t>(sqlite3_column_int64(stmt, 3));

            AppEntry entry;
            entry.setID(id);
            entry.setTitle(std::string(title));
            entry.setStartTime(startTime);
            entry.setEndTime(endTime);

            entries.push_back(entry);
        }
        sqlite3_finalize(stmt);
        appEntries = entries;
        return appEntries;
    } else {
        throw std::runtime_error("Query error: " + std::string(sqlite3_errmsg(db)));
    }
}

void DatabaseManager::createTable(sqlite3* dbToCreate)
{
    // elements of AppEntry
    const char* createTableSql = R"(
    CREATE TABLE IF NOT EXISTS AppUsage (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        title TEXT NOT NULL,
        startTime INTEGER,
        endTime INTEGER
    ))";

    char* errMsg;
    int rc = sqlite3_exec(dbToCreate, createTableSql, nullptr, nullptr, &errMsg);

    if (rc != SQLITE_OK) {
        sqlite3_free(errMsg);
        throw std::runtime_error("SQL error: " + std::string(errMsg));
    }
}
