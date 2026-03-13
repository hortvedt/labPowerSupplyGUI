#pragma once

#include <chrono>
#include <filesystem>
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
        void updateHistory(); // update_data
        void chargeCheck();
        void chargeUpdate();
        void chargeSetupHighLevel();
        void chargeSetupLowLevel();
        auto readyBeforeCharge() -> bool;
        void makeCurrentParams();
        auto readBatteryVoltage() -> volt; // checkVoltage
        void setVoltage();                 // vset
        void setCurrent();                 // iset
        void end();

        void setChargeParams( std::filesystem::path a_yamlFile );
        void setBatteryParams( std::filesystem::path a_yamlFile );

    private: // methods
    private: // members
        Psu& m_psu;

        volt m_voltage { 0 };
        ampere m_current { 0 };
        volt m_batteryVoltage { 0 };

        unsigned int m_soc { 0 }; // State Of Charge

        // Plotting and logging
        bool logging { true };
        std::vector< std::chrono::time_point< std::chrono::system_clock > > m_timeHistory;
        std::vector< volt > m_voltageHistory;
        std::vector< ampere > m_currentHistory;
        std::vector< volt > m_batteryVoltageHistory;
    };
} // namespace psu::bc
