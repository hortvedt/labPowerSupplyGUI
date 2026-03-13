#include "batterycharger.h"
#include <yaml-cpp/yaml.h>

namespace psu::bc
{

    BatteryCharger::BatteryCharger( Psu& a_psu )
        : m_psu { a_psu }
    {
    }

    void BatteryCharger::updateHistory()
    {
        m_timeHistory.push_back( std::chrono::system_clock::now() );
        m_voltageHistory.push_back( m_voltage );
        m_currentHistory.push_back( m_current );
        m_batteryVoltageHistory.push_back( m_batteryVoltage );
    }

    auto BatteryCharger::readyBeforeCharge() -> bool
    {
        m_batteryVoltage = readBatteryVoltage();

        return {};
    }

    void BatteryCharger::setChargeParams( std::filesystem::path a_yamlFile ) {}

    void BatteryCharger::setBatteryParams( std::filesystem::path a_yamlFile ) {}

} // namespace psu::bc
