#pragma once

#include <QObject>

#include <psu.h>
#include <unitdefinitions.h>

// Does no nullptr checks

namespace psu::mmi
{

    class PsuController : public QObject
    {
        Q_OBJECT

        Q_PROPERTY( psu::volt voltage READ voltage NOTIFY voltageChanged FINAL );
        Q_PROPERTY( psu::volt current READ current NOTIFY currentChanged FINAL );
        Q_PROPERTY( bool serialOpen READ serialOpen NOTIFY serialOpenChanged FINAL );
        Q_PROPERTY( bool currentLimited READ currentLimited NOTIFY currentLimitedChanged FINAL );
        Q_PROPERTY( bool voltageLimited READ voltageLimited NOTIFY voltageLimitedChanged FINAL );
        Q_PROPERTY( bool outputOn READ outputOn NOTIFY outputOnChanged FINAL );
        Q_PROPERTY( psu::volt setVoltage READ setVoltage NOTIFY setVoltageChanged FINAL );
        Q_PROPERTY( psu::ampere setCurrent READ setCurrent NOTIFY setCurrentChanged FINAL );
        Q_PROPERTY( QString identification READ identification NOTIFY identificationChanged FINAL );

    public:
        explicit PsuController( Psu* a_psu, QObject* a_parent = nullptr );

        //Methods
        volt voltage();
        ampere current();
        bool serialOpen();
        bool currentLimited();
        bool voltageLimited();
        bool outputOn();
        volt setVoltage();
        ampere setCurrent();
        QString identification();

        void createNewPsu();

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

        // Members
        bool m_serialSet = false;

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
