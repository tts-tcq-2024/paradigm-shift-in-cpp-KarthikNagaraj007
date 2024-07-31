#include "Checker.h"
#include <gtest/gtest.h>

// Test the Battery::isWithinLimits method
TEST(BatteryTest, IsWithinLimits) {
    Battery battery;
    BatteryLimits limits{0, 45};
    
    EXPECT_TRUE(battery.isWithinLimits(25, limits, BatteryParameter::TEMPERATURE));
    EXPECT_FALSE(battery.isWithinLimits(-1, limits, BatteryParameter::TEMPERATURE));
    EXPECT_FALSE(battery.isWithinLimits(50, limits, BatteryParameter::TEMPERATURE));
}

// Test the Battery::isWithinWarningLimits method
TEST(BatteryTest, IsWithinWarningLimits) {
    Battery battery;
    BatteryWarningLimits warningLimits{20, 40};

    EXPECT_TRUE(battery.isWithinWarningLimits(30, warningLimits, BatteryParameter::TEMPERATURE));
    EXPECT_FALSE(battery.isWithinWarningLimits(15, warningLimits, BatteryParameter::TEMPERATURE));
    EXPECT_FALSE(battery.isWithinWarningLimits(45, warningLimits, BatteryParameter::TEMPERATURE));
}

// Test the Battery::batteryIsOk method
TEST(BatteryTest, BatteryIsOk) {
    Battery battery;

    EXPECT_TRUE(battery.batteryIsOk(25, 70, 0.7));
    EXPECT_FALSE(battery.batteryIsOk(50, 85, 0));
    EXPECT_FALSE(battery.batteryIsOk(-1, 70, 0.7));
    EXPECT_FALSE(battery.batteryIsOk(25, 19, 0.7));
    EXPECT_FALSE(battery.batteryIsOk(25, 70, 0.9));
}

// Test the Battery::checkParameter method
TEST(BatteryTest, CheckParameter) {
    Battery battery;
    BatteryLimits limits{0, 45};
    BatteryWarningLimits warningLimits{20, 40};

    EXPECT_TRUE(battery.checkParameter(30, limits, warningLimits, BatteryParameter::TEMPERATURE));
    EXPECT_FALSE(battery.checkParameter(50, limits, warningLimits, BatteryParameter::TEMPERATURE));
    EXPECT_FALSE(battery.checkParameter(10, limits, warningLimits, BatteryParameter::TEMPERATURE));
}

// Test the language setting and corresponding messages
TEST(BatteryTest, LanguageSetting) {
    Battery battery;

    // Check default language (English)
    EXPECT_EQ(battery.isWithinLimits(50, {0, 45}, BatteryParameter::TEMPERATURE), false);

    // Set to German and check messages
    battery.setLanguage("German");
    EXPECT_EQ(battery.isWithinLimits(50, {0, 45}, BatteryParameter::TEMPERATURE), false);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
