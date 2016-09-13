#ifndef UI_WDG_ULIST_H
#define UI_WDG_ULIST_H

#include <QtWidgets/QTreeView>
#include <QtWidgets/QItemDelegate>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QHBoxLayout>
#include <math.h>

#include "global.h"
#include "u_core.h"

class ui_wdg_ulist_mdl;
class ui_wdg_ulist_control;
class ui_wdg_ulist;

class ui_wdg_ulist : public QTreeView
{
	Q_OBJECT
public:
	explicit ui_wdg_ulist(QWidget *parent = 0);
	void resizeEvent(QResizeEvent *event);

	ui_wdg_ulist_mdl * mdl;

	QAction * cm_viewInfo;
	QAction * cm_copyUrl;
	QAction * cm_copyAllFilesUrl;
	QAction * cm_copyAllFilesUrlDescr;

signals:

public slots:
	void upd();
	void son_dblclick(QModelIndex index);
	void copy_links();
	void copy_all_files_links();
	void copy_all_files_links_descr();
	void open_info();
};

class ui_wdg_ulist_control : public QItemDelegate
{
	Q_OBJECT
public:
	explicit ui_wdg_ulist_control(QObject * parent = 0);

	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
	QWidget * createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

class ui_wdg_ulist_mdl : public QAbstractItemModel
{
	Q_OBJECT

public:
	ui_wdg_ulist_mdl(QObject *parent = 0);
	~ui_wdg_ulist_mdl();

	void upd();

	QVariant headerData(int section, Qt::Orientation orientation, int role) const;
	Qt::ItemFlags flags(const QModelIndex &index) const;
	int rowCount(const QModelIndex &parent) const;
	int columnCount(const QModelIndex &parent) const;
	QVariant data(const QModelIndex &index, int role) const;
	QModelIndex index(int row, int column, const QModelIndex &parent) const;
	QModelIndex parent(const QModelIndex &child) const;

	static QString format_time (int time);
};

#endif // UI_WDG_ULIST_H
