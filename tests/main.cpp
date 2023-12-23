/**
 * @file main.cpp
 * @brief Test driver.
 * @detailed The test driver. Through its associated tests, this driver aims to exercise all
 * of the functionality of the AppTracker, AppEntry, and DatabaseManager classes in a clear and
 * consistent way so that the class's interface and implementation can be easily inferred.
 * @author Syed Ali
 */

#include <gtest/gtest.h>

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}