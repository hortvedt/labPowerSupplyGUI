#include <csvcontroller.h>

namespace psu::mmi
{
    CsvController::CsvController( Psu* a_psu, QObject* a_parent )
        : QObject { a_parent }
        , m_psu { a_psu }
    {
    }

} // namespace psu::mmi
