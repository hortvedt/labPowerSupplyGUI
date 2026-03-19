#pragma once

// #include <chrono>
#include <filesystem>
#include <map>
#include <psu.h>
#include <unitdefinitions.h>
#include <utils.h>

namespace psu::bc
{
    // The python class is more of a cli so some thing will be natural to take out
    class BatteryCharger
    {
    public:
        explicit BatteryCharger( Psu& a_psu );

        void startSerial();
        void settings();
        void unsafeCharge();
        void charge();
        // void updateHistory(); // update_data
        auto chargeCheck() -> bool;
        void measureAndUpdateChargeMembers(); // Charge_update
        void chargeSetupHighLevel();
        void chargeSetupLowLevel();
        auto readyBeforeCharge() -> bool;
        // void makeCurrentParams(); // Now take in current params
        auto measureBatteryVoltage() -> volt; // checkVoltage
        void setVoltage( volt a_voltage );   // vset
        void setCurrent( ampere a_current ); // iset
        void end();
        auto readVoltage() -> volt;
        auto readCurrent() -> ampere;
        void startCharging();
        void endCharging();
        void chargeLoop();

        void resetCharging();
        void setChargeParams( volt a_voltageMax,
                              volt a_voltageMin,
                              volt a_voltageNominal,
                              volt a_voltageChargeCutOff,
                              ah a_capacity,
                              ampere a_currentMax,
                              ampere a_currentChargeCutOff,
                              std::map< unsigned int, volt > a_socVoltage,
                              std::map< unsigned int, ampere > a_socChargeCurrent,
                              second a_waitTimeForBatteryVoltageMeasurements,
                              second a_baseTimeBetweenMeasurements );
        auto batteryParamsValid() -> bool;
        void turnOffOutput();
        void turnOnOutput();
        // TODO: move these methods to the upper level
        // void setChargeParams( std::filesystem::path a_yamlFile );
        // void setBatteryParams( std::filesystem::path a_yamlFile );

    private: // methods
        auto getSetVoltage() -> volt;
        auto getSetCurrent() -> ampere;
        auto batteryVoltagesValid() -> bool;

    private: // members
        Psu& m_psu;

        volt m_setVoltage;
        ampere m_setCurrent;
        volt m_batteryVoltage;
        volt m_voltage;
        ampere m_current;

        unsigned int m_soc; // State Of Charge
        second m_waitTimeBetweenMeasurements;
        bool m_verbose { true }; // TODO: Add the verbose part
        bool m_batteryParamsSet { false };

        // Charge params
        // Trying to remove what is not a core part and the first two are not
        // std::string m_port; // Not necessary any more
        // std::string m_battery; // Not this ether
        // ah m_capacity; // Duplicate from battery params
        std::filesystem::path m_csvFile; // Dont think i want this functionality here

        // Battery params
        volt m_voltageMax;
        volt m_voltageMin;
        volt m_voltageNominal;
        volt m_voltageChargeCutOff;
        ah m_capacity; // In use for waitTimeBetweenMeasurements
        // The values in the yaml are in  capacity, but I think I only need those values one layer up.
        ampere m_currentMax; // A safety to
        // ampere m_currentMin; // Is this necessary?
        ampere m_currentChargeCutOff;
        second m_waitTimeForBatteryVoltageMeasurements; // New C++ possible value 0.5
        second m_baseTimeBetweenMeasurements;           // New C++ possible value 120

        std::map< unsigned int, volt > m_socVoltage;
        std::map< unsigned int, ampere > m_socChargeCurrent; // This is in ampere, yaml is in C-rate

        // Plotting and logging. Not sure I want this in this class. Maybe just a outside call to get all the values and do it outside.
        // bool logging { true };
        // std::vector< std::chrono::time_point< std::chrono::system_clock > > m_timeHistory;
        // std::vector< volt > m_voltageHistory;
        // std::vector< ampere > m_currentHistory;
        // std::vector< volt > m_batteryVoltageHistory;
    };
} // namespace psu::bc
