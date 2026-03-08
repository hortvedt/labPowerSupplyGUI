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
} // namespace psu::utils
