#ifndef CCS_MYLINEEDIT_H
#define CCS_MYLINEEDIT_H
#include <QObject>
#include <QLineEdit>
class MyLineEdit : public QLineEdit
{
	Q_OBJECT
public:
	MyLineEdit(QWidget* parent = nullptr);

protected:
	void focusInEvent(QFocusEvent* event);
	void focusOutEvent(QFocusEvent* event);
};

#endif
