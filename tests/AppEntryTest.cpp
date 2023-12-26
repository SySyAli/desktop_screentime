/**
 * @file AppEntryTest
 * @brief Testing for the AppEntry Class.
 * @author Syed Ali
 */

#include "../AppEntry.h"
#include <gtest/gtest.h>

class AppEntryTest : public ::testing::Test { };

TEST_F(AppEntryTest, ConstructorInitializesProperties)
{
    auto t_s = std::chrono::system_clock::now();
    AppEntry entry("Test Title", t_s, t_s, 1);
    EXPECT_EQ(entry.getTitle(), "Test Title");
    EXPECT_EQ(entry.getID(), 1);

    auto duration = std::chrono::duration_cast<std::chrono::seconds>(entry.getStartTime() - t_s);
    EXPECT_TRUE(abs(std::chrono::duration<double>(duration).count()) < 0.00001);

    duration = std::chrono::duration_cast<std::chrono::seconds>(entry.getEndTime() - t_s);
    EXPECT_TRUE(abs(std::chrono::duration<double>(duration).count()) < 0.00001);
}

TEST_F(AppEntryTest, SettersAndGetters)
{
    auto t_s = std::chrono::system_clock::now();
    AppEntry entry;
    entry.setTitle("New Title");
    entry.setStartTime(t_s);
    entry.setEndTime(t_s);
    entry.setID(2);

    EXPECT_EQ(entry.getTitle(), "New Title");
    EXPECT_EQ(entry.getStartTime(), t_s);
    EXPECT_EQ(entry.getEndTime(), t_s);
    EXPECT_EQ(entry.getID(), 2);
}

TEST_F(AppEntryTest, IsEmptyReturnsCorrectValue)
{
    AppEntry entry;
    entry.setTitle("");
    EXPECT_TRUE(entry.isEmpty());

    entry.setTitle("Non-empty");
    EXPECT_FALSE(entry.isEmpty());
}