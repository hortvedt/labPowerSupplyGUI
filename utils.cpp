#include <utils.h>

#include <format>

namespace psu::utils
{

    auto voltageToFixedWidthString( double a_voltage ) -> std::string
    {
        return std::format( "{:05.2f}", a_voltage );
    }

    auto currentToFixedWidthString( double a_current ) -> std::string
    {
        return std::format( "{:05.3f}", a_current );
    }

    void validateVoltageValue( double a_voltage )
    {
        if ( a_voltage > 30 )
        {
            throw std::out_of_range( "Set voltage is larger than max ( 30V )." );
        }

        if ( a_voltage < 0 )
        {
            throw std::out_of_range( "Set voltage is negative." );
        }
    }

    void validateCurrentValue( double a_current )
    {
        if ( a_current > 5 )
        {
            throw std::out_of_range( "Set current is larger than max ( 5A )." );
        }

        if ( a_current < 0 )
        {
            throw std::out_of_range( "Set voltage is negative." );
        }
    }
} // namespace psu::utils
