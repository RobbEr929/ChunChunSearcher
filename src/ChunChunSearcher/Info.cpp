#include "info.h"

Info::Info(QLabel* label)
	: lab(label)
{ }

void Info::ShowInfo(QString str)
{
	lab->setText(str);
}