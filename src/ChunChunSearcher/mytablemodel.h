#ifndef CCS_MYTABLEMODEL_H
#define CCS_MYTABLEMODEL_H
#include "global.h"
#include <QObject>
#include <QAbstractTableModel>
#include <QStringList>
using namespace ccs;

class MyTableModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	explicit MyTableModel(QObject* parent = nullptr);
	int rowCount(const QModelIndex& parent = QModelIndex())const override;
	int columnCount(const QModelIndex& parent = QModelIndex())const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole)const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
	void addData(QStringList& data);
	void setData(QList<QStringList>& data);
	void deleteData(const QModelIndex& index);
	void updateData(const QModelIndex& index, QStringList& it);
	void clear();
	void setHeader(QStringList& header);
	bool isVaild(const QModelIndex& index);
	QStringList getRowData(const QModelIndex& index)const;
	QList<QStringList> getData()const;
	QString Name(const QModelIndex& index);
	QString Path(const QModelIndex& index);
	QString FullPath(const QModelIndex& index);
	void sort(int column, Qt::SortOrder order = Qt::AscendingOrder);
	~MyTableModel() override;

private:
	bool lessThan(QString& left, QString& right);
	QList<QStringList> modelData;
	QStringList horizontalHead;

public slots:
	void rowDoubleClicked(const QModelIndex& index);
};
#endif
