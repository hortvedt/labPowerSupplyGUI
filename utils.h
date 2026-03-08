#pragma once

#include <string>

namespace psu::utils
{
auto voltageToFixedWidthString( double a_voltage ) -> std::string;
auto currentToFixedWidthString( double a_voltage ) -> std::string;

// TODO: add the csv stuff

} // namespace psu::utils
