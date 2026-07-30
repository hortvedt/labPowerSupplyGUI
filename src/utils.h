#pragma once

#include <algorithm>
#include <string>
#include <unitdefinitions.h>
// OS Specific milliSleep
#ifdef _WIN32
#include <windows.h>
#else
#include <map>
#include <unistd.h>
#endif

namespace psu::utils
{
    auto voltageToFixedWidthString( volt a_voltage ) -> std::string;
    auto currentToFixedWidthString( ampere a_current ) -> std::string;

    void validateVoltageValue( volt a_voltage );
    void validateCurrentValue( ampere a_current );

    void milliSleep( unsigned int a_millisecondTime );
    void secondSleep( second a_secondTime );

    template < typename Key, typename Value >
    auto findMinElement( const std::map< Key, Value >& a_map ) ->
        typename std::map< Key, Value >::const_iterator
    {
        if ( a_map.empty() )
        {
            return a_map.end();
        }

        return std::min_element( a_map.begin(),
                                 a_map.end(),
                                 []( const auto& a_first, const auto& a_second )
                                 { return a_first.second < a_second.second; } );
    }

    // TODO: add the csv stuff

} // namespace psu::utils
