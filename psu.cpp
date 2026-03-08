#include <psu.h>

#include <utils.h>
// OS Specific sleep
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

namespace psu {

    Psu::Psu( const std::string& a_port, uint a_baudrate, time a_timeOut, time a_serialWaitTime )
        : m_serialWaitTime( a_serialWaitTime )
        , m_timeOutTime( a_timeOut )
        , m_serial( a_port, a_baudrate, m_timeOutTime )
    {
    }

    void Psu::closeSerial()
    {
        m_serial.close();
    }

    void Psu::sleep( uint a_millisecondTime )
    {
#ifdef _WIN32
        Sleep( a_millisecondTime );
#else
        usleep( a_millisecondTime * 1000 );
#endif
    }

    void Psu::writeSerial( const std::string& a_command )
    {
        m_serial.write( a_command + ENDCHARS );
        m_serial.flushOutput();
        sleep( m_serialWaitTime );
    }

    void Psu::setVoltage( double a_voltage )
    {
        utils::validateVoltageValue( a_voltage );
        std::string voltageString { SET_VOLTAGE };
        voltageString += utils::voltageToFixedWidthString( a_voltage );
        writeSerial( voltageString );
        updateStatus();
    }
    void Psu::setCurrent( double a_current )
    {
        utils::validateCurrentValue( a_current );
        std::string currentString { SET_CURRENT };
        currentString += utils::currentToFixedWidthString( a_current );
        updateStatus();
    }

    void Psu::turnOutputOn()
    {
        writeSerial( OUTPUT_ON );
        updateStatus();
    }

    void Psu::turnOutputOff()
    {
        writeSerial( OUTPUT_OFF );
        updateStatus();
    }

    auto Psu::getSetVoltage() -> double
    {
        m_setVoltage.clear();
        writeSerial( VOLTAGE_SET );
        m_serial.readline( m_setVoltage );
        return std::stod( m_setVoltage );
    }

    auto Psu::getSetCurrent() -> double
    {
        m_setCurrent.clear();
        writeSerial( CURRENT_SET );
        m_serial.readline( m_setCurrent );
        return std::stod( m_setCurrent );
    }

    auto Psu::getStatus() -> std::string
    {
        m_status.clear();
        writeSerial( VOLTAGE_SET );
        m_serial.readline( m_status );
        // TODO should probably check that it returns size 3.
        return m_status;
    }

    void Psu::updateStatus()
    {
        getStatus();

        m_currentLimited = m_status.at( 0 ) == '1';
        m_outputOn = m_status.at( 1 ) == '1';
        m_ocp = m_status.at( 2 ) == '1';

        // TODO add the verbose part
    }

    auto Psu::voltage() -> double
    {
        m_voltage.clear();
        writeSerial( CURRENT_OUTPUT );
        m_serial.readline( m_voltage );
        return std::stod( m_voltage );
    }

    auto Psu::current() -> double
    {
        return {};
    }

    auto Psu::measureVoltage( double a_safeVoltage,
                              time a_waitForMeasurement,
                              double a_checkingCurrent ) -> double
    {
        return {};
    }

    void Psu::setVerbose( bool a_verbose )
    {
        m_verbose = a_verbose;
    }

    auto Psu::getIdentification() -> std::string
    {
        m_identification.clear();
        writeSerial( IDENTIFICATION );
        m_serial.readline( m_identification );
        return m_identification;
    }

} // namespace psu
