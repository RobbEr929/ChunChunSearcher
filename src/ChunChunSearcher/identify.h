#ifndef CCS_IDENTIFY_H
#define CCS_IDENTIFY_H
#include "global.h"
#include "configuration.h"
#include <stdio.h>
#include <QObject>

class Identify :public QObject
{
	Q_OBJECT
public:
	Identify();
	static quint8 IdentifyBySuffix(QString& path);
};
#endif
