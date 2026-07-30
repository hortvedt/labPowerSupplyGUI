#pragma once

#include <QObject>

namespace psu::mmi
{

    class SerialSetupController : QObject
    {
        Q_OBJECT
    public:
        SerialSetupController( QObject* parent = nullptr );

    private:
    };

} // namespace psu::mmi
