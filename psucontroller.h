#pragma once

#include <QObject>

#include <psu.h>
#include <qqmlintegration.h>
#include <unitdefinitions.h>

// Does no nullptr checks

namespace psu::mmi
{

    class PsuController : public QObject
    {
        Q_OBJECT
        QML_ELEMENT
        QML_UNCREATABLE( "" )

        Q_PROPERTY( psu::volt voltage READ voltage NOTIFY voltageChanged );
        Q_PROPERTY( psu::volt current READ current NOTIFY currentChanged );
        Q_PROPERTY( bool serialOpen READ serialOpen NOTIFY serialOpenChanged );
        Q_PROPERTY( bool currentLimited READ currentLimited NOTIFY currentLimitedChanged );
        Q_PROPERTY( bool voltageLimited READ voltageLimited NOTIFY voltageLimitedChanged );
        Q_PROPERTY( bool outputOn READ outputOn NOTIFY outputOnChanged );
        Q_PROPERTY( psu::volt setVoltage READ setVoltage NOTIFY setVoltageChanged );
        Q_PROPERTY( psu::ampere setCurrent READ setCurrent NOTIFY setCurrentChanged );
        Q_PROPERTY( QString identification READ identification NOTIFY identificationChanged );

    public:
        explicit PsuController( Psu* a_psu, QObject* a_parent = nullptr );

        //Methods
        auto voltage() -> volt;
        auto current() -> ampere;
        auto serialOpen() -> bool;
        auto currentLimited() -> bool;
        auto voltageLimited() -> bool;
        auto outputOn() -> bool;
        auto setVoltage() -> volt;
        auto setCurrent() -> ampere;
        auto identification() -> QString;

        // void createNewPsu();

        auto connectedToPsu() -> bool;

        void updateContinuallyChangingData();
        void updateSetState();
        void updateIdentification();

        // void setPsu( Psu* a_psu );
        auto isSerialSet() -> bool;

    signals:
        void voltageChanged();
        void currentChanged();
        void serialOpenChanged();

        void currentLimitedChanged();
        void voltageLimitedChanged();
        void outputOnChanged();

        void setVoltageChanged();
        void setCurrentChanged();
        void identificationChanged();

    private:
        // Methods
        void getAllValues();
        void resetAllValues();
        void outputOffReset();

        void updateVoltage();
        void updateCurrent();
        void updateStatus();

        void updateSetVoltage();
        void updateSetCurrent();
        void updateSerialOpen();

        // Members
        bool m_serialSet = false;
        bool m_allValuesReset = true;

        // Setup
        std::string m_port;
        unsigned int m_baudrate;
        second m_serialWaitTime; // Not sure this is nedded any longer.
        serial_cpp::Timeout m_timeOut;
        serial_cpp::bytesize_t m_bytesize;
        serial_cpp::parity_t m_parity;
        serial_cpp::stopbits_t m_stopbits;
        serial_cpp::flowcontrol_t m_flowcontrol;

        Psu* m_psu;

        // Statuses
        volt m_voltage;
        ampere m_current;
        bool m_serialOpen;
        bool m_currentLimited;
        bool m_voltageLimited;
        bool m_outputOn;
        volt m_setVoltage;
        ampere m_setCurrent;
        QString m_identification;
    };

} // namespace psu
