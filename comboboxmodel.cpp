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
        roles [ TextRole ] = "displayText";
        roles [ ValueRole ] = "itemValue";
        return roles;
    }

    void ComboBoxModel::addItem( const QString &text, int value )
    {
        beginInsertRows( QModelIndex(), m_items.size(), m_items.size() );
        m_items.append( qMakePair( text, value ) );
        endInsertRows();
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

    int ComboBoxModel::currentValue() const
    {
        if ( m_currentIndex >= 0 && m_currentIndex < m_items.size() )
            return m_items [ m_currentIndex ].second;
        return -1;
    }

    QString ComboBoxModel::currentText() const
    {
        if ( m_currentIndex >= 0 && m_currentIndex < m_items.size() )
            return m_items [ m_currentIndex ].first;
        return QString();
    }
} // namespace psu::mmi
