#pragma once

#include <serial_cpp/serial.h>
#include <unitdefinitions.h>

namespace psu
{
    constexpr std::string ENDCHARS = "\r\n";
    constexpr std::string SET_VOLTAGE = "VSET1:";
    constexpr std::string VOLTAGE_SET = "VSET1?";
    constexpr std::string VOLTAGE_OUTPUT = "VOUT1?";
    constexpr std::string SET_CURRENT = "ISET1:";
    constexpr std::string CURRENT_SET = "ISET1?";
    constexpr std::string CURRENT_OUTPUT = "IOUT1?";
    constexpr std::string OUTPUT_ON = "OUTPUT1";
    constexpr std::string OUTPUT_OFF = "OUTPUT0";
    constexpr std::string STATUS = "STATUS?";
    constexpr std::string IDENTIFICATION = "*IDN?";

    using time = double;
    using volt = double;
    using ampere = double;

    class Psu
    {
    public:
        explicit Psu( const std::string& a_port, // com
                      uint a_baudrate = 9600,
                      time a_timeOut = 1,
                      time a_serialWaitTime = 0.05 );

        void closeSerial();
        void openSerial();
        void setVoltage( volt a_voltage );   // vset
        void setCurrent( ampere a_current ); // iset
        void turnOutputOn();
        void turnOutputOff();
        auto getSetVoltage() -> volt;
        auto getSetCurrent() -> ampere;
        auto getStatus() -> std::string;         // should this return or just fetch the new value
        auto getIdentification() -> std::string; // should this return or just fetch the new value
        void updateStatus();
        auto voltage() -> volt;
        auto current() -> ampere;
        auto measureVoltage( volt a_safeVoltage = 5,
                             time a_waitForMeasurement = 0.5,
                             ampere a_checkingCurrent = 0 ) -> double;

        void setVerbose( bool a_verbose );

        // TODO: include the csv stuff

    private: // methods
        // TODO Fint out what can be private
        void sleep( uint a_time );
        void writeSerial( const std::string& a_command );

    private: // members
        // Strings
        std::string m_statusString;     // might not be kept, just use the flags instead
        std::string m_setVoltageString; // setV, might not be kept
        std::string m_setCurrentString; // setI, might not be kept
        std::string m_identificationString;
        std::string m_currentString;
        std::string m_voltageString;

        // Values
        volt m_setVoltage;
        ampere m_setCurrent;

        // Status flags
        bool m_currentLimited = false; // cv, Current or voltage limited?
        bool m_outputOn = false;       // on
        bool m_ocp = false;            // ocp, What is it?

        time m_serialWaitTime;
        serial_cpp::Timeout m_timeOutTime;

        serial_cpp::Serial m_serial;

        bool m_verbose = false; // TODO Do something with this
    };

} // namespace psu
