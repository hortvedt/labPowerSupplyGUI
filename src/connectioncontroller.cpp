#include <connectioncontroller.h>

namespace
{

    void populateBytesize( psu::mmi::ComboBoxModel &a_comboBox )
    {
        a_comboBox.addItem( "5", serial_cpp::bytesize_t::fivebits );
        a_comboBox.addItem( "6", serial_cpp::bytesize_t::sixbits );
        a_comboBox.addItem( "7", serial_cpp::bytesize_t::sevenbits );
        a_comboBox.addItem( "8", serial_cpp::bytesize_t::eightbits );

        a_comboBox.setCurrentIndex(
            3 ); // Debug Petter: This does not work. Setting defaults is not working. Maybe use some qt index magic.
    }

    void populateParity( psu::mmi::ComboBoxModel &a_comboBox )
    {
        a_comboBox.addItem( "None", serial_cpp::parity_t::parity_none );
        a_comboBox.addItem( "Even", serial_cpp::parity_t::parity_even );
        a_comboBox.addItem( "Odd", serial_cpp::parity_t::parity_odd );
        a_comboBox.addItem( "Space", serial_cpp::parity_t::parity_space );
        a_comboBox.addItem( "Mark", serial_cpp::parity_t::parity_mark );

        a_comboBox.setCurrentIndex( 0 );
    }

    void populateStopbits( psu::mmi::ComboBoxModel &a_comboBox )
    {
        a_comboBox.addItem( "1", serial_cpp::stopbits_t::stopbits_one );
        a_comboBox.addItem( "1.5", serial_cpp::stopbits_t::stopbits_one_point_five );
        a_comboBox.addItem( "2", serial_cpp::stopbits_t::stopbits_two );

        a_comboBox.setCurrentIndex( 0 );
    }

    void populateFlowcontrol( psu::mmi::ComboBoxModel &a_comboBox )
    {
        a_comboBox.addItem( "None", serial_cpp::flowcontrol_t::flowcontrol_none );
        a_comboBox.addItem( "Software", serial_cpp::flowcontrol_t::flowcontrol_software );
        a_comboBox.addItem( "Hardware", serial_cpp::flowcontrol_t::flowcontrol_hardware );

        a_comboBox.setCurrentIndex( 0 );
    }

} // namespace

namespace psu::mmi
{
    ConnectionController::ConnectionController( Psu *a_psu, QObject *parent )
        : QObject { parent }
        , m_psu { a_psu }
    {
        populateBytesize( m_bytesizeCombo );
        populateParity( m_parityCombo );
        populateStopbits( m_stopbitsCombo );
        populateFlowcontrol( m_flowcontrolCombo );
    }

    void ConnectionController::setSerial( const std::string &a_port,
                                          serial_cpp::Timeout &a_timeOut,
                                          unsigned int a_baudrate,
                                          second a_serialWaitTime,
                                          serial_cpp::bytesize_t a_bytesize,
                                          serial_cpp::parity_t a_parity,
                                          serial_cpp::stopbits_t a_stopbits,
                                          serial_cpp::flowcontrol_t a_flowcontrol )
    {
        m_serial.setPort( a_port );
        m_serial.setBaudrate( a_baudrate );
        m_serial.setTimeout( a_timeOut );
        m_serial.setBytesize( a_bytesize );
        m_serial.setParity( a_parity );
        m_serial.setStopbits( a_stopbits );
        m_serial.setFlowcontrol( a_flowcontrol );

        m_psu->setSerial( &m_serial, a_serialWaitTime );
    }

    void ConnectionController::setSerial()
    {
        setSerial( m_port,
                   m_timeOut,
                   m_baudrate,
                   m_serialWaitTime,
                   m_bytesize,
                   m_parity,
                   m_stopbits,
                   m_flowcontrol );
    }

    void ConnectionController::updateSerialSettings()
    {
        serial_cpp::bytesize_t bytesize = getSelectedBytesize();
        serial_cpp::parity_t parity = getSelectedParity();
        serial_cpp::stopbits_t stopbits = getSelectedStopbits();
        serial_cpp::flowcontrol_t flowcontrol = getSelectedFlowcontrol();

        m_bytesize = bytesize;
        m_parity = parity;
        m_stopbits = stopbits;
        m_flowcontrol = flowcontrol;

        m_port = m_qStringPort.toStdString();
        m_timeOut = serial_cpp::Timeout::simpleTimeout( m_timeOutTime );
    }

    auto ConnectionController::connectToPsu() -> bool
    {
        if ( not m_psu->serialOpen() )
        {
            m_psu->openSerial();
        }

        std::string &identification = m_psu->getIdentification();
        return not identification.empty();
    }

    void ConnectionController::connectToSerial()
    {
        updateSerialSettings();
        setSerial();

        m_connectedToSerial = true;
        emit connectedToSerialChanged();
    }

    auto ConnectionController::bytesizeCombo() -> ComboBoxModel *
    {
        return &m_bytesizeCombo;
    }

    auto ConnectionController::parityCombo() -> ComboBoxModel *
    {
        return &m_parityCombo;
    }

    auto ConnectionController::stopbitsCombo() -> ComboBoxModel *
    {
        return &m_stopbitsCombo;
    }

    auto ConnectionController::flowcontrolCombo() -> ComboBoxModel *
    {
        return &m_flowcontrolCombo;
    }

    auto ConnectionController::getSelectedBytesize() const -> serial_cpp::bytesize_t
    {
        QVariant value = m_bytesizeCombo.currentValue();
        if ( value.isValid() && value.canConvert< int >() )
        {
            return static_cast< serial_cpp::bytesize_t >( value.toInt() );
        }
        return serial_cpp::eightbits;
    }

    auto ConnectionController::getSelectedParity() const -> serial_cpp::parity_t
    {
        QVariant value = m_parityCombo.currentValue();
        if ( value.isValid() && value.canConvert< int >() )
        {
            return static_cast< serial_cpp::parity_t >( value.toInt() );
        }
        return serial_cpp::parity_none;
    }

    auto ConnectionController::getSelectedStopbits() const -> serial_cpp::stopbits_t
    {
        QVariant value = m_stopbitsCombo.currentValue();
        if ( value.isValid() && value.canConvert< int >() )
        {
            return static_cast< serial_cpp::stopbits_t >( value.toInt() );
        }
        return serial_cpp::stopbits_one;
    }

    auto ConnectionController::getSelectedFlowcontrol() const -> serial_cpp::flowcontrol_t
    {
        QVariant value = m_flowcontrolCombo.currentValue();
        if ( value.isValid() && value.canConvert< int >() )
        {
            return static_cast< serial_cpp::flowcontrol_t >( value.toInt() );
        }
        return serial_cpp::flowcontrol_none;
    }

    auto ConnectionController::connectedToSerial() -> bool
    {
        return m_connectedToSerial;
    }

    auto ConnectionController::connectedToPsu() -> bool
    {
        return m_connectedToPsu;
    }

} // namespace psu::mmi
