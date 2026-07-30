#include <comboboxmodel.h>

namespace psu::mmi
{

    ComboBoxModel::ComboBoxModel( QObject *parent )
        : QAbstractListModel( parent )
        , m_currentIndex( -1 )
    {
    }

    int ComboBoxModel::rowCount( const QModelIndex &parent ) const
    {
        Q_UNUSED( parent )
        return m_items.size();
    }

    QVariant ComboBoxModel::data( const QModelIndex &index, int role ) const
    {
        if ( !index.isValid() || index.row() >= m_items.size() )
            return QVariant();

        const auto &item = m_items [ index.row() ];

        switch ( role )
        {
        case Qt::DisplayRole:
            [[fallthrough]];
        case TextRole:
            return item.first;
        case ValueRole:
            return item.second;
        default:
            return QVariant();
        }
    }

    QHash< int, QByteArray > ComboBoxModel::roleNames() const
    {
        QHash< int, QByteArray > roles;
        roles [ TextRole ] = "TextRole";
        roles [ Qt::DisplayRole ] = "DisplayRole";
        roles [ ValueRole ] = "ValueRole";
        return roles;
    }

    void ComboBoxModel::addItem( const QString &text, const QVariant &value )
    {
        beginInsertRows( QModelIndex(), m_items.size(), m_items.size() );
        m_items.append( qMakePair( text, value ) );
        endInsertRows();
    }

    // Convenience overloads for common types
    void ComboBoxModel::addItem( const QString &text, int value )
    {
        addItem( text, QVariant( value ) );
    }

    void ComboBoxModel::addItem( const QString &text, double value )
    {
        addItem( text, QVariant( value ) );
    }

    void ComboBoxModel::addItem( const QString &text, const QString &value )
    {
        addItem( text, QVariant( value ) );
    }

    void ComboBoxModel::addItem( const QString &text, bool value )
    {
        addItem( text, QVariant( value ) );
    }

    void ComboBoxModel::clear()
    {
        beginResetModel();
        m_items.clear();
        m_currentIndex = -1;
        endResetModel();
        emit currentIndexChanged();
        emit currentValueChanged();
        emit currentTextChanged();
    }

    void ComboBoxModel::setCurrentIndex( int index )
    {
        if ( m_currentIndex == index )
            return;

        if ( index < -1 || index >= m_items.size() )
            return;

        m_currentIndex = index;
        emit currentIndexChanged();
        emit currentValueChanged();
        emit currentTextChanged();
    }

    QVariant ComboBoxModel::currentValue() const
    {
        if ( m_currentIndex >= 0 && m_currentIndex < m_items.size() )
            return m_items [ m_currentIndex ].second;
        return QVariant();
    }

    QString ComboBoxModel::currentText() const
    {
        if ( m_currentIndex >= 0 && m_currentIndex < m_items.size() )
            return m_items [ m_currentIndex ].first;
        return QString();
    }

    // Convenience methods to get value as specific types
    int ComboBoxModel::currentValueAsInt() const
    {
        QVariant value = currentValue();
        if ( value.canConvert< int >() )
            return value.toInt();
        return 0;
    }

    QString ComboBoxModel::currentValueAsString() const
    {
        QVariant value = currentValue();
        if ( value.canConvert< QString >() )
            return value.toString();
        return QString();
    }

    double ComboBoxModel::currentValueAsDouble() const
    {
        QVariant value = currentValue();
        if ( value.canConvert< double >() )
            return value.toDouble();
        return 0.0;
    }

    bool ComboBoxModel::currentValueAsBool() const
    {
        QVariant value = currentValue();
        if ( value.canConvert< bool >() )
            return value.toBool();
        return false;
    }

} // namespace psu::mmi