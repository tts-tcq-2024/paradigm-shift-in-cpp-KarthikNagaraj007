#include <assert.h>
#include <iostream>
using namespace std;

void outputMessage(const std::string& message) {
    cout << message << "\n";
}

bool isTemperatureOk(float temperature) {
  if(temperature < 0 || temperature > 45) {
    outputMessage("Temperature out of range!");
    return false;
  }
  return true;
}

bool isSocOk(float soc) {
  if(soc < 20 || soc > 80) {
    outputMessage("State of Charge out of range!");
    return false;
  }
  return true;
}

bool isChargeRateOk(float chargeRate) {
  if(chargeRate > 0.8) {
    outputMessage("Charge Rate out of range!");
    return false;
  }
  return true;
}

bool batteryIsOk(float temperature, float soc, float chargeRate) {
  return isTemperatureOk(temperature) && isSocOk(soc) && isChargeRateOk(chargeRate);
}
