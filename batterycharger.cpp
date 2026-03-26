#include "batterycharger.h"

#include <assert.h>

// #include <yaml-cpp/yaml.h>

namespace psu::bc
{

    BatteryCharger::BatteryCharger( Psu& a_psu )
        : m_psu { a_psu }
    {
    }

    void BatteryCharger::startCharging()
    {
        try
        {
            turnOffOutput();
            if ( readyBeforeCharge() )
            {
                chargingStartup();

                m_charging = true;
                m_chargingThread = std::thread( &BatteryCharger::mainChargeLoop, this );

                chargingEnding();
            }
        }
        catch ( const std::exception& error )
        {
            turnOffOutput();
            throw error;
        }
    }

    void BatteryCharger::endCharging()
    {
        m_charging = false;
        turnOffOutput();
        if ( m_chargingThread.joinable() )
        {
            m_chargingThread.join();
        }
    }

    void BatteryCharger::startSerial()
    {
        m_psu.openSerial();
    }

    auto BatteryCharger::chargeCheck() -> bool
    {
        return ( m_batteryVoltage > m_voltageMin && m_batteryVoltage < m_voltageChargeCutOff
                 && m_current > m_currentChargeCutOff );
    }

    void BatteryCharger::measureAndUpdateChargeMembers()
    {
        readVoltage();
        readCurrent();
        measureBatteryVoltage();
        auto socVoltageIterator = m_socVoltage.upper_bound( m_soc );
        while ( socVoltageIterator != m_socVoltage.end()
                && m_batteryVoltage > socVoltageIterator->second )
        {
            m_soc = socVoltageIterator->first;
            ++socVoltageIterator;
        }

        m_waitTimeBetweenMeasurements = m_baseTimeBetweenMeasurements
                                        / ( m_socChargeCurrent.at( m_soc ) / m_capacity );
    }

    // void BatteryCharger::updateHistory()
    // {
    //     m_timeHistory.push_back( std::chrono::system_clock::now() );
    //     m_voltageHistory.push_back( m_voltage );
    //     m_currentHistory.push_back( m_current );
    //     m_batteryVoltageHistory.push_back( m_batteryVoltage );
    // }

    auto BatteryCharger::readyBeforeCharge() -> bool
    {
        return ( batteryVoltagesValid() && batteryParamsValid() );
    }

    auto BatteryCharger::measureBatteryVoltage() -> volt
    {
        auto futureBatteryVoltage = m_psu.measureVoltage( m_voltageMax,
                                                          m_waitTimeForBatteryVoltageMeasurements );
        m_batteryVoltage = futureBatteryVoltage.get();
        return m_batteryVoltage;
    }

    void BatteryCharger::setVoltage( volt a_voltage )
    {
        // Could add a while and do it until it changes
        // I have a todo at the psu level to check for already set value
        assert( a_voltage < m_voltageMax );
        m_psu.setVoltage( a_voltage );
        getSetVoltage();
    }

    void BatteryCharger::setCurrent( ampere a_current )
    {
        assert( a_current < m_currentMax );
        m_psu.setCurrent( a_current );
        getSetCurrent();
    }

    void BatteryCharger::endSerial()
    {
        m_psu.closeSerial();
    }

    auto BatteryCharger::readVoltage() -> volt
    {
        m_voltage = m_psu.voltage();
        return m_voltage;
    }

    auto BatteryCharger::readCurrent() -> ampere
    {
        m_current = m_psu.current();
        return m_current;
    }

    void BatteryCharger::chargingStartup()
    {
        turnOffOutput();
        setVoltage( m_voltageMax );
        setCurrent( utils::findMinElement( m_socChargeCurrent )->second );
        turnOnOutput();
        utils::secondSleep( m_waitTimeForBatteryVoltageMeasurements );
        measureAndUpdateChargeMembers();
    }

    void BatteryCharger::chargingEnding()
    {
        turnOffOutput();
    }

    void BatteryCharger::mainChargeLoop()
    {
        while ( m_charging && chargeCheck() )
        {
            std::this_thread::sleep_for( std::chrono::milliseconds(
                static_cast< unsigned int >( m_waitTimeBetweenMeasurements * 1000 ) ) );

            // Update in a thread-safe way
            {
                std::lock_guard< std::mutex > lock( m_mutex );
                measureAndUpdateChargeMembers();
                setCurrent( m_socChargeCurrent.at( m_soc ) );
            }
        }
    }

    void BatteryCharger::setChargeParams( volt a_voltageMax,
                                          volt a_voltageMin,
                                          volt a_voltageNominal,
                                          volt a_voltageChargeCutOff,
                                          ah a_capacity,
                                          ampere a_currentMax,
                                          ampere a_currentChargeCutOff,
                                          std::map< unsigned int, volt > a_socVoltage,
                                          std::map< unsigned int, ampere > a_socChargeCurrent,
                                          second a_waitTimeForBatteryVoltageMeasurements,
                                          second a_baseTimeBetweenMeasurements )
    {
        //  Set members
        m_voltageMax = a_voltageMax;
        m_voltageMin = a_voltageMin;
        m_voltageNominal = a_voltageNominal;
        m_voltageChargeCutOff = a_voltageChargeCutOff;
        m_capacity = a_capacity;
        m_currentMax = a_currentMax;
        m_currentChargeCutOff = a_currentChargeCutOff;
        m_socVoltage = a_socVoltage;
        m_socChargeCurrent = a_socChargeCurrent;
        m_waitTimeForBatteryVoltageMeasurements = a_waitTimeForBatteryVoltageMeasurements;
        m_baseTimeBetweenMeasurements = a_baseTimeBetweenMeasurements;

        // Update other values
        m_batteryParamsSet = true;
    }

    auto BatteryCharger::batteryParamsValid() -> bool
    {
        bool relations = ( m_voltageMax > m_voltageMin && m_voltageMax >= m_voltageChargeCutOff
                           && m_currentChargeCutOff <= m_currentMax );
        bool positive = ( m_voltageMax >= 0 && m_voltageMin >= 0 && m_voltageNominal >= 0
                          && m_voltageChargeCutOff >= 0 && m_capacity >= 0 && m_currentMax >= 0
                          && m_currentChargeCutOff >= 0 );
        return ( relations && positive );
    }

    void BatteryCharger::turnOffOutput()
    {
        m_psu.turnOutputOff();
    }

    void BatteryCharger::turnOnOutput()
    {
        m_psu.turnOutputOn();
    }

    auto BatteryCharger::getSetVoltage() -> volt
    {
        m_setVoltage = m_psu.getSetVoltage();
        return m_setVoltage;
    }

    auto BatteryCharger::getSetCurrent() -> ampere
    {
        m_setCurrent = m_psu.getSetCurrent();
        return m_setCurrent;
    }

    auto BatteryCharger::batteryVoltagesValid() -> bool
    {
        measureBatteryVoltage();
        return ( m_batteryVoltage > m_voltageMin && m_batteryVoltage < m_voltageMax );
    }

    // TODO: move these methods to the upper level
    // void BatteryCharger::setChargeParams( std::filesystem::path a_yamlFile )
    // {
    //     YAML::Node chargeParams = YAML::LoadFile( a_yamlFile );

    // }

    // void BatteryCharger::setBatteryParams( std::filesystem::path a_yamlFile ) {
    //     YAML::Node batteryParams = YAML::LoadFile( a_yamlFile );
    // }

} // namespace psu::bc
