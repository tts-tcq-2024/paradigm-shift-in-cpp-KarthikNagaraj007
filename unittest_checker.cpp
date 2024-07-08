#include <gtest/gtest.h>
#include "Checker.h"

// Test cases for isTemperatureOk
TEST(TemperatureTest, WithinRange) {
    EXPECT_TRUE(isTemperatureOk(25));
    EXPECT_TRUE(isTemperatureOk(0));
    EXPECT_TRUE(isTemperatureOk(45));
}

TEST(TemperatureTest, OutOfRange) {
    EXPECT_FALSE(isTemperatureOk(-1));
    EXPECT_FALSE(isTemperatureOk(46));
}

// Test cases for isSocOk
TEST(SocTest, WithinRange) {
    EXPECT_TRUE(isSocOk(50));
    EXPECT_TRUE(isSocOk(20));
    EXPECT_TRUE(isSocOk(80));
}

TEST(SocTest, OutOfRange) {
    EXPECT_FALSE(isSocOk(19));
    EXPECT_FALSE(isSocOk(81));
}

// Test cases for isChargeRateOk
TEST(ChargeRateTest, WithinRange) {
    EXPECT_TRUE(isChargeRateOk(0.5));
    EXPECT_TRUE(isChargeRateOk(0.8));
}

TEST(ChargeRateTest, OutOfRange) {
    EXPECT_FALSE(isChargeRateOk(0.9));
}

// Test cases for batteryIsOk
TEST(BatteryTest, AllConditions) {
    EXPECT_TRUE(batteryIsOk(25, 70, 0.7));
    EXPECT_FALSE(batteryIsOk(-1, 50, 0.5));
    EXPECT_FALSE(batteryIsOk(46, 50, 0.5));
    EXPECT_FALSE(batteryIsOk(25, 19, 0.5));
    EXPECT_FALSE(batteryIsOk(25, 81, 0.5));
    EXPECT_FALSE(batteryIsOk(25, 50, 0.9));
    EXPECT_FALSE(batteryIsOk(-1, 81, 0.9));
    EXPECT_TRUE(batteryIsOk(0, 50, 0.5));
    EXPECT_TRUE(batteryIsOk(45, 50, 0.5));
    EXPECT_TRUE(batteryIsOk(25, 20, 0.5));
    EXPECT_TRUE(batteryIsOk(25, 80, 0.5));
    EXPECT_TRUE(batteryIsOk(25, 50, 0.8));
}
