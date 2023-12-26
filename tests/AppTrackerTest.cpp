/**
 * @class AppTrackerTest
 * @brief Testing for the AppTracker Class.
 * @author Syed Ali
 */

#include "../AppTracker.h"
#include "../AppEntry.h"
#include <gtest/gtest.h>
#include <vector>

class AppTrackerTest : public ::testing::Test {
protected:
    AppTracker tracker;

    void SetUp() override
    {
        // Clear the database before each test
        tracker.clearTracking();
    }
};

TEST_F(AppTrackerTest, ConstructorInitializesProperly)
{
    // Test that the AppTracker constructor initializes the tracking state
    // correctly
    EXPECT_NO_THROW(AppTracker());
}

TEST_F(AppTrackerTest, StopTrackingStopsTheLoop)
{
    tracker.stopTracking();
    EXPECT_FALSE(tracker.getTrackingBool());
}

TEST_F(AppTrackerTest, ClearTrackingClearsData)
{
    // Test that clearTracking clears the database
    AppEntry entry("Test App", std::chrono::system_clock::now(), std::chrono::system_clock::now());
    tracker.getDatabaseManager().insertData(entry);

    tracker.clearTracking();
    auto entries = tracker.getAppEntries();
    EXPECT_TRUE(entries.empty());
}

TEST_F(AppTrackerTest, GetAppEntriesReturnsEntries)
{
    // Insert a test entry
    auto t_s = std::chrono::system_clock::now();
    AppEntry entry("Test App", t_s, t_s);
    tracker.getDatabaseManager().insertData(entry);

    // Get entries and verify
    auto entries = tracker.getAppEntries();
    ASSERT_EQ(entries.size(), 1);
    EXPECT_EQ(entries[0].getTitle(), "Test App");

    auto duration
        = std::chrono::duration_cast<std::chrono::seconds>(entries[0].getStartTime() - t_s);
    EXPECT_TRUE(abs(std::chrono::duration<double>(duration).count()) < 0.00001);

    duration = std::chrono::duration_cast<std::chrono::seconds>(entries[0].getEndTime() - t_s);
    EXPECT_TRUE(abs(std::chrono::duration<double>(duration).count()) < 0.00001);
}
