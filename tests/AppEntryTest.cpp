/**
 * @file AppEntryTest
 * @brief Testing for the AppEntry Class.
 * @author Syed Ali
 */

#include "../AppEntry.h"
#include <gtest/gtest.h>

class AppEntryTest : public ::testing::Test {};

TEST_F(AppEntryTest, ConstructorInitializesProperties) {
    AppEntry entry = AppEntry("Test Title", 123, 456, 1);
    EXPECT_EQ(entry.getTitle(), "Test Title");
    EXPECT_EQ(entry.getStartTime(), 123);
    EXPECT_EQ(entry.getEndTime(), 456);
    EXPECT_EQ(entry.getID(), 1);
}

TEST_F(AppEntryTest, SettersAndGetters) {
    AppEntry entry;
    entry.setTitle("New Title");
    entry.setStartTime(100);
    entry.setEndTime(200);
    entry.setID(2);

    EXPECT_EQ(entry.getTitle(), "New Title");
    EXPECT_EQ(entry.getStartTime(), 100);
    EXPECT_EQ(entry.getEndTime(), 200);
    EXPECT_EQ(entry.getID(), 2);
}

TEST_F(AppEntryTest, IsEmptyReturnsCorrectValue) {
    AppEntry entry;
    entry.setTitle("");
    EXPECT_TRUE(entry.isEmpty());

    entry.setTitle("Non-empty");
    EXPECT_FALSE(entry.isEmpty());
}