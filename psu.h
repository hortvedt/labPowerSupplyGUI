#pragma once

#include <vector>
// #include <chrono>
#include <serial_cpp/serial.h>

namespace psu
{

using time = double;

class Psu
{
public:
    Psu( std::string a_com,
         uint a_baudrate = 9600,
         time a_timeOut = 1,
         time a_serialWaitTime = 0.05 );

    void closeSerial();
    void writeSerial();
    void writeSerialContinually();
    void setSetVoltage( double a_voltage ); // vset
    void setSetCurrent( double a_current ); // iset
    void turnOutputOn();
    void turnOutputOff();
    auto getSetVoltage() -> double;
    auto getSetCurrent() -> double;
    auto getStatus() -> std::string;
    void updateStatus( bool a_verbose = false );
    double voltage();
    double current();
    double measureVoltage( double a_safeVoltage = 5,
                           time a_waitForMeasurement = 0.5,
                           double a_checkingCurrent = 0 );

    // TODO: include the csv stuff

private: // methods
private: // members
    // byte vectors
    std::vector< char > m_status;
    std::vector< char > m_setVoltage; // setV
    std::vector< char > m_setCurrent; // setI
    std::vector< char > m_identification;

    // Status flags
    bool m_currentLimited; // cv, Current or voltage limited?
    bool m_on;
    bool m_ocp; // What is it?

    time m_serialWaitTime;
    time m_timeOutTime;

    serial_cpp::Serial m_serial;
};

} // namespace psu
