#include <applicationcontroller.h>

namespace psu::mmi
{
    ApplicationController::ApplicationController( Psu *a_psu, QObject *parent )
        : QObject { parent }
        , m_psu { a_psu }
    {
    }
} // namespace psu::mmi
