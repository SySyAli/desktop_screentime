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
    AppEntry entry("Test App", 100, 200);
    tracker.getDatabaseManager().insertData(entry);

    tracker.clearTracking();
    auto entries = tracker.getAppEntries();
    EXPECT_TRUE(entries.empty());
}

TEST_F(AppTrackerTest, GetAppEntriesReturnsEntries)
{
    // Insert a test entry
    AppEntry entry("Test App", 100, 200);
    tracker.getDatabaseManager().insertData(entry);

    // Get entries and verify
    auto entries = tracker.getAppEntries();
    ASSERT_EQ(entries.size(), 1);
    EXPECT_EQ(entries[0].getTitle(), "Test App");
    EXPECT_EQ(entries[0].getStartTime(), 100);
    EXPECT_EQ(entries[0].getEndTime(), 200);
}
