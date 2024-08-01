#include "Checker.h"
#include <gtest/gtest.h>

TEST(BatteryParametersCheckTest, WarningStatusTest) {
    ParameterRange range = {0, 2.25, 42.75, 45};

    EXPECT_EQ(getWarningStatus(1.0f, range), WarningStatus::LOW_WARNING);
    EXPECT_EQ(getWarningStatus(30.0f, range), WarningStatus::NO_WARNING);
    EXPECT_EQ(getWarningStatus(46.0f, range), WarningStatus::HIGH_WARNING);
}

TEST(BatteryParametersCheckTest, BreachStatusTest) {
    ParameterRange range = {0, 2.25, 42.75, 45};

    EXPECT_EQ(getBreachStatus(1.0f, range), BreachStatus::LOW_BREACH);
    EXPECT_EQ(getBreachStatus(30.0f, range), BreachStatus::NO_BREACH);
    EXPECT_EQ(getBreachStatus(46.0f, range), BreachStatus::HIGH_BREACH);
}

TEST(BatteryParametersCheckTest, StatusMessageTranslationTest) {
    ParameterRange range = {0, 2.25, 42.75, 45};

    EXPECT_EQ(statusToMessageTranslation("Temperature", getBreachStatus(1.0f, range), getWarningStatus(1.0f, range)), "Temperature is below the safe range!");
    EXPECT_EQ(statusToMessageTranslation("Temperature", getBreachStatus(30.0f, range), getWarningStatus(30.0f, range)), "Temperature is normal.");
    EXPECT_EQ(statusToMessageTranslation("Temperature", getBreachStatus(46.0f, range), getWarningStatus(46.0f, range)), "Temperature is above the safe range!");
}

TEST(BatteryParametersCheckTest, CheckTemperatureTest) {
    BreachStatus breachStatus;
    WarningStatus warningStatus;

    EXPECT_TRUE(checkTemperature(25.0f, breachStatus, warningStatus));
    EXPECT_EQ(breachStatus, BreachStatus::NO_BREACH);
    EXPECT_EQ(warningStatus, WarningStatus::NO_WARNING);

    EXPECT_FALSE(checkTemperature(50.0f, breachStatus, warningStatus));
    EXPECT_EQ(breachStatus, BreachStatus::HIGH_BREACH);
    EXPECT_EQ(warningStatus, WarningStatus::NO_WARNING);

    EXPECT_FALSE(checkTemperature(-10.0f, breachStatus, warningStatus));
    EXPECT_EQ(breachStatus, BreachStatus::LOW_BREACH);
    EXPECT_EQ(warningStatus, WarningStatus::NO_WARNING);
}

TEST(BatteryParametersCheckTest, CheckSocTest) {
    BreachStatus breachStatus;
    WarningStatus warningStatus;

    EXPECT_TRUE(checkSoc(50.0f, breachStatus, warningStatus));
    EXPECT_EQ(breachStatus, BreachStatus::NO_BREACH);
    EXPECT_EQ(warningStatus, WarningStatus::NO_WARNING);

    EXPECT_FALSE(checkSoc(90.0f, breachStatus, warningStatus));
    EXPECT_EQ(breachStatus, BreachStatus::HIGH_BREACH);
    EXPECT_EQ(warningStatus, WarningStatus::NO_WARNING);

    EXPECT_FALSE(checkSoc(10.0f, breachStatus, warningStatus));
    EXPECT_EQ(breachStatus, BreachStatus::LOW_BREACH);
    EXPECT_EQ(warningStatus, WarningStatus::NO_WARNING);
}

TEST(BatteryParametersCheckTest, CheckChargeRateTest) {
    BreachStatus breachStatus;
    WarningStatus warningStatus;

    EXPECT_TRUE(checkChargeRate(0.4f, breachStatus, warningStatus));
    EXPECT_EQ(breachStatus, BreachStatus::NO_BREACH);
    EXPECT_EQ(warningStatus, WarningStatus::NO_WARNING);

    EXPECT_FALSE(checkChargeRate(0.9f, breachStatus, warningStatus));
    EXPECT_EQ(breachStatus, BreachStatus::HIGH_BREACH);
    EXPECT_EQ(warningStatus, WarningStatus::NO_WARNING);

    EXPECT_FALSE(checkChargeRate(-0.1f, breachStatus, warningStatus));
    EXPECT_EQ(breachStatus, BreachStatus::LOW_BREACH);
    EXPECT_EQ(warningStatus, WarningStatus::NO_WARNING);
}

TEST(BatteryParametersCheckTest, BatteryIsOkTest) {
    EXPECT_TRUE(batteryIsOk(25.0f, 50.0f, 0.4f));
    EXPECT_FALSE(batteryIsOk(50.0f, 50.0f, 0.4f));
    EXPECT_FALSE(batteryIsOk(25.0f, 90.0f, 0.4f));
    EXPECT_FALSE(batteryIsOk(25.0f, 50.0f, 0.9f));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
