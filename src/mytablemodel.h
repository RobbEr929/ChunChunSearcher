#ifndef CCS_MYTABLEMODEL_H
#define CCS_MYTABLEMODEL_H
#include "global.h"
#include <QObject>
#include <QAbstractTableModel>

using namespace ccs;

struct ModelItem
{
	QString name;
	QString path;
};

class MyTableModel : public QAbstractTableModel
{
	Q_OBJECT

public:
	explicit MyTableModel(QObject* parent = nullptr);
	int rowCount(const QModelIndex& parent = QModelIndex())const override;
	int columnCount(const QModelIndex& parent = QModelIndex())const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole)const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
	void addData(ModelItem& data);
	void setData(QList<ModelItem>& data);
	void deleteData(const QModelIndex& index);
	void updateData(const QModelIndex& index, ModelItem& it);
	void setHeader(QStringList& header);
	bool isVaild(const QModelIndex& index);
	ModelItem getRowData(const QModelIndex& index)const;
	QList<ModelItem> getData()const;
	QString Name(const QModelIndex& index);
	QString Path(const QModelIndex& index);
	QString FullPath(const QModelIndex& index);
	void sort(int column, Qt::SortOrder order = Qt::AscendingOrder);
	~MyTableModel() override;

private:
	bool lessThan(QString& left, QString& right);
	QList<ModelItem> modelData;
	QStringList horizontalHead;

public slots:
	void rowDoubleClicked(const QModelIndex& index);
};
#endif
