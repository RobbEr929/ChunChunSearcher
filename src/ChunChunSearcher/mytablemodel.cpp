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
	modelData = QList<QStringList>();
}

int MyTableModel::rowCount(const QModelIndex& parent) const
{
	return modelData.count();
}

int MyTableModel::columnCount(const QModelIndex& parent) const
{
	return horizontalHead.size();
}

QVariant MyTableModel::data(const QModelIndex& index, int role) const
{
	if (!index.isValid() || index.row() > modelData.count())
	{
		return QVariant();
	}
	if (role == Qt::ToolTipRole || role == Qt::DisplayRole)
	{
		return modelData[index.row()][index.column()];
	}
	return QVariant();
}

QVariant MyTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role != Qt::DisplayRole)
		return QAbstractTableModel::headerData(section, orientation, role);
	if (orientation == Qt::Horizontal)
	{
		return horizontalHead[section];
	}
	return QAbstractItemModel::headerData(section, orientation);
}

void MyTableModel::addData(QStringList& data)
{
	beginInsertRows(QModelIndex(), rowCount(), rowCount());
	modelData.push_back(std::move(data));
	endInsertRows();
}

void MyTableModel::setData(QList<QStringList>& data)
{
	beginResetModel();
	modelData = std::move(data);
	endResetModel();
}

void MyTableModel::deleteData(const QModelIndex& index)
{
	if (!isVaild(index))
	{
		return;
	}
	beginRemoveRows(QModelIndex(), index.row(), index.row());
	modelData.removeAt(index.row());
	endRemoveRows();
}

void MyTableModel::updateData(const QModelIndex& index, QStringList& it)
{
	if (!isVaild(index))
	{
		return;
	}
	beginResetModel();
	modelData[index.row()] = std::move(it);
	endResetModel();
}

void MyTableModel::clear()
{
	beginResetModel();
	modelData = QList<QStringList>();
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
	if (!index.isValid() || index.row() > modelData.count())
	{
		return false;
	}
	return true;
}

QList<QStringList> MyTableModel::getData() const
{
	return modelData;
}

QStringList MyTableModel::getRowData(const QModelIndex& index) const
{
	if (!index.isValid() || index.row() > modelData.count())
	{
		return QStringList();
	}
	else
		return modelData[index.row()];
}

QString MyTableModel::Name(const QModelIndex& index)
{
	qDebug() << "Call Name";
	if (!index.isValid() || index.row() > modelData.count())
	{
		return QString();
	}
	return modelData[index.row()][0];
}

QString MyTableModel::Path(const QModelIndex& index)
{
	qDebug() << "Call Path ";
	if (!index.isValid() || index.row() > modelData.count() || this->horizontalHead.size() < 2)
	{
		return QString();
	}
	return modelData[index.row()][1];
}

QString MyTableModel::FullPath(const QModelIndex& index)
{
	qDebug() << "Call FullPath";
	if (!index.isValid() || index.row() > modelData.count() || this->horizontalHead.size() < 2)
	{
		return QString();
	}
	if (modelData[index.row()][1].isEmpty())
		return modelData[index.row()][0];
	else
		return modelData[index.row()][1] % '\\' % modelData[index.row()][0];
}

void MyTableModel::sort(int column, Qt::SortOrder order)
{
	beginResetModel();
	if (modelData.isEmpty() || column < 0 || column >= columnCount())
		return;
	const bool asc = (order == Qt::AscendingOrder);
	std::sort(modelData.begin(), modelData.end(),
		[column, asc, this](const QStringList& left, const QStringList& right) {
			QString leftVal = left[column];
			QString rightVal = right[column];
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
	if (!index.isValid() || index.row() > modelData.count() || this->horizontalHead.size() < 2)
	{
		return;
	}
	if (modelData[index.row()][2].isEmpty())
	{
		QFileInfo fileInfo(modelData[index.row()][1]);
		if (fileInfo.exists())
		{
			QDesktopServices::openUrl(QUrl::fromLocalFile(fileInfo.absoluteFilePath()));
		}
	}
	else
	{
		QFileInfo fileInfo(modelData[index.row()][2] % '\\' % modelData[index.row()][1]);
		if (fileInfo.exists())
		{
			QDesktopServices::openUrl(QUrl::fromLocalFile(fileInfo.absoluteFilePath()));
		}
	}
}