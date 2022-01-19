#include "mytablemodel.h"
#include <QDebug>
#include <QSize>
#include <QColor>
#include <QMessageBox>
#include <QStringBuilder>
#include <QDesktopServices>
#include <QFileInfo>
#include <QUrl>

MyTableModel::MyTableModel(QObject* parent)
	: QAbstractTableModel(parent)
{
	modelData = QList<ModelItem>();
}

int MyTableModel::rowCount(const QModelIndex& parent) const
{
	return modelData.count();
}

int MyTableModel::columnCount(const QModelIndex& parent) const
{
	return 2;
}

QVariant MyTableModel::data(const QModelIndex& index, int role) const
{
	if ( !index.isValid() || index.row() > modelData.count() )
	{
		return QVariant();
	}
	if ( role == Qt::ToolTipRole || role == Qt::DisplayRole )
	{
		switch ( index.column() )
		{
		case 0:
			return modelData[index.row()].name;
		case 1:
			return modelData[index.row()].path;
		}
	}
	return QVariant();
}

QVariant MyTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if ( role != Qt::DisplayRole )
		return QAbstractTableModel::headerData(section, orientation, role);
	if ( orientation == Qt::Horizontal )
	{
		return horizontalHead[section];
	}
	return QAbstractItemModel::headerData(section, orientation);
}

void MyTableModel::addData(ModelItem& data)
{
	beginResetModel();
	modelData.push_back(std::move(data));
	endResetModel();
}

void MyTableModel::setData(QList<ModelItem>& data)
{
	beginResetModel();
	modelData = std::move(data);
	endResetModel();
}

void MyTableModel::deleteData(const QModelIndex& index)
{
	if ( !isVaild(index) )
	{
		return;
	}
	beginResetModel();
	modelData.removeAt(index.row());
	endResetModel();
}

void MyTableModel::updateData(const QModelIndex& index, ModelItem& it)
{
	if ( !isVaild(index) )
	{
		return;
	}
	beginResetModel();
	modelData[index.row()] = std::move(it);
	endResetModel();
}

void MyTableModel::setHeader(QStringList& header)
{
	beginResetModel();
	horizontalHead = std::move(header);
	endResetModel();
}

bool MyTableModel::isVaild(const QModelIndex& index)
{
	if ( !index.isValid() || index.row() > modelData.count() )
	{
		return false;
	}
	return true;
}

QList<ModelItem> MyTableModel::getData() const
{
	return modelData;
}

ModelItem MyTableModel::getRowData(const QModelIndex& index) const
{
	if ( !index.isValid() || index.row() > modelData.count() )
	{
		return ModelItem();
	}
	else
		return modelData[index.row()];
}

QString MyTableModel::Name(const QModelIndex& index)
{
	qDebug() << "Call Name";
	if ( !index.isValid() || index.row() > modelData.count() )
	{
		return QString();
	}
	return modelData[index.row()].name;
}

QString MyTableModel::Path(const QModelIndex& index)
{
	qDebug() << "Call Path ";
	if ( !index.isValid() || index.row() > modelData.count() )
	{
		return QString();
	}
	return modelData[index.row()].path;
}

QString MyTableModel::FullPath(const QModelIndex& index)
{
	qDebug() << "Call FullPath";
	if ( !index.isValid() || index.row() > modelData.count() )
	{
		return QString();
	}
	if ( modelData[index.row()].path.isEmpty() )
		return modelData[index.row()].name;
	else
		return modelData[index.row()].path % '\\' % modelData[index.row()].name;
}

void MyTableModel::sort(int column, Qt::SortOrder order)
{
	beginResetModel();
	if ( modelData.isEmpty() || column < 0 || column >= columnCount() )
		return;
	const bool asc = ( order == Qt::AscendingOrder );
	std::sort(modelData.begin(), modelData.end(),
			  [column, asc, this](const ModelItem& left, const ModelItem& right){
		QString leftVal, rightVal;
		switch ( column )
		{
		case 0:
			leftVal = left.name;
			rightVal = right.name;
			break;
		case 1:
			leftVal = left.path;
			rightVal = right.path;
			break;
		}
		return asc
			? lessThan(leftVal, rightVal)
			: lessThan(rightVal, leftVal);
	});
	endResetModel();
}

MyTableModel::~MyTableModel()
{ }

bool MyTableModel::lessThan(QString& left, QString& right)
{
	return left.compare(right) < 0;
}

void MyTableModel::rowDoubleClicked(const QModelIndex& index)
{
	qDebug() << "Call rowDoubleClicked";
	if ( !index.isValid() || index.row() > modelData.count() )
	{
		return;
	}
	if ( modelData[index.row()].path.isEmpty() )
	{
		QFileInfo fileInfo(modelData[index.row()].name);
		if ( fileInfo.exists() )
		{
			QDesktopServices::openUrl(QUrl::fromLocalFile(fileInfo.absoluteFilePath()));
		}
	}
	else
	{
		QFileInfo fileInfo(modelData[index.row()].path % '\\' % modelData[index.row()].name);
		if ( fileInfo.exists() )
		{
			QDesktopServices::openUrl(QUrl::fromLocalFile(fileInfo.absoluteFilePath()));
		}
	}
}