#include "mylistmodel.h"
#include <QColor>

MyListModel::MyListModel(QObject* parent)
	:QAbstractListModel(parent)
{ }

int MyListModel::rowCount(const QModelIndex& parent) const
{
	return modelData.size();
}

QVariant MyListModel::data(const QModelIndex& index, int role) const
{
	if ( !index.isValid() || index.row() > modelData.size() )
	{
		return QVariant();
	}
	if ( role == Qt::ToolTipRole || role == Qt::DisplayRole )
		return modelData.at(index.row());
	return QVariant();
}

void MyListModel::setData(const QStringList& value)
{
	beginResetModel();
	modelData = std::move(value);
	endResetModel();
}

void MyListModel::addData(const QString& value)
{
	beginResetModel();
	modelData.append(std::move(value));
	endResetModel();
}

void MyListModel::deleteData(const QModelIndex& index)
{
	beginResetModel();
	modelData.removeAt(index.row());
	endResetModel();
}

bool MyListModel::isVaild(const QModelIndex& index)
{
	if ( !index.isValid() || index.row() > modelData.size() )
	{
		return false;
	}
	return true;
}

QString MyListModel::getRowData(const QModelIndex& index)
{
	return modelData[index.row()];
}

QStringList MyListModel::getData() const
{
	return modelData;
}