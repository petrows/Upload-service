#ifndef ui_wdg_flist_H
#define ui_wdg_flist_H

#include <QTreeView>
#include <QItemDelegate>
#include <QLabel>
#include <QPushButton>
#include <QProgressBar>
#include <QHBoxLayout>
#include <math.h>

#include "global.h"
#include "u_core.h"

class ui_wdg_flist_mdl;
class ui_wdg_flist_control;
class ui_wdg_flist;

class ui_wdg_flist : public QTreeView
{
    Q_OBJECT
public:
	explicit ui_wdg_flist(QWidget *parent, u_upload * upl);
	void resizeEvent(QResizeEvent *event);

	ui_wdg_flist_mdl * mdl;
	u_upload * upl;
	QAction  * cm_copyUrl;
	QAction  * cm_copyUrlDesc;
	QAction  * cm_openUrl;


signals:

public slots:
	void upd();
	void son_dblclick(QModelIndex index);
	void son_cm_copyLink();
	void son_cm_copyLinkDesc();
	void son_cm_openLink();
};

class ui_wdg_flist_control : public QItemDelegate
{
	Q_OBJECT
public:
	explicit ui_wdg_flist_control(QObject * parent = 0);

	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	QWidget * createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

class ui_wdg_flist_mdl : public QAbstractItemModel
{
	Q_OBJECT

public:
	ui_wdg_flist_mdl(QObject *parent = 0);
	~ui_wdg_flist_mdl();

	void upd();
	u_upload * upl;

	QVariant headerData(int section, Qt::Orientation orientation, int role) const;
	Qt::ItemFlags flags(const QModelIndex &index) const;
	int rowCount(const QModelIndex &parent) const;
	int columnCount(const QModelIndex &parent) const;
	QVariant data(const QModelIndex &index, int role) const;
	QModelIndex index(int row, int column, const QModelIndex &parent) const;
	QModelIndex parent(const QModelIndex &child) const;

	static QString format_time (int time);
};

#endif // ui_wdg_flist_H
