#include "bccontroller.h"

namespace psu::mmi
{
    BcController::BcController( Psu *a_psu, QObject *a_parent )
        : QObject { a_parent }
        , m_psu { a_psu }
        , m_batteryCharger { new BatteryCharger( a_psu ) }
    {
    }

} // namespace psu::mmi
