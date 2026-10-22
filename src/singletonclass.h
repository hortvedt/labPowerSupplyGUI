#pragma once

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
#include <qqmlintegration.h>
#include <qtmetamacros.h>
#include <serial_cpp/serial.h>
#include <string>
#include <unitdefinitions.h>

namespace psu::mmi
{

    class SingletonClass : public QObject
    {
        Q_OBJECT
        QML_ELEMENT
        QML_SINGLETON

        Q_PROPERTY( psu::mmi::PsuController* psuController MEMBER m_psuController CONSTANT )
        Q_PROPERTY( psu::mmi::BcController* bcController MEMBER m_bcController CONSTANT )
        Q_PROPERTY( psu::mmi::CsvController* csvController MEMBER m_csvController CONSTANT )
        Q_PROPERTY( psu::mmi::ConnectionController* connectionController MEMBER
                        m_connectionController CONSTANT )
        Q_PROPERTY( psu::mmi::ApplicationController* applicationController MEMBER
                        m_applicationController CONSTANT )

    public:
        explicit SingletonClass( QObject* parent = nullptr );

        static auto create( QQmlEngine* a_qmlEngine ) -> std::unique_ptr< SingletonClass >;

        void setSerial( const std::string& a_port, // com
                        unsigned int a_baudrate = DEFAULT_BAUDRATE,
                        second a_serialWaitTime = DEFAULT_SERIAL_WAIT_TIME, // Hopefully not needed
                        const serial_cpp::Timeout& a_timeOut = serial_cpp::Timeout(),
                        serial_cpp::bytesize_t a_bytesize = serial_cpp::eightbits,
                        serial_cpp::parity_t a_parity = serial_cpp::parity_none,
                        serial_cpp::stopbits_t a_stopbits = serial_cpp::stopbits_one,
                        serial_cpp::flowcontrol_t a_flowcontrol = serial_cpp::flowcontrol_none );

    signals:

    private:
        serial_cpp::Serial* m_serial { nullptr };
        psu::Psu* m_psu { nullptr };
        psu::BatteryCharger* m_batteryCharger { nullptr };
        psu::mmi::PsuController* m_psuController { nullptr };
        psu::mmi::BcController* m_bcController { nullptr };
        psu::mmi::CsvController* m_csvController { nullptr };
        psu::mmi::ConnectionController* m_connectionController { nullptr };
        psu::mmi::ApplicationController* m_applicationController { nullptr };
    };

} // namespace psu::mmi
