#pragma once

#include <QObject>

#include <batterycharger.h>
#include <psu.h>

namespace psu::mmi
{

        class BcController : public QObject
        {
            Q_OBJECT
        public:
            explicit BcController( Psu* a_psu, QObject* a_parent = nullptr );

        signals:

        private:
            Psu* m_psu { nullptr };
            BatteryCharger* m_batteryCharger;
        };

} // namespace psu
