#ifndef CCS_MYLISTMODEL_H
#define CCS_MYLISTMODEL_H
#include <QObject>
#include <QAbstractListModel>

class MyListModel : public QAbstractListModel
{
	Q_OBJECT
public:
	explicit MyListModel(QObject* parent = nullptr);
	int rowCount(const QModelIndex& parent = QModelIndex())const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole)const override;
	void setData(const QStringList& value);
	void addData(const QString& value);
	void deleteData(const QModelIndex& index);
	bool isVaild(const QModelIndex& index);
	QString getRowData(const QModelIndex& index);
	QStringList getData()const;

private:
	QStringList modelData;
};

#endif
