#ifndef CCS_INFO_H
#define CCS_INFO_H
#include <QLabel>
#include <QObject>
#include <QThread>

class Info : public QObject
{
	Q_OBJECT
public:
	Info(QLabel* label);

private:
	QLabel* lab;

public slots:
	void ShowInfo(QString str);
};

#endif