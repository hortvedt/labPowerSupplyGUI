#pragma once

#include <QObject>

namespace psu
{
    namespace bc
    {

        class BcController : public QObject
        {
            Q_OBJECT
        public:
            explicit BcController( QObject *parent = nullptr );

        signals:
        };

    } // namespace bc
} // namespace psu
