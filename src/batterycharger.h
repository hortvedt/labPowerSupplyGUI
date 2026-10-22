#pragma once

// #include <chrono>
#include <atomic>
#include <filesystem>
#include <map>
#include <mutex>
#include <psu.h>
#include <thread>
#include <unitdefinitions.h>

namespace psu
{

    constexpr second DEFAULT_BASE_TIME_BETWEEN_MEASUREMENTS = 120;
    constexpr second DEFAULT_WAIT_TIME_FOR_BATTERY_VOLTAGE_MEASUREMENTS = 0.5;

    // The python class is more of a cli so some thing will be natural to take out
    class BatteryCharger
    {
    public:
        explicit BatteryCharger( Psu* a_psu );

        void startCharging();
        void endCharging();
        void measureAndUpdateChargeMembers(); // Charge_update
        auto readyBeforeCharge() -> bool;
        auto measureBatteryVoltage() -> volt; // checkVoltage
        void startSerial();
        void endSerial();
        auto readVoltage() -> volt;
        auto readCurrent() -> ampere;

        void resetCharging();
        void setChargeParams( volt a_voltageMax,
                              volt a_voltageMin,
                              volt a_voltageNominal,
                              volt a_voltageChargeCutOff,
                              ah a_capacity,
                              ampere a_currentMax,
                              ampere a_currentChargeCutOff,
                              const std::map< unsigned int, volt >& a_socVoltage,
                              const std::map< unsigned int, ampere >& a_socChargeCurrent,
                              second a_waitTimeForBatteryVoltageMeasurements,
                              second a_baseTimeBetweenMeasurements );
        [[nodiscard]] auto batteryParamsValid() const -> bool;
        void turnOffOutput();
        void turnOnOutput();
        // TODO: move these methods to the upper level
        // void setChargeParams( std::filesystem::path a_yamlFile );
        // void setBatteryParams( std::filesystem::path a_yamlFile );

    private:
        // methods
        auto getSetVoltage() -> volt;
        auto getSetCurrent() -> ampere;
        auto batteryVoltagesValid() -> bool;
        void setVoltage( volt a_voltage );   // vset
        void setCurrent( ampere a_current ); // iset

        void chargingStartup();
        void mainChargeLoop();
        [[nodiscard]] auto chargeCheck() const -> bool;
        void chargingEnding();

        void unsafeCharge();

        // members
        Psu* m_psu;

        std::atomic< bool > m_charging { false };
        std::thread m_chargingThread;

        std::mutex m_mutex;

        volt m_setVoltage { 0 };
        ampere m_setCurrent { 0 };
        volt m_batteryVoltage { 0 };
        volt m_voltage { 0 };
        ampere m_current { 0 };

        unsigned int m_soc { 0 }; // State Of Charge
        second m_waitTimeBetweenMeasurements { 0 };
        bool m_verbose { true }; // TODO: Add the verbose part
        bool m_batteryParamsSet { false };

        // Charge params
        // Trying to remove what is not a core part and the first two are not
        // std::string m_port; // Not necessary any more
        // std::string m_battery; // Not this ether
        // ah m_capacity; // Duplicate from battery params
        std::filesystem::path m_csvFile; // Dont think i want this functionality here

        // Battery params
        volt m_voltageMax { 0 };
        volt m_voltageMin { 0 };
        volt m_voltageNominal { 0 };
        volt m_voltageChargeCutOff { 0 };
        ah m_capacity { 0 }; // In use for waitTimeBetweenMeasurements
        // The values in the yaml are in  capacity, but I think I only need those values one layer up.
        ampere m_currentMax { 0 }; // A safety to
        // ampere m_currentMin; // Is this necessary?
        ampere m_currentChargeCutOff { 0 };
        second m_waitTimeForBatteryVoltageMeasurements {
            DEFAULT_WAIT_TIME_FOR_BATTERY_VOLTAGE_MEASUREMENTS
        }; // New C++ possible value 0.5
        second m_baseTimeBetweenMeasurements {
            DEFAULT_BASE_TIME_BETWEEN_MEASUREMENTS
        }; // New C++ possible value 120

        std::map< unsigned int, volt > m_socVoltage;
        std::map< unsigned int, ampere > m_socChargeCurrent; // This is in ampere, yaml is in C-rate

        // Plotting and logging. Not sure I want this in this class. Maybe just a outside call to get all the values and do it outside.
        // bool logging { true };
        // std::vector< std::chrono::time_point< std::chrono::system_clock > > m_timeHistory;
        // std::vector< volt > m_voltageHistory;
        // std::vector< ampere > m_currentHistory;
        // std::vector< volt > m_batteryVoltageHistory;
    };
} // namespace psu
