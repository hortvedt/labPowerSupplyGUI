#pragma once

#include <QObject>
#include <comboboxmodel.h>
#include <psu.h>
#include <qqmlintegration.h>

namespace psu::mmi
{

    class ConnectionController : public QObject
    {
        Q_OBJECT
        QML_ELEMENT
        QML_UNCREATABLE( "" )

        Q_PROPERTY( bool connectedToPsu READ connectedToPsu NOTIFY connectedToPsuChanged )

        Q_PROPERTY( psu::mmi::ComboBoxModel* bytesizeCombo READ bytesizeCombo CONSTANT )
        Q_PROPERTY( psu::mmi::ComboBoxModel* parityCombo READ parityCombo CONSTANT )
        Q_PROPERTY( psu::mmi::ComboBoxModel* stopbitsCombo READ stopbitsCombo CONSTANT )
        Q_PROPERTY( psu::mmi::ComboBoxModel* flowcontrolCombo READ flowcontrolCombo CONSTANT )

    public:
        explicit ConnectionController( Psu* a_psu, QObject* parent = nullptr );

        void setSerial( const std::string& a_port, // com
                        unsigned int a_baudrate = 9600,
                        second a_serialWaitTime = 0.00, // Hopefully not needed
                        serial_cpp::Timeout a_timeOut = serial_cpp::Timeout(),
                        serial_cpp::bytesize_t a_bytesize = serial_cpp::eightbits,
                        serial_cpp::parity_t a_parity = serial_cpp::parity_none,
                        serial_cpp::stopbits_t a_stopbits = serial_cpp::stopbits_one,
                        serial_cpp::flowcontrol_t a_flowcontrol = serial_cpp::flowcontrol_none );

    signals:
        void connectedToPsuChanged();

    public slots:
        auto connectToPsu() -> bool;

    private:
        // methods
        auto connectedToPsu() -> bool;
        auto bytesizeCombo() -> ComboBoxModel*;
        auto parityCombo() -> ComboBoxModel*;
        auto stopbitsCombo() -> ComboBoxModel*;
        auto flowcontrolCombo() -> ComboBoxModel*;

        // members
        serial_cpp::Serial* m_serial { nullptr };
        psu::Psu* m_psu { nullptr };

        bool m_connectedToPsu;

        ComboBoxModel m_bytesizeCombo;
        ComboBoxModel m_parityCombo;
        ComboBoxModel m_stopbitsCombo;
        ComboBoxModel m_flowcontrolCombo;

        std::string m_port; // com
        unsigned int m_baudrate { 9600 };
        second m_serialWaitTime { 0.00 }; // Hopefully not needed, was 0.05
        serial_cpp::Timeout m_timeOut { serial_cpp::Timeout() };
        serial_cpp::bytesize_t m_bytesize { serial_cpp::eightbits };
        serial_cpp::parity_t m_parity { serial_cpp::parity_none };
        serial_cpp::stopbits_t m_stopbits { serial_cpp::stopbits_one };
        serial_cpp::flowcontrol_t m_flowcontrol { serial_cpp::flowcontrol_none };
    };
} // namespace psu::mmi
