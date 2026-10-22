#pragma once

#include <QObject>
#include <psu.h>
#include <qqmlintegration.h>
#include <qtmetamacros.h>
#include <qtypes.h>

namespace psu::mmi
{

    class ApplicationController : public QObject
    {
        Q_OBJECT
        QML_ELEMENT
        QML_UNCREATABLE( "" )

        Q_PROPERTY( Tab tab READ getTab WRITE setTab NOTIFY tabChanged )

    public:
        enum struct Tab : quint8
        {
            Connect = 0,
            Standard,
            CSV,
            BatteryCharger,
            FreeSerial
        };
        Q_ENUM( Tab )

        explicit ApplicationController( Psu* a_psu, QObject* parent = nullptr );

    signals:
        void tabChanged();

    public slots:
        void changeTab( psu::mmi::ApplicationController::Tab a_tab );

    private:
        // methods
        void setTab( Tab a_tab );
        [[nodiscard]] auto getTab() const -> Tab;

        psu::Psu* m_psu { nullptr };

        Tab m_tab { Tab::Connect };
    };
} // namespace psu::mmi
