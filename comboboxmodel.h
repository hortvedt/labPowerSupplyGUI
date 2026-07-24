#pragma once

#include <QAbstractListModel>
#include <QPair>
#include <QVector>

// AI written base

namespace psu::mmi
{
    class ComboBoxModel : public QAbstractListModel
    {
        Q_OBJECT
        Q_PROPERTY(
            int currentIndex READ currentIndex WRITE setCurrentIndex NOTIFY currentIndexChanged )
        Q_PROPERTY( int currentValue READ currentValue NOTIFY currentValueChanged )
        Q_PROPERTY( QString currentText READ currentText NOTIFY currentTextChanged )

    public:
        enum Roles
        {
            TextRole = Qt::UserRole + 1,
            ValueRole
        };

        explicit ComboBoxModel( QObject *parent = nullptr );

        // Basic QAbstractListModel functions
        int rowCount( const QModelIndex &parent = QModelIndex() ) const override;
        QVariant data( const QModelIndex &index, int role = Qt::DisplayRole ) const override;
        QHash< int, QByteArray > roleNames() const override;

        // Add an item (string, value)
        Q_INVOKABLE void addItem( const QString &text, int value );
        Q_INVOKABLE void clear();

        // Getters/Setters
        int currentIndex() const { return m_currentIndex; }
        void setCurrentIndex( int index );

        int currentValue() const;
        QString currentText() const;

    signals:
        void currentIndexChanged();
        void currentValueChanged();
        void currentTextChanged();

    private:
        QVector< QPair< QString, int > > m_items;
        int m_currentIndex;
    };

} // namespace psu::mmi
