#pragma once

#include <QObject>
#include <comboboxmodel.h>
#include <psu.h>
#include <qqmlintegration.h>

namespace psu::mmi
{

    class ApplicationController : public QObject
    {
        Q_OBJECT
        QML_ELEMENT
        QML_UNCREATABLE( "" )

    public:
        enum struct Tabs
        {
            Connect = 0,
            Standard,
            CSV,
            BatteryCharger,
            FreeSerial
        };
        Q_ENUM( Tabs )

        explicit ApplicationController( Psu* a_psu, QObject* parent = nullptr );

    signals:

    private:
        psu::Psu* m_psu { nullptr };
    };
} // namespace psu::mmi
