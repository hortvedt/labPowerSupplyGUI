#pragma once

#include <QAbstractListModel>
#include <QPair>
#include <QVariant>
#include <QVector>
#include <qqmlintegration.h>

// AI written base

namespace psu::mmi
{
    class ComboBoxModel : public QAbstractListModel
    {
        Q_OBJECT
        QML_ELEMENT

        Q_PROPERTY(
            int currentIndex READ currentIndex WRITE setCurrentIndex NOTIFY currentIndexChanged )
        Q_PROPERTY( QVariant currentValue READ currentValue NOTIFY currentValueChanged )
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

        // Add items with various value types
        Q_INVOKABLE void addItem( const QString &text, const QVariant &value );
        Q_INVOKABLE void addItem( const QString &text, int value );
        Q_INVOKABLE void addItem( const QString &text, double value );
        Q_INVOKABLE void addItem( const QString &text, const QString &value );
        Q_INVOKABLE void addItem( const QString &text, bool value );

        Q_INVOKABLE void clear();

        // Getters/Setters
        int currentIndex() const { return m_currentIndex; }
        void setCurrentIndex( int index );

        QVariant currentValue() const;
        QString currentText() const;

        // Convenience getters for specific types (Q_INVOKABLE for QML)
        Q_INVOKABLE int currentValueAsInt() const;
        Q_INVOKABLE QString currentValueAsString() const;
        Q_INVOKABLE double currentValueAsDouble() const;
        Q_INVOKABLE bool currentValueAsBool() const;

    signals:
        void currentIndexChanged();
        void currentValueChanged();
        void currentTextChanged();

    private:
        QVector< QPair< QString, QVariant > > m_items;
        int m_currentIndex;
    };

} // namespace psu::mmi