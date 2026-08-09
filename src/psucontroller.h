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

        Q_PROPERTY( QString voltage READ voltageString NOTIFY voltageChanged );
        Q_PROPERTY( QString current READ currentString NOTIFY currentChanged );
        Q_PROPERTY( bool serialOpen READ serialOpen NOTIFY serialOpenChanged );
        Q_PROPERTY( bool currentLimited READ currentLimited NOTIFY currentLimitedChanged );
        Q_PROPERTY( bool voltageLimited READ voltageLimited NOTIFY voltageLimitedChanged );
        Q_PROPERTY( bool outputOn READ outputOn NOTIFY outputOnChanged );
        Q_PROPERTY( QString valueSetVoltage READ valueOfSetVoltageString NOTIFY setVoltageChanged );
        Q_PROPERTY( QString valueSetCurrent READ valueOfSetCurrentString NOTIFY setCurrentChanged );
        Q_PROPERTY( QString identification READ identification NOTIFY identificationChanged );

        Q_PROPERTY( bool tempDifferentFromSetVoltage READ tempDifferentFromSetVoltage NOTIFY
                        tempDifferentFromSetVoltageChanged );
        Q_PROPERTY( bool tempDifferentFromSetCurrent READ tempDifferentFromSetCurrent NOTIFY
                        tempDifferentFromSetCurrentChanged );

    public:
        explicit PsuController( Psu* a_psu, QObject* a_parent = nullptr );

        //Methods
        auto voltage() -> volt;
        auto voltageString() -> QString;
        auto current() -> ampere;
        auto currentString() -> QString;
        auto serialOpen() -> bool;
        auto currentLimited() -> bool;
        auto voltageLimited() -> bool;
        auto outputOn() -> bool;
        auto valueOfSetVoltage() -> volt;
        auto valueOfSetVoltageString() -> QString;
        auto valueOfSetCurrent() -> ampere;
        auto valueOfSetCurrentString() -> QString;
        auto identification() -> QString;        

        auto connectedToPsu() -> bool;

        void updateContinuallyChangingData();
        void updateSetState();
        void updateIdentification();

        auto isSerialSet() -> bool;

        auto tempDifferentFromSetVoltage() -> bool;
        auto tempDifferentFromSetCurrent() -> bool;

    public slots:
        void setVoltage( volt a_voltage );
        void setCurrent( ampere a_current );

        void setTempVoltage( volt a_voltage );
        void setTempCurrent( volt a_current );

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

        void tempDifferentFromSetVoltageChanged();
        void tempDifferentFromSetCurrentChanged();

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

        // volt m_tempValueSetVoltage;
        // ampere m_tempValueSetCurrent;

        bool m_tempDifferentFromSetVoltage;
        bool m_tempDifferentFromSetCurrent;

        // Setup
        // std::string m_port;
        // unsigned int m_baudrate;
        // second m_serialWaitTime; // Not sure this is nedded any longer.
        // serial_cpp::Timeout m_timeOut;
        // serial_cpp::bytesize_t m_bytesize;
        // serial_cpp::parity_t m_parity;
        // serial_cpp::stopbits_t m_stopbits;
        // serial_cpp::flowcontrol_t m_flowcontrol;

        Psu* m_psu;

        // Statuses
        volt m_voltage { 0 };
        ampere m_current { 0 };
        bool m_serialOpen { false };
        bool m_currentLimited { false };
        bool m_voltageLimited { false };
        bool m_outputOn { false };
        volt m_setVoltage { 0 };
        ampere m_setCurrent { 0 };
        QString m_identification;

        double m_epsilon { 0.0001 };
    };

} // namespace psu
