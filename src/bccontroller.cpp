#include <bccontroller.h>

#include <QList>
#include <QObject>
#include <QString>
#include <batterycharger.h>
#include <string>
#include <unitdefinitions.h>
#include <utils.h>

namespace psu::mmi
{
    BcController::BcController( BatteryCharger *a_batteryCharger, QObject *a_parent )
        : QObject { a_parent }
        , m_batteryCharger { a_batteryCharger }
    {
    }

    auto BcController::voltageString() -> QString
    {
        const volt voltage = m_batteryCharger->readVoltage();
        const std::string voltageString = utils::voltageToFixedWidthString( voltage );
        return QString::fromStdString( voltageString );
    }

    auto BcController::currentString() -> QString
    {
        const ampere current = m_batteryCharger->readCurrent();
        const std::string currentString = utils::currentToFixedWidthString( current );
        return QString::fromStdString( currentString );
    }

    auto BcController::batteryVoltageString() -> QString
    {
        const volt voltage = m_batteryCharger->measureBatteryVoltage();
        const std::string voltageString = utils::voltageToFixedWidthString( voltage );
        return QString::fromStdString( voltageString );
    }

    auto BcController::chargingOn() -> bool
    {
        return m_chargingOn;
    }

    auto BcController::voltageMax() -> volt
    {
        return m_voltageMax;
    }

    auto BcController::voltageMin() -> volt
    {
        return m_voltageMin;
    }

    auto BcController::currentMax() -> ampere
    {
        return m_currentMax;
    }

    auto BcController::currentChargeCutOff() -> ampere
    {
        return m_currentChargeCutOff;
    }

    auto BcController::capacity() -> ah
    {
        return m_capacity;
    }

    auto BcController::socVoltage() -> QList< unsigned int >
    {
        return m_socVoltage;
    }

    auto BcController::socChargeCurrent() -> QList< unsigned int >
    {
        return m_socChargeCurrent;
    }

} // namespace psu::mmi
