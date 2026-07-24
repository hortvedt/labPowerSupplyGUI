#pragma once

#include <QObject>

namespace psu::mmi
{

    class ApplicationController : public QObject
    {
        Q_OBJECT

    public:
        explicit ApplicationController( QObject *parent = nullptr );

    signals:

    private:
        bool connectedToPsu;
    };
} // namespace psu::mmi
