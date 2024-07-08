#ifndef CHECKER_HPP
#define CHECKER_HPP
// Function definitions
bool isTemperatureOk(float temperature) ;

bool isSocOk(float soc) ;

bool isChargeRateOk(float chargeRate) ;

bool batteryIsOk(float temperature, float soc, float chargeRate) ;

#endif
