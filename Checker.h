#ifndef CHECKER_H
#define CHECKER_H

#include <string>
#include <map>

// Enum to define different battery parameters
enum class BatteryParameter {
    TEMPERATURE,
    SOC,
    CHARGE_RATE
};

// Struct to define the limits of battery parameters
struct BatteryLimits {
    float min;
    float max;
};

// Struct to define the warning limits of battery parameters
struct BatteryWarningLimits {
    float min;
    float max;
};

class Battery {
public:
    // Constructor
    Battery();
    
    // Method to check if a value is within defined limits for a parameter
    bool isWithinLimits(float value, BatteryLimits limits, BatteryParameter parameter);

    // Method to print an error message for a parameter
    void printErrorMessage(BatteryParameter parameter);

    // Method to check if a value is within defined warning limits for a parameter
    bool isWithinWarningLimits(float value, BatteryWarningLimits limits, BatteryParameter parameter);

    // Method to print a warning message for a parameter
    void printWarningMessage(BatteryParameter parameter);

    // Method to check if the battery parameters are within acceptable limits
    bool batteryIsOk(float temperature, float soc, float chargeRate);

    // Method to check both limits and warning limits for a parameter
    bool checkParameter(float value, BatteryLimits limits, BatteryWarningLimits warningLimits, BatteryParameter parameter);

    // Method to test the batteryIsOk function
    void testBatteryIsOk();
    
    // Method to set the language for messages
    void setLanguage(const std::string& lang);

private:
    // Maps to hold error and warning messages in different languages
    std::map<BatteryParameter, std::string> parameterErrorMessages;
    std::map<BatteryParameter, std::string> parameterWarningMessages;
    std::map<BatteryParameter, std::string> parameterErrorMessagesGerman;
    std::map<BatteryParameter, std::string> parameterWarningMessagesGerman;

    // Variable to hold the current language
    std::string language;

    // Default error and warning messages in English
    const std::map<BatteryParameter, std::string> defaultErrorMessages = {
        {BatteryParameter::TEMPERATURE, "Temperature out of range!"},
        {BatteryParameter::SOC, "State of Charge out of range!"},
        {BatteryParameter::CHARGE_RATE, "Charge Rate out of range!"}
    };

    const std::map<BatteryParameter, std::string> defaultWarningMessages = {
        {BatteryParameter::TEMPERATURE, "Warning: Temperature approaching limit!"},
        {BatteryParameter::SOC, "Warning: State of Charge approaching limit!"},
        {BatteryParameter::CHARGE_RATE, "Warning: Charge Rate approaching limit!"}
    };

    // Default error and warning messages in German
    const std::map<BatteryParameter, std::string> defaultErrorMessagesGerman = {
        {BatteryParameter::TEMPERATURE, "Temperatur außerhalb des Bereichs!"},
        {BatteryParameter::SOC, "Ladezustand außerhalb des Bereichs!"},
        {BatteryParameter::CHARGE_RATE, "Ladegeschwindigkeit außerhalb des Bereichs!"}
    };

    const std::map<BatteryParameter, std::string> defaultWarningMessagesGerman = {
        {BatteryParameter::TEMPERATURE, "Warnung: Temperatur nähert sich dem Limit!"},
        {BatteryParameter
