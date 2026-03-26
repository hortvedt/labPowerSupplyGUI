#pragma once

#include <QObject>
#include <psu.h>

namespace psu
{

    class PsuController : public QObject
    {
        Q_OBJECT

        Q_PROPERTY( volt voltage READ voltage NOTIFY voltageChanged FINAL );
        Q_PROPERTY( volt current READ current NOTIFY currentChanged FINAL );

    public:
        explicit PsuController( Psu a_psu, QObject *a_parent = nullptr );

        volt voltage();
        ampere current();

    signals:

    private:
        volt m_voltage;
        ampere m_current;
    };

} // namespace psu
