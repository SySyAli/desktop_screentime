/**
 * @class DatabaseManagerTest
 * @brief Testing for the DatabaseManager Class.
 * @author Syed Ali
 */

#include "../DatabaseManager.h"
#include <gtest/gtest.h>

class DatabaseManagerTest : public ::testing::Test {
protected:
    DatabaseManager dbManager;

    void SetUp() override
    {
        dbManager.clearData();
    }
};

TEST_F(DatabaseManagerTest, CreateTable)
{
    // Test that the table is created successfully
    EXPECT_NO_THROW(DatabaseManager());
}

TEST_F(DatabaseManagerTest, InsertData)
{
    // Create a new AppEntry
    auto t_s = std::chrono::system_clock::now();
    AppEntry entry("Test App", t_s, t_s);

    // Test inserting data into the table
    EXPECT_NO_THROW(dbManager.insertData(entry));
    EXPECT_GT(entry.getID(), 0); // ID should be greater than 0 after insertion
}

TEST_F(DatabaseManagerTest, QueryData)
{
    // Insert a test entry
    auto t_s = std::chrono::system_clock::now();
    AppEntry entry("Test App", t_s, t_s);
    dbManager.insertData(entry);

    // Query data and check if the entry is present
    auto entries = dbManager.getAppEntries();
    ASSERT_EQ(entries.size(), 1);
    EXPECT_EQ(entries[0].getTitle(), "Test App");

    auto duration
        = std::chrono::duration_cast<std::chrono::seconds>(entries[0].getStartTime() - t_s);
    EXPECT_TRUE(abs(std::chrono::duration<double>(duration).count()) < 0.00001);

    duration = std::chrono::duration_cast<std::chrono::seconds>(entries[0].getEndTime() - t_s);
    EXPECT_TRUE(abs(std::chrono::duration<double>(duration).count()) < 0.00001);
}

TEST_F(DatabaseManagerTest, ClearData)
{
    // Insert a test entry
    auto t_s = std::chrono::system_clock::now();
    AppEntry entry("Test App", t_s, t_s);
    dbManager.insertData(entry);

    // Clear data and verify the table is empty
    dbManager.clearData();
    auto entries = dbManager.getAppEntries();
    EXPECT_TRUE(entries.empty());
}