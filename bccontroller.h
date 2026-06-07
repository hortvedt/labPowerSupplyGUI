#pragma once

#include <QObject>

namespace psu::mmi
{

        class BcController : public QObject
        {
            Q_OBJECT
        public:
            explicit BcController( QObject *parent = nullptr );

        signals:
        };

} // namespace psu
