#pragma once

#include <QObject>

#include <QtQml/qqmlregistration.h>
#include <applicationcontroller.h>
#include <bccontroller.h>
#include <csvcontroller.h>
#include <psucontroller.h>

namespace psu::mmi
{

    class SingletonClass : public QObject
    {
        Q_OBJECT
        QML_SINGLETON

        Q_PROPERTY( psu::mmi::PsuController psuController MEMBER m_psuController CONSTANT )
        Q_PROPERTY( psu::mmi::BcController bcController MEMBER m_bcController CONSTANT )
        Q_PROPERTY( psu::mmi::CsvController psuController MEMBER m_csvController CONSTANT )
        Q_PROPERTY( psu::mmi::ApplicationController applicationController MEMBER
                        m_applicationController CONSTANT )

    public:
        explicit SingletonClass( QObject* parent = nullptr );

        void setSerial( const std::string& a_port, // com
                        unsigned int a_baudrate = 9600,
                        second a_serialWaitTime = 0.05, // Hopefully not needed
                        serial_cpp::Timeout a_timeOut = serial_cpp::Timeout(),
                        serial_cpp::bytesize_t a_bytesize = serial_cpp::eightbits,
                        serial_cpp::parity_t a_parity = serial_cpp::parity_none,
                        serial_cpp::stopbits_t a_stopbits = serial_cpp::stopbits_one,
                        serial_cpp::flowcontrol_t a_flowcontrol = serial_cpp::flowcontrol_none );

    signals:

    private:
        serial_cpp::Serial* m_serial { nullptr };
        psu::Psu* m_psu { nullptr };
        psu::mmi::PsuController* m_psuController { nullptr };
        psu::mmi::BcController* m_bcController { nullptr };
        psu::mmi::CsvController* m_csvController { nullptr };
        psu::mmi::ApplicationController* m_applicationController { nullptr };
    };

} // namespace psu::mmi
