#define BOOST_TEST_MODULE CoreFunctionalityTest
#include <boost/test/included/unit_test.hpp>

#include <psu.h>
#include <utils.h>

BOOST_AUTO_TEST_SUITE( coreFuntionalityTests )

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE( utilsTests )

BOOST_AUTO_TEST_CASE( voltageToFixedWidthStringTest )
{
    double voltage { 2.4 };
    std::string voltageString { psu::utils::voltageToFixedWidthString( voltage ) };
    std::string correctString { "02.40" };
    BOOST_CHECK_EQUAL( voltageString, correctString );
}

BOOST_AUTO_TEST_CASE( currentToFixedWidthStringTest )
{
    double current { 4.4 };
    std::string currentString { psu::utils::currentToFixedWidthString( current ) };
    std::string correctString { "4.400" };
    BOOST_CHECK_EQUAL( currentString, correctString );
}

BOOST_AUTO_TEST_CASE( validateVoltageValueTest )
{
    BOOST_REQUIRE_THROW( psu::utils::validateVoltageValue( 30.1 ), std::out_of_range );
    BOOST_REQUIRE_THROW( psu::utils::validateVoltageValue( -1 ), std::out_of_range );
}

BOOST_AUTO_TEST_CASE( validateCurrentValueTest )
{
    BOOST_REQUIRE_THROW( psu::utils::validateCurrentValue( 5.1 ), std::out_of_range );
    BOOST_REQUIRE_THROW( psu::utils::validateCurrentValue( -1 ), std::out_of_range );
}

BOOST_AUTO_TEST_SUITE_END()
