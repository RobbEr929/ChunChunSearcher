#include "mylineedit.h"
#include "configuration.h"
#include <QTimer>

MyLineEdit::MyLineEdit(QWidget* parent)
	:QLineEdit(parent)
{ }

void MyLineEdit::focusInEvent(QFocusEvent* event)
{
	if ( Configuration::SelectAll() )
	{
		QTimer::singleShot(0, this, SLOT(selectAll()));
	}
}

void MyLineEdit::focusOutEvent(QFocusEvent* event)
{
	deselect();
}