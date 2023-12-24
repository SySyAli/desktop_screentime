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
    AppEntry entry("Test App", 100, 200);

    // Test inserting data into the table
    EXPECT_NO_THROW(dbManager.insertData(entry));
    EXPECT_GT(entry.getID(), 0); // ID should be greater than 0 after insertion
}

TEST_F(DatabaseManagerTest, QueryData)
{
    // Insert a test entry
    AppEntry entry("Test App", 100, 200);
    dbManager.insertData(entry);

    // Query data and check if the entry is present
    auto entries = dbManager.getAppEntries();
    ASSERT_EQ(entries.size(), 1);
    EXPECT_EQ(entries[0].getTitle(), "Test App");
    EXPECT_EQ(entries[0].getStartTime(), 100);
    EXPECT_EQ(entries[0].getEndTime(), 200);
}

TEST_F(DatabaseManagerTest, ClearData)
{
    // Insert a test entry
    AppEntry entry("Test App", 100, 200);
    dbManager.insertData(entry);

    // Clear data and verify the table is empty
    dbManager.clearData();
    auto entries = dbManager.getAppEntries();
    EXPECT_TRUE(entries.empty());
}