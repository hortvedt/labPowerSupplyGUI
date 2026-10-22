#include <bccontroller.h>

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
        volt voltage = m_batteryCharger->readVoltage();
        std::string voltageString = utils::voltageToFixedWidthString( voltage );
        return QString::fromStdString( voltageString );
    }

    auto BcController::currentString() -> QString
    {
        ampere current = m_batteryCharger->readCurrent();
        std::string currentString = utils::currentToFixedWidthString( current );
        return QString::fromStdString( currentString );
    }

    auto BcController::batteryVoltageString() -> QString
    {
        volt voltage = m_batteryCharger->measureBatteryVoltage();
        std::string voltageString = utils::voltageToFixedWidthString( voltage );
        return QString::fromStdString( voltageString );
    }

    auto BcController::chargingOn() -> bool
    {
        return m_chargingOn;
    }

    auto BcController::voltageMax() -> unsigned int
    {
        return m_voltageMax;
    }

    auto BcController::voltageMin() -> unsigned int
    {
        return m_voltageMin;
    }

    auto BcController::currentMax() -> unsigned int
    {
        return m_currentMax;
    }

    auto BcController::currentChargeCutOff() -> unsigned int
    {
        return m_currentChargeCutOff;
    }

    auto BcController::capacity() -> unsigned int
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
