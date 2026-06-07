#include <psucontroller.h>

namespace psu::mmi
{

    PsuController::PsuController( Psu* a_psu, QObject* parent )
        : QObject { parent }
        , m_psu { a_psu }
    {
    }

    volt PsuController::voltage()
    {
        return m_voltage;
    }

    ampere PsuController::current()
    {
        return m_current;
    }

    bool PsuController::serialOpen()
    {
        return m_serialOpen;
    }

    bool PsuController::currentLimited()
    {
        return m_currentLimited;
    }

    bool PsuController::voltageLimited()
    {
        return m_voltageLimited;
    }

    bool PsuController::outputOn()
    {
        return m_outputOn;
    }

    volt PsuController::setVoltage()
    {
        return m_setVoltage;
    }

    ampere PsuController::setCurrent()
    {
        return m_setCurrent;
    }

    QString PsuController::identification()
    {
        return m_identification;
    }

    bool PsuController::isSerialSet()
    {
        m_serialSet = m_psu->isSerialSet();
        return m_serialSet;
    }

    // void PsuController::setPsu( Psu *a_psu )
    // {
    //     m_psu = a_psu;
    //     m_psuSet = true;
    // }

    void PsuController::getAllValues()
    {
        // Status
        if ( m_serialSet )
        {
            m_serialOpen = m_psu->serialOpen();
            if ( m_serialOpen )
            {
                m_identification = QString::fromStdString( m_psu->getIdentification() );

                m_setVoltage = m_psu->getSetVoltage();
                m_setCurrent = m_psu->getSetCurrent();

                m_psu->updateStatus();
                m_currentLimited = m_psu->getCurrentLimited();
                m_voltageLimited = m_psu->getVoltageLimited();
                m_outputOn = m_psu->getoutputOn();

                if ( m_outputOn )
                {
                    m_voltage = m_psu->voltage();
                    m_current = m_psu->current();
                }
                else
                {
                    outputOffReset();
                }
            }
            else
            {
                resetAllValues();
            }
        }
    }

    void PsuController::resetAllValues()
    {
        m_identification.clear();

        m_setVoltage = 0;
        m_setCurrent = 0;

        m_currentLimited = false;
        m_voltageLimited = false;
        m_outputOn = false;

        outputOffReset();
    }

    void PsuController::outputOffReset()
    {
        m_voltage = 0;
        m_current = 0;
    }

} // namespace psu
