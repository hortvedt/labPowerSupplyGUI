#pragma once

#include <QObject>

#include <QtQml/qqmlregistration.h>
#include <bccontroller.h>
#include <csvcontroller.h>
#include <psucontroller.h>

namespace psu::mmi
{

    class SingletonClass : public QObject
    {
        Q_OBJECT
        QML_SINGLETON

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
        serial_cpp::Serial* m_serial;
        psu::Psu* m_psu;
        psu::mmi::PsuController* m_psuController;
        psu::mmi::BcController* m_bcController;
        psu::mmi::CsvController* m_csvController;
    };

} // namespace psu::mmi
