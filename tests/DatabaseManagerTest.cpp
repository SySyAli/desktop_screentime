/**
 * @file DatabaseManagerTest.cpp
 * @brief Testing for the DatabaseManager Class.
 * @author Syed Ali
 */


//#include "../DatabaseManager.h"
//#include <gtest/gtest.h>

//class DatabaseManagerTest : public ::testing::Test {
//protected:
//    DatabaseManager dbManager;
//
//    void SetUp() override {
//        dbManager.clearData();
//    }
//};
//
//TEST_F(DatabaseManagerTest, InsertDataInsertsCorrectly) {
//    AppEntry entry("Test Title", 123, 456);
//    dbManager.insertData(entry);
//
//    auto entries = dbManager.getAppEntries();
//    ASSERT_EQ(entries.size(), 1);
//    EXPECT_EQ(entries[0].getTitle(), "Test Title");
//}