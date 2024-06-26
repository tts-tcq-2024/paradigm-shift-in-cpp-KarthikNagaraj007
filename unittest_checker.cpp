#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <iostream>
using namespace std;
using ::testing::_;
using ::testing::Invoke;
using ::testing::Test;

// Mock class to replace outputMessage
class MockOutput {
public:
    MOCK_METHOD(void, outputMessage, (const std::string& message), ());
};

MockOutput* mockOutput;

// mock function
void outputMessage(const std::string& message) {
    mockOutput->outputMessage(message);
}

// Function definitions
bool isTemperatureOk(float temperature) {
    if (temperature < 0 || temperature > 45) {
        outputMessage("Temperature out of range!");
        return false;
    }
    return true;
}

bool isSocOk(float soc) {
    if (soc < 20 || soc > 80) {
        outputMessage("State of Charge out of range!");
        return false;
    }
    return true;
}

bool isChargeRateOk(float chargeRate) {
    if (chargeRate > 0.8) {
        outputMessage("Charge Rate out of range!");
        return false;
    }
    return true;
}

bool batteryIsOk(float temperature, float soc, float chargeRate) {
    return isTemperatureOk(temperature) && isSocOk(soc) && isChargeRateOk(chargeRate);
}

// Test fixture class
class BatteryTest : public Test {
protected:
    MockOutput mock;
    void SetUp() override {
        mockOutput = &mock;
    }
    void TearDown() override {
        mockOutput = nullptr;
    }
};

// Test cases
TEST_F(BatteryTest, TemperatureTest) {
    EXPECT_CALL(mock, outputMessage("Temperature out of range!")).Times(1);
    EXPECT_FALSE(isTemperatureOk(-1));
}

TEST_F(BatteryTest, SocTest) {
    EXPECT_CALL(mock, outputMessage("State of Charge out of range!")).Times(1);
    EXPECT_FALSE(isSocOk(19));
}

TEST_F(BatteryTest, ChargeRateTest) {
    EXPECT_CALL(mock, outputMessage("Charge Rate out of range!")).Times(1);
    EXPECT_FALSE(isChargeRateOk(0.9));
}

TEST_F(BatteryTest, BatteryIsOkTest) {
    EXPECT_CALL(mock, outputMessage(_)).Times(0);
    EXPECT_TRUE(batteryIsOk(25, 50, 0.5));

    EXPECT_CALL(mock, outputMessage("Temperature out of range!")).Times(1);
    EXPECT_FALSE(batteryIsOk(50, 50, 0.5));

    EXPECT_CALL(mock, outputMessage("State of Charge out of range!")).Times(1);
    EXPECT_FALSE(batteryIsOk(25, 85, 0.5));

    EXPECT_CALL(mock, outputMessage("Charge Rate out of range!")).Times(1);
    EXPECT_FALSE(batteryIsOk(25, 50, 0.9));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
