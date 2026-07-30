#include <utils.h>

#include <format>

namespace psu::utils
{

    auto voltageToFixedWidthString( volt a_voltage ) -> std::string
    {
        return std::format( "{:05.2f}", a_voltage );
    }

    auto currentToFixedWidthString( ampere a_current ) -> std::string
    {
        return std::format( "{:05.3f}", a_current );
    }

    void validateVoltageValue( volt a_voltage )
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

    void validateCurrentValue( ampere a_current )
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

    void milliSleep( unsigned int a_millisecondTime )
    {
#ifdef _WIN32
        Sleep( a_millisecondTime );
#else
        usleep( a_millisecondTime * 1000 );
#endif
    }

    void secondSleep( second a_secondTime )
    {
        milliSleep( static_cast< unsigned int >( a_secondTime * 1000 ) );
    }

} // namespace psu::utils
