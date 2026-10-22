#include <singletonclass.h>

#include <QObject>
#include <applicationcontroller.h>
#include <batterycharger.h>
#include <bccontroller.h>
#include <connectioncontroller.h>
#include <csvcontroller.h>
#include <memory>
#include <psu.h>
#include <psucontroller.h>
#include <qqmlengine.h>
#include <serial_cpp/serial.h>
#include <string>
#include <unitdefinitions.h>

namespace psu::mmi
{

    SingletonClass::SingletonClass( QObject* a_parent )
        : QObject { a_parent }
        , m_psu { new Psu() }
        , m_batteryCharger { new BatteryCharger( m_psu ) }
        , m_psuController { new PsuController( m_psu, this ) }
        , m_bcController { new BcController( m_batteryCharger, this ) }
        // Maybe take the PsuController instead of the psu directly
        , m_csvController { new CsvController( m_psu, this ) }
        , m_connectionController { new ConnectionController( m_psu, this ) }
        , m_applicationController { new ApplicationController( m_psu, this ) }
    {
    }

    auto SingletonClass::create( QQmlEngine* a_qmlEngine ) -> std::unique_ptr< SingletonClass >
    {
        return std::make_unique< SingletonClass >( a_qmlEngine );
    }

    void SingletonClass::setSerial( const std::string& a_port,
                                    unsigned int a_baudrate,
                                    second a_serialWaitTime,
                                    const serial_cpp::Timeout& a_timeOut,
                                    serial_cpp::bytesize_t a_bytesize,
                                    serial_cpp::parity_t a_parity,
                                    serial_cpp::stopbits_t a_stopbits,
                                    serial_cpp::flowcontrol_t a_flowcontrol )
    {
        delete m_serial;

        m_serial = new serial_cpp::Serial( a_port, // Maybe use shared pointer or something
                                           a_baudrate,
                                           a_timeOut,
                                           a_bytesize,
                                           a_parity,
                                           a_stopbits,
                                           a_flowcontrol );

        m_psu->setSerial( m_serial, a_serialWaitTime );
    }

} // namespace psu::mmi
