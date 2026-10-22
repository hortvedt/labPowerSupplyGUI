#pragma once

#include <QObject>

#include <batterycharger.h>
#include <psu.h>
#include <qqmlintegration.h>
#include <unitdefinitions.h>

namespace psu::mmi
{

        class BcController : public QObject
        {
            Q_OBJECT
            QML_ELEMENT
            QML_UNCREATABLE( "" )

            Q_PROPERTY( QString voltage READ voltageString NOTIFY voltageChanged );
            Q_PROPERTY( QString current READ currentString NOTIFY currentChanged );
            Q_PROPERTY(
                QString batteryVoltage READ batteryVoltageString NOTIFY batteryVoltageChanged );
            Q_PROPERTY( bool chargingOn READ chargingOn NOTIFY chargingOnChanged );

            Q_PROPERTY( volt voltageMax READ voltageMax NOTIFY chargeParamsChanged );
            Q_PROPERTY( unsigned int voltageMin READ voltageMin NOTIFY chargeParamsChanged );
            Q_PROPERTY( unsigned int currentMax READ currentMax NOTIFY chargeParamsChanged );
            Q_PROPERTY( unsigned int currentChargeCutOff READ currentChargeCutOff NOTIFY
                            chargeParamsChanged );
            Q_PROPERTY( unsigned int capacity READ capacity NOTIFY chargeParamsChanged );

            Q_PROPERTY( QList< unsigned int > socVoltage READ socVoltage NOTIFY socsChanged )
            Q_PROPERTY(
                QList< unsigned int > socChargeCurrent READ socChargeCurrent NOTIFY socsChanged )
        public:
            explicit BcController( BatteryCharger* a_batteryCharger,
                                   QObject* a_parent = nullptr ); // Needs to take a batteryCharger

            auto voltageString() -> QString;
            auto currentString() -> QString;
            auto batteryVoltageString() -> QString;
            auto chargingOn() -> bool;
            auto voltageMax() -> unsigned int;
            auto voltageMin() -> unsigned int;
            auto currentMax() -> unsigned int;
            auto currentChargeCutOff() -> unsigned int;
            auto capacity() -> unsigned int;

            auto socVoltage() -> QList< unsigned int >;
            auto socChargeCurrent() -> QList< unsigned int >;

        signals:

        private:
            BatteryCharger* m_batteryCharger { nullptr };

            volt m_voltage { 0 };
            ampere m_current { 0 };
            volt m_batteryVoltage { 0 };

            bool m_chargingOn { false };

            volt m_voltageMax { 0 };
            volt m_voltageMin { 0 };
            ampere m_currentMax { 0 };
            ampere m_currentChargeCutOff { 0 };
            ah m_capacity { 0 };

            QList< unsigned int > m_socVoltage;
            QList< unsigned int > m_socChargeCurrent;
        };

} // namespace psu
