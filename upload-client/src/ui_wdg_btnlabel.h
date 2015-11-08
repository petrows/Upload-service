#ifndef UI_WDG_BTNLABEL_H
#define UI_WDG_BTNLABEL_H

#include <QLabel>

class ui_wdg_btnlabel : public QLabel
{
    Q_OBJECT
public:
    explicit ui_wdg_btnlabel(QWidget *parent = 0);

	void mousePressEvent(QMouseEvent *ev);

signals:
	void clicked();

public slots:

};

#endif // UI_WDG_BTNLABEL_H
