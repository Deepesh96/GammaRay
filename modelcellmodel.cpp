#include "modelcellmodel.h"
#include "util.h"

#include <qvector.h>

using namespace Endoscope;

ModelCellModel::ModelCellModel(QObject* parent): QAbstractTableModel(parent)
{
}

void ModelCellModel::setModelIndex(const QModelIndex& index)
{
  beginResetModel();
  m_index = index;
  endResetModel();
}

QVariant ModelCellModel::data(const QModelIndex& index, int role) const
{
  if ( !index.isValid() )
    return QVariant();

  const QVariant value = m_index.data( static_cast<Qt::ItemDataRole>( index.row() ) );
  if ( role == Qt::DisplayRole ) {
    switch( index.column() ) {
      case 0:
      {
        static QVector<QString> itemDataRoleNames = QVector<QString>()
          << "Qt::DisplayRole"
          << "Qt::DecorationRole"
          << "Qt::EditRole"
          << "Qt::ToolTipRole"
          << "Qt::StatusTipRole"
          << "Qt::WhatsThisRole"
          << "Qt::FontRole"
          << "Qt::TextAlignmentRole"
          << "Qt::BackgroundRole"
          << "Qt::ForegroundRole"
          << "Qt::CheckStateRole"
          << "Qt::AccessibleTextRole"
          << "Qt::AccessibleDescriptionRole"
          << "Qt::SizeHintRole";

        Q_ASSERT( index.row() < itemDataRoleNames.size() );
        return itemDataRoleNames.at( index.row() );
      }  
      case 1: return Util::variantToString( value );
      case 2: return value.typeName();
    }
  } else if ( role == Qt::EditRole ) {
    if ( index.column() == 1 )
      return value;
  }

  return QVariant();
}

int ModelCellModel::columnCount(const QModelIndex& parent) const
{
  if ( parent.isValid() )
    return 0;
  return 3;
}

int ModelCellModel::rowCount(const QModelIndex& parent) const
{
  if ( parent.isValid() || !m_index.isValid() )
    return 0;
  return 14;
}

QVariant ModelCellModel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if ( role == Qt::DisplayRole && orientation == Qt::Horizontal ) {
    switch ( section ) {
      case 0: return tr( "Role" );
      case 1: return tr( "Value" );
      case 2: return tr( "Type" );
    }
  }
  return QAbstractItemModel::headerData(section, orientation, role);
}

#include "modelcellmodel.moc"
