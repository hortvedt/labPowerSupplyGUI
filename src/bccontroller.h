#pragma once

#include <QObject>

#include <batterycharger.h>
#include <psu.h>
#include <qqmlintegration.h>

namespace psu::mmi
{

        class BcController : public QObject
        {
            Q_OBJECT
            QML_ELEMENT
            QML_UNCREATABLE( "" )
        public:
            explicit BcController( Psu* a_psu,
                                   QObject* a_parent = nullptr ); // Needs to take a batteryCharger

        signals:

        private:
            Psu* m_psu { nullptr };
            BatteryCharger* m_batteryCharger;
        };

} // namespace psu
