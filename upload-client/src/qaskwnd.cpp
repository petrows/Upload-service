#include "qaskwnd.h"

QAskWnd::QAskWnd(QWidget *parent) :
    QDialog(parent)
{
}

int QAskWnd::exec()
{
	QDialog::exec();

	// Now get result...

	return 0;
}
