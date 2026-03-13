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

    void Psu::openSerial()
    {
        m_serial.open();
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

    void Psu::setVoltage( volt a_voltage )
    {
        utils::validateVoltageValue( a_voltage );
        std::string voltageString { SET_VOLTAGE };
        voltageString += utils::voltageToFixedWidthString( a_voltage );
        writeSerial( voltageString );
        m_setVoltage = a_voltage;
        updateStatus();
    }
    void Psu::setCurrent( ampere a_current )
    {
        utils::validateCurrentValue( a_current );
        std::string currentString { SET_CURRENT };
        currentString += utils::currentToFixedWidthString( a_current );
        m_setCurrent = a_current;
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

    auto Psu::getSetVoltage() -> volt
    {
        m_setVoltageString.clear();
        writeSerial( VOLTAGE_SET );
        m_serial.readline( m_setVoltageString );
        return std::stod( m_setVoltageString );
    }

    auto Psu::getSetCurrent() -> ampere
    {
        m_setCurrentString.clear();
        writeSerial( CURRENT_SET );
        m_serial.readline( m_setCurrentString );
        return std::stod( m_setCurrentString );
    }

    auto Psu::getStatus() -> std::string
    {
        m_statusString.clear();
        writeSerial( STATUS );
        m_serial.readline( m_statusString );
        // TODO should probably check that it returns size 3.
        return m_statusString;
    }

    void Psu::updateStatus()
    {
        getStatus();

        m_currentLimited = m_statusString.at( 0 ) == '1';
        m_outputOn = m_statusString.at( 1 ) == '1';
        m_ocp = m_statusString.at( 2 ) == '1';

        // TODO add the verbose part
    }

    auto Psu::voltage() -> volt
    {
        m_voltageString.clear();
        writeSerial( CURRENT_OUTPUT );
        m_serial.readline( m_voltageString );
        return std::stod( m_voltageString );
    }

    auto Psu::current() -> ampere
    {
        m_currentString.clear();
        writeSerial( CURRENT_OUTPUT );
        m_serial.readline( m_currentString );
        return std::stod( m_currentString );
    }

    auto Psu::measureVoltage( volt a_safeVoltage,
                              time a_waitForMeasurement,
                              ampere a_checkingCurrent ) -> volt
    {
        bool outputOnBeforeMeasurement { m_outputOn };
        volt setVoltageBeforeMeasurement { m_setVoltage };
        ampere setCurrentBeforeMeasurement { m_setCurrent };

        setCurrent( a_checkingCurrent );
        setVoltage( a_safeVoltage );
        if ( not outputOnBeforeMeasurement )
        {
            turnOutputOn();
        }
        sleep( a_waitForMeasurement );

        volt batteryVoltage { voltage() };

        if ( not outputOnBeforeMeasurement )
        {
            turnOutputOff();
        }
        setVoltage( setVoltageBeforeMeasurement );
        setCurrent( setCurrentBeforeMeasurement );

        return batteryVoltage;
    }

    void Psu::setVerbose( bool a_verbose )
    {
        m_verbose = a_verbose;
    }

    auto Psu::getIdentification() -> std::string
    {
        m_identificationString.clear();
        writeSerial( IDENTIFICATION );
        m_serial.readline( m_identificationString );
        return m_identificationString;
    }

} // namespace psu
