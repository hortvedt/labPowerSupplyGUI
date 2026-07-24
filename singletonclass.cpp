#include <singletonclass.h>

namespace psu::mmi
{

    SingletonClass::SingletonClass( QObject *parent )
        : QObject { parent }
        , m_psu { new Psu() }
        , m_psuController { new PsuController( m_psu, this ) }
        , m_bcController { new BcController( m_psu, this ) }
        , m_csvController { new CsvController( m_psu, this ) }
    {
    }

    void SingletonClass::setSerial( const std::string &a_port,
                                    unsigned int a_baudrate,
                                    second a_serialWaitTime,
                                    serial_cpp::Timeout a_timeOut,
                                    serial_cpp::bytesize_t a_bytesize,
                                    serial_cpp::parity_t a_parity,
                                    serial_cpp::stopbits_t a_stopbits,
                                    serial_cpp::flowcontrol_t a_flowcontrol )
    {
        if ( m_serial != nullptr )
        {
            delete m_serial;
        }

        m_serial = new serial_cpp::Serial( a_port,
                                           a_baudrate,
                                           a_timeOut,
                                           a_bytesize,
                                           a_parity,
                                           a_stopbits,
                                           a_flowcontrol );

        m_psu->setSerial( m_serial, a_serialWaitTime );
    }

} // namespace psu::mmi
