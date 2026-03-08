#pragma once

#include <string>

namespace psu::utils
{
auto voltageToFixedWidthString( double a_voltage ) -> std::string;
auto currentToFixedWidthString( double a_voltage ) -> std::string;

void validateVoltageValue( double a_voltage );
void validateCurrentValue( double a_current );
// TODO: add the csv stuff

} // namespace psu::utils
