#pragma once

#include <QObject>

#include <psu.h>

namespace psu::mmi
{
    class CsvController : public QObject
    {
        Q_OBJECT
    public:
        explicit CsvController( Psu* a_psu, QObject* parent = nullptr );

    signals:

    private:
        Psu* m_psu { nullptr };
    };
} // namespace psu::mmi
