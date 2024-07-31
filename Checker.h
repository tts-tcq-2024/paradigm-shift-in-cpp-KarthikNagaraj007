#ifndef CHECKER_H
#define CHECKER_H

#include <string>
#include <map>

// Enum to represent different battery parameters
enum class BatteryParameter {
    TEMPERATURE,
    SOC,
    CHARGE_RATE
};

// Struct to define the limits for battery parameters
struct BatteryLimits {
    float min;
    float max;
};

// Struct to define the warning limits for battery parameters
struct BatteryWarningLimits {
    float min;
    float max;
};

// Battery class to check and monitor battery parameters
class Battery {
public:
    // Constructor to initialize battery messages and default language
    Battery();

    // Method to check if a value is within defined limits
    bool isWithinLimits(float value, BatteryLimits limits, BatteryParameter parameter);

    // Method to print an error message for a specific parameter
    void printErrorMessage(BatteryParameter parameter);

    // Method to check if a value is within warning limits
    bool isWithinWarningLimits(float value, BatteryWarningLimits limits, BatteryParameter parameter);

    // Method to print a warning message for a specific parameter
    void printWarningMessage(BatteryParameter parameter);

    // Method to check if the battery parameters are within acceptable and warning limits
    bool batteryIsOk(float temperature, float soc, float chargeRate);

    // Method to check both limits and warning limits for a parameter
    bool checkParameter(float value, BatteryLimits limits, BatteryWarningLimits warningLimits, BatteryParameter parameter); 

    // Method to test the batteryIsOk method with various test cases
    void testBatteryIsOk();

    // Method to set the language for error and warning messages
    void setLanguage(const std::string& lang);

private:
    // Maps to store error and warning messages for parameters in different languages
    std::map<BatteryParameter, std::string> parameterErrorMessages;
    std::map<BatteryParameter, std::string> parameterWarningMessages;
    std::map<BatteryParameter, std::string> parameterErrorMessagesGerman;
    std::map<BatteryParameter, std::string> parameterWarningMessagesGerman;

    // Variable to store the current language for messages
    std::string language;
};

#endif // CHECKER_H
