#pragma once

#include <future>
#include <serial_cpp/serial.h>
#include <unitdefinitions.h>

// Implement Queue-Based with Worker Thread
// Is unsafe, does not check for set serial interface

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

    using second = double;
    using volt = double;
    using ampere = double;

    class Psu
    {
    public:
        explicit Psu();

        void closeSerial();
        void openSerial();
        auto serialOpen() -> bool;
        void setVoltage( volt a_voltage );   // vset
        void setCurrent( ampere a_current ); // iset
        void turnOutputOn();
        void turnOutputOff();
        auto getSetVoltage() -> volt;
        auto getSetCurrent() -> ampere;
        auto getStatus() -> std::string&; // should this return or just fetch the new value
        auto getCurrentLimited() -> bool;
        auto getVoltageLimited() -> bool;
        auto getoutputOn() -> bool;
        auto getIdentification() -> std::string&; // should this return or just fetch the new value
        void updateStatus();
        auto voltage() -> volt;
        auto current() -> ampere;
        auto measureVoltage( volt a_safeVoltage = 5,
                             second a_waitForMeasurement = 0.5,
                             ampere a_checkingCurrent = 0 ) -> std::future< volt >;

        void setVerbose( bool a_verbose );

        void setSerial( serial_cpp::Serial* a_serial, second a_serialWaitTime = 0.05 );
        auto isSerialSet() const -> bool;

    private: // methods
        // TODO Fint out what can be private
        void sleep( unsigned int a_time ); // Should use a unit
        void writeSerial( const std::string& a_command );
        auto measureVoltageAsync( volt a_safeVoltage,
                                  second a_waitForMeasurement,
                                  ampere a_checkingCurrent ) -> volt;

    private: // members
        std::mutex m_mutex;

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
        bool m_currentLimited { false }; // cv, Current or voltage limited?
        bool m_outputOn { false };       // on
        bool m_ocp { false };            // ocp, What is it? Guessing voltageLimited

        second m_serialWaitTime;

        serial_cpp::Serial* m_serial { nullptr };

        bool m_verbose { false }; // TODO Do something with this
    };

} // namespace psu
