#pragma once

#include <string>
#include <unitdefinitions.h>

namespace psu::utils
{
    auto voltageToFixedWidthString( volt a_voltage ) -> std::string;
    auto currentToFixedWidthString( ampere a_current ) -> std::string;

    void validateVoltageValue( volt a_voltage );
    void validateCurrentValue( ampere a_current );
    // TODO: add the csv stuff

} // namespace psu::utils
