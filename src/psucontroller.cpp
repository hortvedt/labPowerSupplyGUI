#include <psucontroller.h>

#include <qdebug.h>
#include <utils.h>

namespace psu::mmi
{

    PsuController::PsuController( Psu* a_psu, QObject* parent )
        : QObject { parent }
        , m_psu { a_psu }
    {
    }

    auto PsuController::voltage() -> volt
    {
        return m_voltage;
    }

    auto PsuController::voltageString() -> QString
    {
        return QString::fromStdString( utils::voltageToFixedWidthString( m_voltage ) );
    }

    auto PsuController::current() -> ampere
    {
        return m_current;
    }

    auto PsuController::currentString() -> QString
    {
        return QString::fromStdString( utils::currentToFixedWidthString( m_current ) );
    }

    auto PsuController::serialOpen() -> bool
    {
        return m_serialOpen;
    }

    auto PsuController::currentLimited() -> bool
    {
        return m_currentLimited;
    }

    auto PsuController::voltageLimited() -> bool
    {
        return m_voltageLimited;
    }

    auto PsuController::outputOn() -> bool
    {
        return m_outputOn;
    }

    auto PsuController::valueOfSetVoltage() -> volt
    {
        return m_setVoltage;
    }

    auto PsuController::valueOfSetVoltageString() -> QString
    {
        return QString::fromStdString( utils::voltageToFixedWidthString( m_setVoltage ) );
    }

    auto PsuController::valueOfSetCurrent() -> ampere
    {
        return m_setCurrent;
    }

    auto PsuController::valueOfSetCurrentString() -> QString
    {
        return QString::fromStdString( utils::currentToFixedWidthString( m_setCurrent ) );
    }

    auto PsuController::identification() -> QString
    {
        return m_identification;
    }

    auto PsuController::connectedToPsu() -> bool
    {
        if ( m_serialSet )
        {
        }
        return true;
    }

    void PsuController::updateContinuallyChangingData()
    {
        if ( m_serialSet )
        {
            updateStatus();
            updateVoltage();
            updateCurrent();
        }
    }

    void PsuController::updateSetState()
    {
        if ( m_serialSet )
        {
            updateSerialOpen();
            updateSetVoltage();
            updateSetCurrent();
        }
    }

    void PsuController::updateIdentification()
    {
        std::string newIdentification = m_psu->getIdentification();
        if ( m_identification != newIdentification )
        {
            m_identification = QString::fromStdString( newIdentification );
            emit identificationChanged();
        }
    }

    bool PsuController::isSerialSet()
    {
        m_serialSet = m_psu->isSerialSet();
        return m_serialSet;
    }

    auto PsuController::tempDifferentFromSetVoltage() -> bool
    {
        return m_tempDifferentFromSetVoltage;
    }

    auto PsuController::tempDifferentFromSetCurrent() -> bool
    {
        return m_tempDifferentFromSetCurrent;
    }

    void PsuController::setTempVoltage( volt a_voltage )
    {
        bool valueDifferent = std::abs( m_setVoltage - a_voltage ) > m_epsilon;
        if ( valueDifferent != m_tempDifferentFromSetVoltage )
        {
            m_tempDifferentFromSetVoltage = valueDifferent;
            emit tempDifferentFromSetVoltageChanged();
        }
    }

    void PsuController::setTempCurrent( volt a_current )
    {
        bool valueDifferent = std::abs( m_setCurrent - a_current ) > m_epsilon;
        if ( valueDifferent != m_tempDifferentFromSetCurrent )
        {
            m_tempDifferentFromSetCurrent = valueDifferent;
            emit tempDifferentFromSetCurrentChanged();
        }
    }

    void PsuController::setVoltage( volt a_voltage )
    {
        m_psu->setVoltage( a_voltage );
    }

    void PsuController::setCurrent( ampere a_current )
    {
        m_psu->setCurrent( a_current );
    }

    // void PsuController::setPsu( Psu *a_psu )
    // {
    //     m_psu = a_psu;
    //     m_psuSet = true;
    // }

    void PsuController::getAllValues() // TODO: Update this to something usefull or remove it.
    {
        // Status
        if ( m_serialSet )
        {
            m_serialOpen = m_psu->serialOpen();
            if ( m_serialOpen )
            {
                m_allValuesReset = false;

                m_psu->updateStatus();

                updateIdentification();
                updateSetState();
                updateContinuallyChangingData();

                // if ( m_outputOn ) // Maybe needed, but dont know
                // {
                //     m_voltage = m_psu->voltage();
                //     m_current = m_psu->current();
                // }
                // else
                // {
                //     outputOffReset();
                // }
            }
            else
            {
                resetAllValues();
            }
        }
    }

    void PsuController::resetAllValues()
    {
        m_allValuesReset = true;

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

    void PsuController::updateVoltage()
    {
        volt newVoltage = m_psu->voltage();
        if ( m_voltage != newVoltage )
        {
            m_voltage = newVoltage;
            emit voltageChanged();
        }
    }

    void PsuController::updateCurrent()
    {
        ampere newCurrent = m_psu->current();
        if ( m_current != newCurrent )
        {
            m_current = newCurrent;
            emit currentChanged();
        }
    }

    void PsuController::updateStatus()
    {
        m_psu->updateStatus();

        bool newCurrentLimited = m_psu->getCurrentLimited();
        if ( m_currentLimited != newCurrentLimited )
        {
            m_currentLimited = newCurrentLimited;
            emit currentLimitedChanged();
        }

        bool newVoltageLimited = m_psu->getVoltageLimited();
        if ( m_voltageLimited != newVoltageLimited )
        {
            m_voltageLimited = newVoltageLimited;
            emit voltageLimitedChanged();
        }

        bool newOutputOn = m_psu->getOutputOn();
        if ( m_outputOn != newOutputOn )
        {
            m_outputOn = newOutputOn;
            emit outputOnChanged();
        }
    }

    void PsuController::updateSetVoltage()
    {
        volt newSetVoltage = m_psu->getSetVoltage();
        if ( m_setVoltage != newSetVoltage )
        {
            m_setVoltage = newSetVoltage;
            emit setVoltageChanged();
        }
    }

    void PsuController::updateSetCurrent()
    {
        ampere newSetCurrent = m_psu->getSetCurrent();
        if ( m_setCurrent != newSetCurrent )
        {
            m_setCurrent = newSetCurrent;
            emit setCurrentChanged();
        }
    }

    void PsuController::updateSerialOpen()
    {
        bool newSerialOpen = m_psu->serialOpen();
        if ( m_serialOpen != newSerialOpen )
        {
            m_serialOpen = newSerialOpen;
            emit serialOpenChanged();
        }
    }

} // namespace psu
