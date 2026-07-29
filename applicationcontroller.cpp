#include <applicationcontroller.h>

namespace psu::mmi
{
    ApplicationController::ApplicationController( Psu *a_psu, QObject *parent )
        : QObject { parent }
        , m_psu { a_psu }
    {
    }

    void ApplicationController::changeTab( Tab a_tab ) {}

    void ApplicationController::setTab( Tab a_tab )
    {
        if ( a_tab == m_tab )
        {
            return;
        }

        m_tab = a_tab;
        emit tabChanged();
    }

    auto ApplicationController::getTab() -> ApplicationController::Tab const
    {
        return m_tab;
    }
} // namespace psu::mmi
