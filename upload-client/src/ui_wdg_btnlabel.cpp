#include "ui_wdg_btnlabel.h"

#include <QMouseEvent>

ui_wdg_btnlabel::ui_wdg_btnlabel(QWidget *parent) :
    QLabel(parent)
{
	this->setCursor(Qt::PointingHandCursor);
}

void ui_wdg_btnlabel::mousePressEvent(QMouseEvent *ev)
{
	if (ev->buttons() == Qt::LeftButton)
	{
		emit this->clicked();
		ev->accept();
	}
}
